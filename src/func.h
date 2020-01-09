
void checkKeyboad()
{
    if (getKey() == ENTER)
    {
        menuMain();
    }
    if (getKey() == DOWN || getKey() == UP)
    {
        menuSelectPumpCal();
    }
    if (getKey() == LEFT || getKey() == RIGHT)
    {
        menuSelectPumpRun();
    }
}

int getPumpCalAddress(int pumpNumber)
{

    switch (pumpNumber)
    {
    case 1:
        return PUMP_1_CALIBRATION;
        break;

    case 2:
        return PUMP_2_CALIBRATION;
        break;
    case 3:
        return PUMP_3_CALIBRATION;
        break;

    default:
        return 0;
        break;
    }
}

int getPumpMilliliterAddress(int pumpNumber)
{

    switch (pumpNumber)
    {
    case 1:
        return PUMP_1_MILLILITER;
        break;

    case 2:
        return PUMP_2_MILLILITER;
        break;
    case 3:
        return PUMP_3_MILLILITER;
        break;

    default:
        return 0;
        break;
    }
}

int getPumpTimesDayAddress(int pumpNumber)
{

    switch (pumpNumber)
    {
    case 1:
        return PUMP_1_TIMESDAY;
        break;

    case 2:
        return PUMP_2_TIMESDAY;
        break;
    case 3:
        return PUMP_3_TIMESDAY;
        break;

    default:
        return 100;
        break;
    }
}

int getPumpPin(int pumpNumber)
{

    switch (pumpNumber)
    {
    case 1:
        return PUMP_1_PIN;
        break;

    case 2:
        return PUMP_2_PIN;
        break;

    case 3:
        return PUMP_3_PIN;
        break;

    default:
        return 100;
        break;
    }
}

int calcRunTime(int hourStart, int minStart, int secStart, int hourEnd, int minEnd, int secEnd)
{

    int start = (hourStart * 3600) + (minStart * 60) + secStart;
    int end = (hourEnd * 3600) + (minEnd * 60) + secEnd;

    int totalSec = end - start;

    return totalSec;
}

float getTimeNowSeconds()
{
    //updated RTC from main.cpp every 1 sec
    float hour = float(myrtc.hours);
    float min = float(myrtc.minutes);
    float sec = float(myrtc.seconds);

    float timeInSeconds = (hour * 3600.0000) + (min * 60.0000) + (sec);

    return timeInSeconds;
}

bool checkTimeToDosing(int pumpNumber, int timesDay)
{

    float timeInSeconds = getTimeNowSeconds(); //float(hour * 3600.0000) + float(min * 60.0000) + float(sec);
    float intervalDosing = 86400.00 / timesDay;

    if (lastDosing[pumpNumber - 1] > timeInSeconds)
    {
        lastDosing[pumpNumber - 1] = 0;
    }

    float lastPump = lastDosing[pumpNumber - 1];
    float calc = (lastPump + intervalDosing) / timeInSeconds;
    float constante = 1.0000;

    if (calc <= constante)
    {
        //Serial.println("h " + String(float(36000.0000 * hour)) + " m " + String(float(min * 60.0000)) + " s " + String(float(sec)));
        Serial.println("Pump " + String(pumpNumber));
        Serial.println("time now " + String(timeInSeconds));
        Serial.println("last pump " + String(lastDosing[pumpNumber - 1]));
        Serial.println("Calc " + String(calc));

        lastDosing[pumpNumber - 1] = timeInSeconds;
        Serial.println("true pump" + String(pumpNumber));
        return true;
    }
    else
    {
        return false;
    }
}

void runPumpDosing(int pumpDosingNumber)
{
    if (!dosginPumpRunning[pumpDosingNumber - 1])
    {
        int pumpDosingVolume = EEPROM.read(getPumpMilliliterAddress(pumpDosingNumber));
        int pumpDosingTimesDay = EEPROM.read(getPumpTimesDayAddress(pumpDosingNumber));

        if (pumpDosingVolume > 0 && pumpDosingTimesDay > 0 && !refillPumpRunning && !(dosginPumpRunning[0] || dosginPumpRunning[1] || dosginPumpRunning[2]))
        {

            if (checkTimeToDosing(pumpDosingNumber, pumpDosingTimesDay))
            {

                int pumpDosingPin = getPumpPin(pumpDosingNumber);
                int pumpDosingCalValue = EEPROM.read(getPumpCalAddress(pumpDosingNumber));
                int pumpDosingTimeRun = (pumpDosingVolume * pumpDosingCalValue) / 100;

                digitalWrite(pumpDosingPin, LOW);
                timeStartDosing[pumpDosingNumber - 1] = millis();
                dosginPumpRunning[pumpDosingNumber - 1] = true;
                timeDosingMillis[pumpDosingNumber - 1] = pumpDosingTimeRun * 1000;
                timesRunningdosingPump[pumpDosingNumber - 1]++;
                Serial.println("Time to run: " + String(pumpDosingTimeRun) + " | dosing cal: " + pumpDosingCalValue + "  | dosing volume: " + pumpDosingVolume);
                //stop dosing by interrupt on main.cpp
            }
        }
    }
}

void checkDosingPumpToRun()
{
    //check every 5000 milliseconds
    if ((millis() - timeCheckDosingPump) >= 5000)
    {
        for (size_t i = 1; i <= PUMP_QUANTITY; i++)
        {
            runPumpDosing(i);
        }
        timeCheckDosingPump = millis();
    }
}

void updateTimeDateLCD()
{
    if (millis() - lastTimeUpdateLCD >= 1000)
    {
        printTime(1);
        lastTimeUpdateLCD = millis();
    }
}

void interruptDosingPump()
{
    for (int i = 1; i <= PUMP_QUANTITY; i++)
    {
        if (dosginPumpRunning[i - 1])
        {
            Serial.println("pump" + String(i) + " dosing time " + String(timeDosingMillis[i - 1]));

            if (long(millis() - timeStartDosing[i - 1]) >= long(timeDosingMillis[i - 1]))
            {
                digitalWrite(getPumpPin(i), HIGH);
                Serial.println("stop " + String(i) + "| time running " + String(millis() - timeStartDosing[i - 1]) + " |inicial " + String(timeStartDosing[i - 1]) + " | now " + String(millis()) + " | time to pump " + String(timeDosingMillis[i - 1]));
                dosginPumpRunning[i - 1] = false;
            }
        }
    }
}

void interruptRefillPump()
{
    if (refillPumpRunning)
    {
        if ((millis() - pumpRefillStartTime) >= ANTI_FLOOD_TIMEOUT)
        {
            long millisNow = millis();
            Serial.println("Stop pump refill ");
            Serial.println("time running " + String(millisNow - pumpRefillStartTime) + " | inicial " + String(pumpRefillStartTime) + " | now " + String(millisNow));
            systemStatus = false;
            digitalWrite(PUMP_PIN, LOW);
            refillPumpRunning = false;
        }
    }
}


void inictialiationDosingPump()
{
    myrtc.updateTime();
    float timeNowSec = getTimeNowSeconds();
    for (int i = 0; i < PUMP_QUANTITY; i++)
    {
        lastDosing[i] = timeNowSec;
        digitalWrite(getPumpPin(i), HIGH);
    }

    for (int i = 0; i < PUMP_QUANTITY; i++)
    {
        Serial.println("pump" + String(i + 1) + " " + (String)lastDosing[i]);
    }
}