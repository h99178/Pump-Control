
uint8_t _ui8cursorPosition = 0;


void printTime(int caseMenu)
{

    String _strfirst;
    String _strsecond;
    bool _boolcleanLine1 = false;
    bool _boolcleanLine2 = false;
    lcd.setBacklight(255);

    switch (caseMenu)
    {
    case 1:

        _strfirst = "Date: " + getDate();
        _boolcleanLine1 = true;
        _strsecond = "Time: " + getTime();
        _boolcleanLine2 = false;
        lcd.noBlink();
        lcd.noCursor();
        break;

    case 2:
        _strsecond = "Time: " + getTime();
        _boolcleanLine1 = true;
        break;

    case 3:

        _strfirst = "Date: " + getDate();
        _boolcleanLine1 = true;
        lcd.blink();
        break;

    default:
        break;
    }

    printLDCMessage(_strfirst, 0, 0, _boolcleanLine1);
    printLDCMessage(_strsecond, 0, 1, _boolcleanLine2);
    if (systemStatus)
    {
        lcd.setCursor(15, 1);
        lcd.print("*");
    }
}

void statusLCD()
{
    printLDCMessage("PD: " + String(timesRunningdosingPump[0]) + "|" + String(timesRunningdosingPump[1]) + "|" + String(timesRunningdosingPump[2]), 0, 0, true);
    lcd.noBlink();
    lcd.noCursor();
    printLDCMessage("PR: " + String(timesRunningResillPump), 0, 1, false);
    //lcd.setCursor(_ui8cursorPositionTmp, 1);
}

void editDate(String dateValue, uint8_t _ui8cursorPositionTmp)
{

    printLDCMessage("Edit Date:", 0, 0, true);
    lcd.blink();
    lcd.cursor();
    printLDCMessage(dateValue, 0, 1, false);
    lcd.setCursor(_ui8cursorPositionTmp, 1);
}

void editTime(String dateValue, uint8_t _ui8cursorPositionTmp)
{

    printLDCMessage("Edit Time", 0, 0, true);
    lcd.blink();
    lcd.cursor();
    printLDCMessage(dateValue, 0, 1, false);
    lcd.setCursor(_ui8cursorPositionTmp, 1);
}

void editDateTime(int line)
{
    lcd.noBlink();
    lcd.noCursor();
    printLDCMessage("Edit Date:", 0, 0, true);
    printArrowLeft(line, 13);
    printLDCMessage("Edit Time:", 0, 1, false);
}

void editPump(int line)
{
    lcd.noBlink();
    lcd.noCursor();
    printLDCMessage("Pump refill:", 0, 0, true);
    printArrowLeft(line, 13);
    printLDCMessage("Pump dosing:", 0, 1, false);
}

String funcPreareDate(int dayTmp, int monthTmp, int yearTmp)
{
    Serial.println("Func Prepare Date");
    String dayTmpStr;
    String monthTmpStr;
    String yearTmpStr = String(yearTmp);

    if (dayTmp < 10)
    {
        dayTmpStr = "0" + String(dayTmp);
    }
    else
    {
        dayTmpStr = String(dayTmp);
    }

    if (monthTmp < 10)
    {
        monthTmpStr = "0" + String(monthTmp);
    }
    else
    {
        monthTmpStr = String(monthTmp);
    }

    return dayTmpStr + "/" + monthTmpStr + "/" + yearTmpStr;
}

String funcPreareTime(int hourTmp, int minTmp, int secTmp)
{
    Serial.println("Func Prepare Time");
    String hourTmpStr;
    String minTmpStr;
    String secTmpStr;

    if (hourTmp < 10)
    {
        hourTmpStr = "0" + String(hourTmp);
    }
    else
    {
        hourTmpStr = String(hourTmp);
    }

    if (minTmp < 10)
    {
        minTmpStr = "0" + String(minTmp);
    }
    else
    {
        minTmpStr = String(minTmp);
    }

    if (secTmp < 10)
    {
        secTmpStr = "0" + String(secTmp);
    }
    else
    {
        secTmpStr = String(secTmp);
    }

    return hourTmpStr + ":" + minTmpStr + ":" + secTmpStr;
}

void menuEditDate()
{

    Serial.println("Func Edit Date");
    editDate(getDate(), 0);
    _ui8cursorPosition = 1;
    uint8_t _ui8cursorPositiontmp = 1;
    int dayTmp = myrtc.dayofmonth;
    int monthTmp = myrtc.month;
    int yearTmp = myrtc.year;
    int hourTmp = myrtc.hours;
    int minTmp = myrtc.minutes;
    int secTmp = myrtc.seconds;

    int dayTmpold = myrtc.dayofmonth;
    int monthTmpold = myrtc.month;
    int yearTmpold = myrtc.year;
    bool keyPressed = false;
    while (getKey() != NONE)
    {
        /* code */
    }
    while (true)
    {
        byte keyValeuStr = getKey();
        if (keyValeuStr == RIGHT)
        {

            if (_ui8cursorPosition == 1)
            {
                _ui8cursorPosition = 4;
            }
            else if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 9;
            }
            keyPressed = true;
        }

        if (keyValeuStr == LEFT)
        {
            if (_ui8cursorPosition == 9)
            {
                _ui8cursorPosition = 4;
            }
            else if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 1;
            }
            keyPressed = true;
        }

        if (keyValeuStr == UP)
        {
            Serial.println("UP Clicked");
            if (_ui8cursorPosition == 1)
            {
                if (dayTmp <= 31)
                {
                    dayTmp++;
                }
                else
                {
                    dayTmp = 1;
                }
            }
            else if (_ui8cursorPosition == 4)
            {
                if (monthTmp == 12)
                {
                    monthTmp = 1;
                }
                else
                {
                    monthTmp++;
                }
            }
            else
            {
                yearTmp++;
            }
            keyPressed = true;
        }

        if (keyValeuStr == DOWN)
        {
            Serial.println("DOWN Clicked");
            if (_ui8cursorPosition == 1)
            {
                if (dayTmp == 1)
                {
                    dayTmp = 31;
                }
                else
                {
                    dayTmp--;
                }
            }
            else if (_ui8cursorPosition == 4)
            {
                if (monthTmp == 1)
                {
                    monthTmp = 12;
                }
                else
                {
                    monthTmp--;
                }
            }
            else
            {
                yearTmp--;
            }
            keyPressed = true;
        }

        if (keyValeuStr == ESC)
        {
            break;
        }

        if (keyValeuStr == ENTER)
        {
            setDateTime(secTmp, minTmp, hourTmp, 1, dayTmp, monthTmp, yearTmp);
            break;
        }

        if (dayTmp != dayTmpold || monthTmp != monthTmpold || yearTmp != yearTmpold || _ui8cursorPositiontmp != _ui8cursorPosition)
        {
            /* code */
            editDate(funcPreareDate(dayTmp, monthTmp, yearTmp), _ui8cursorPosition);
            dayTmpold = dayTmp;
            monthTmpold = monthTmp;
            yearTmpold = yearTmp;
            _ui8cursorPositiontmp = _ui8cursorPosition;
        }

        if (keyPressed)
        {
            keyPressed = false;
            while (getKey() != NONE);
            // {
            //     /* code */
            // }
        }

    }
}

void menuEditTime()
{
    Serial.println("Func Edit Time");
    editTime(getTime(), 0);
    _ui8cursorPosition = 1;
    uint8_t _ui8cursorPositionOld = _ui8cursorPosition;
    int dayTmp = myrtc.dayofmonth;
    int monthTmp = myrtc.month;
    int yearTmp = myrtc.year;
    int hourTmp = myrtc.hours;
    int minTmp = myrtc.minutes;
    int secTmp = myrtc.seconds;

    bool keyPressed = false;

    int hourTmpOld = myrtc.hours;
    int minTmpOld = myrtc.minutes;
    int secTmpOld = myrtc.seconds;

    while (getKey() != NONE)
    {
        /* code */
    }
    while (true)
    {
        byte keyValeuStr = getKey();
        if (keyValeuStr == RIGHT)
        {

            if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 7;
            }
            else if (_ui8cursorPosition == 1)
            {
                _ui8cursorPosition = 4;
            }
            keyPressed = true;
        }

        if (keyValeuStr == LEFT)
        {

            if (_ui8cursorPosition == 7)
            {
                _ui8cursorPosition = 4;
            }
            else if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 1;
            }
            keyPressed = true;
        }

        if (keyValeuStr == UP)
        {
            Serial.println("UP Clicked");
            if (_ui8cursorPosition == 1)
            {
                if (hourTmp <= 23)
                {
                    hourTmp++;
                }
                else
                {
                    hourTmp = 0;
                }
            }
            else if (_ui8cursorPosition == 4)
            {
                if (minTmp == 60)
                {
                    minTmp = 0;
                }
                else
                {
                    minTmp++;
                }
            }
            else
            {
                if (secTmp == 60)
                {
                    secTmp = 0;
                }
                else
                {
                    secTmp++;
                }
            }
            keyPressed = true;
        }

        if (keyValeuStr == DOWN)
        {
            Serial.println("DOWN Clicked");

            if (_ui8cursorPosition == 1)
            {
                if (hourTmp == 0)
                {
                    hourTmp = 23;
                }
                else
                {
                    hourTmp--;
                }
            }
            else if (_ui8cursorPosition == 4)
            {
                if (minTmp == 0)
                {
                    minTmp = 60;
                }
                else
                {
                    minTmp--;
                }
            }
            else
            {
                if (secTmp == 0)
                {
                    secTmp = 60;
                }
                else
                {
                    secTmp--;
                }
            }
            keyPressed = true;
        }

        if (keyValeuStr == ESC)
        {
            Serial.println("ESC Clicked");
            while (getKey() == ESC)
            {
                /* code */
            }
            break;
        }

        if (keyValeuStr == ENTER)
        {
            setDateTime(secTmp, minTmp, hourTmp, 1, dayTmp, monthTmp, yearTmp);
            Serial.println("ENTER Clicked");
            while (getKey() == ENTER)
            {
                /* code */
            }

            break;
        }

        if (hourTmp != hourTmpOld || minTmp != minTmpOld || secTmp != secTmpOld || _ui8cursorPosition != _ui8cursorPositionOld)
        {
            Serial.println(funcPreareTime(hourTmp, minTmp, secTmp) + " " + String(_ui8cursorPosition));
            editTime(funcPreareTime(hourTmp, minTmp, secTmp), _ui8cursorPosition);
            hourTmpOld = hourTmp;
            minTmpOld = minTmp;
            secTmpOld = secTmp;
            _ui8cursorPositionOld = _ui8cursorPosition;
        }

        if (keyPressed)
        {
            keyPressed = false;
            while (getKey() != NONE)
            {
                /* code */
            }
        }

        //delay(100);
    }
}

void printPumpRefill()
{
    lcd.home();
    lcd.clear();
    String pumpState;

    if (systemStatus)
    {
        pumpState = "ON";
    }
    else
    {
        pumpState = "OFF";
    }

    lcd.print("Pump Refill: " + pumpState);
}

void menuEditPump1()
{

    printPumpRefill();
    while (getKey() != NONE)
    {
        /* code */
    }

    while (true)
    {
        byte keyValeuStr = getKey();
        //counter = 0;

        if (keyValeuStr == LEFT)
        {
            while (getKey() != NONE)
            {
                /* code */
            }
            systemStatus = systemStatus ^ 1;
            Serial.println(systemStatus);
            printPumpRefill();
        }

        if (keyValeuStr == RIGHT)
        {
            while (getKey() != NONE)
            {
                /* code */
            }
            systemStatus = systemStatus ^ 1;
            Serial.println(systemStatus);
            printPumpRefill();
        }

        if (keyValeuStr == ESC)
        {
            while (getKey() != NONE)
            {
                /* code */
            }
            break;
        }

        if (keyValeuStr == ENTER)
        {
            while (getKey() != NONE)
            {
                /* code */
            }
            break;
        }
    }
}

void menuEditPump2()
{

    lcd.home();
    lcd.clear();
    lcd.print("Pump menu2");
    delay(100);

    while (true)
    {
        byte keyValeuStr = getKey();

        if (keyValeuStr == ESC)
        {
            while (getKey() == ESC)
            {
                /* code */
            }
            break;
        }

        if (keyValeuStr == ENTER)
        {
            while (getKey() == ESC)
            {
                /* code */
            }
            break;
        }
    }
}

void callMenu(int menuNumber)
{

    switch (menuNumber)
    {
    case 1:
        editDateTime(0);
        Serial.println("DateTime Menu line 1");
        break;

    case 2:
        editDateTime(1);
        Serial.println("DateTime Menu line 2");
        break;

    case 3:
        editPump(0);
        Serial.println("Pump Menu 1");
        break;

    case 4:
        editPump(1);
        Serial.println("Pump Menu 2");
        break;
    case 5:
        Serial.println("Status menu");
        statusLCD();
        break;

    default:
        break;
    }
}

void callSelectedMenu(int menuNumber)
{

    switch (menuNumber)
    {
    case 1:
        Serial.println("Edit date menu");
        menuEditDate();
        break;
    case 2:
        Serial.println("Edit time menu");
        menuEditTime();
        break;
    case 3:
        Serial.println("Edit pump refill menu");
        menuEditPump1();
        break;
    case 4:
        Serial.println("Edit pump menu");
        menuSelectPumpConfig();
        break;
    case 5:
        Serial.println("Status menu");
        statusLCD();
        break;

    default:
        break;
    }
}

void menuMain()
{
    int pageNumber = 1;
    int numberOfmenu = 5; //quantidade de menus na funcao callMenu()
    Serial.println("ENTER Clicked");

    while (getKey() == ENTER)
    {
        Serial.println("ENTER ######");
        delay(100);
    }

    while (pageNumber != 0)
    {

        callMenu(pageNumber);
        while (true)
        {
            byte keyValeuStr = getKey();
            if (keyValeuStr == DOWN && pageNumber < numberOfmenu)
            {
                pageNumber++;
                Serial.println(pageNumber);
                break;
            }
            if (keyValeuStr == UP && pageNumber != 1)
            {
                pageNumber--;
                Serial.println(pageNumber);
                break;
            }
            if (keyValeuStr == ESC)
            {
                pageNumber = 0;
                break;
            }
            if (keyValeuStr == ENTER)
            {
                callSelectedMenu(pageNumber);
                break;
            }
        }
        while (getKey() != NONE)
        {
            //delay(50);
        }
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//menu calibration pump
//
//******************************************************************

//function used for pump calibration and configuration
void editPumpCal(uint8_t _ui8cursorPositionTmp)
{

    printLDCMessage("Select Pump:", 0, 0, true);
    lcd.blink();
    lcd.cursor();
    printLDCMessage("1   2   3", 0, 1, false);
    lcd.setCursor(_ui8cursorPositionTmp, 1);
}

void PumpCalLCD(uint8_t _ui8valueCalibrate, uint8_t pumpNumber)
{

    printLDCMessage("Pn Correct Fluid", 0, 0, true);
    lcd.noBlink();
    lcd.noCursor();
    printLDCMessage("P:" + (String)pumpNumber + " 100ml = " + (String)_ui8valueCalibrate, 0, 1, false);
}

void pumpCalibrate(uint8_t _ui8pumpNumber)
{

    Serial.println("Calibrate pump " + _ui8pumpNumber);

    long timeStartCal = 0;

    uint8_t _ui8valueCal = EEPROM.read(getPumpCalAddress(_ui8pumpNumber));
    uint8_t _ui8valueCalOld = _ui8valueCal;
    PumpCalLCD(_ui8valueCal, _ui8pumpNumber);

    bool keyPressed = false;
    bool startCalibration = false;
    bool finishCalibration = false;

    while (getKey() != NONE)
    {
        /* code */
    }
    while (true)
    {
        byte keyValeuStr = getKey();

        if (startCalibration)
        {
            _ui8valueCal = int((millis() - timeStartCal) / 1000);
        }

        if (keyValeuStr == UP)
        {
            Serial.println("UP Clicked");
            //
            if (startCalibration)
            {

                Serial.println("Stop calibration");
                startCalibration = false;
                finishCalibration = true;
                _ui8valueCal = int((millis() - timeStartCal) / 1000);

                digitalWrite(getPumpPin(_ui8pumpNumber), HIGH);
            }
            else
            {
                Serial.println("Start calibration");
                timeStartCal = millis();
                startCalibration = true;
                finishCalibration = false;
                digitalWrite(getPumpPin(_ui8pumpNumber), LOW);
            }

            keyPressed = true;
        }

        if (keyValeuStr == DOWN)
        {
            Serial.println("DOWN Clicked");
            if (startCalibration)
            {

                Serial.println("Stop calibration");
                startCalibration = false;
                finishCalibration = true;
                _ui8valueCal = int((millis() - timeStartCal) / 1000);

                digitalWrite(getPumpPin(_ui8pumpNumber), LOW);
            }
            else
            {
                Serial.println("Start calibration");
                timeStartCal = millis();
                startCalibration = true;
                finishCalibration = false;
                digitalWrite(getPumpPin(_ui8pumpNumber), HIGH);
            }

            keyPressed = true;
        }

        if (keyValeuStr == ESC)
        {
            Serial.println("ESC Clicked");
            while (getKey() == ESC)
            {
                /* code */
            }
            break;
        }

        if (keyValeuStr == ENTER)
        {
            Serial.println("ENTER Clicked");
            while (getKey() == ENTER)
            {
                /* code */
            }
            if (finishCalibration)
            {
                EEPROM.update(getPumpCalAddress(_ui8pumpNumber), _ui8valueCal);
            }

            break;
        }

        if (_ui8valueCalOld != _ui8valueCal && startCalibration)
        {
            /* code */
            Serial.println("Pump value cal" + (String)_ui8valueCal);
            PumpCalLCD(_ui8valueCal, _ui8pumpNumber);
            _ui8valueCalOld = _ui8valueCal;
        }

        if (keyPressed)
        {
            keyPressed = false;
            while (getKey() != NONE)
            {
                /* code */
            }
        }
        delay(100);
    }
}

void menuSelectPumpCal()
{
    Serial.println("Func Cal Pump");
    editPumpCal(0);
    _ui8cursorPosition = 0;
    uint8_t _ui8cursorPositionOld = _ui8cursorPosition;

    bool keyPressed = false;

    while (getKey() != NONE)
    {
        /* code */
    }
    while (true)
    {
        byte keyValeuStr = getKey();
        if (keyValeuStr == RIGHT)
        {

            Serial.println("RIGHT Clicked");
            if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 8;
            }
            else if (_ui8cursorPosition == 0)
            {
                _ui8cursorPosition = 4;
            }
            keyPressed = true;
        }

        if (keyValeuStr == LEFT)
        {
            Serial.println("LEFT Clicked");
            if (_ui8cursorPosition == 8)
            {
                _ui8cursorPosition = 4;
            }
            else if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 0;
            }
            keyPressed = true;
        }

        if (keyValeuStr == UP)
        {
            Serial.println("UP Clicked");
            //
            keyPressed = true;
        }

        if (keyValeuStr == DOWN)
        {
            Serial.println("DOWN Clicked");

            //
            keyPressed = true;
        }

        if (keyValeuStr == ESC)
        {
            Serial.println("ESC Clicked");
            while (getKey() == ESC)
            {
                /* code */
            }
            break;
        }

        if (keyValeuStr == ENTER)
        {
            Serial.println("ENTER Clicked");
            while (getKey() == ENTER)
            {
                /* code */
            }

            if (_ui8cursorPosition == 0)
            {
                pumpCalibrate(1);
            }

            if (_ui8cursorPosition == 4)
            {
                pumpCalibrate(2);
            }

            if (_ui8cursorPosition == 8)
            {
                pumpCalibrate(3);
            }

            break;
        }

        if (_ui8cursorPositionOld != _ui8cursorPosition)
        {
            /* code */
            editPumpCal(_ui8cursorPosition);
            _ui8cursorPositionOld = _ui8cursorPosition;
        }

        if (keyPressed)
        {
            keyPressed = false;
            while (getKey() != NONE)
            {
                /* code */
            }
        }

        //delay(100);
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//menu pump configuration
//
//******************************************************************

void pumpConfigMilliliterLCD(uint8_t _ui8milliliter, uint8_t pumpNumber)
{
    //Pn Dosing Volume:
    // Num: 1 -- 0010ml
    printLDCMessage("Pn Dosing Volume:", 0, 0, true);
    lcd.noBlink();
    lcd.noCursor();
    printLDCMessage("P:" + (String)pumpNumber + " -- " + (String)_ui8milliliter + "ml", 0, 1, false);
}

void pumpDosingDay(uint8_t _ui8timesDay, uint8_t pumpNumber)
{
    // Times a Days:
    // For: 0 (0~30)
    printLDCMessage("Times a Day:", 0, 0, true);
    lcd.noBlink();
    lcd.noCursor();
    printLDCMessage("P:" + (String)pumpNumber + " -- " + (String)_ui8timesDay + " Times", 0, 1, false);
}

void pumpConfigTimesDay(uint8_t _ui8pumpNumber)
{

    Serial.println("Configuration pump times a day " + _ui8pumpNumber);

    uint8_t _ui8valueTimesDay = EEPROM.read(getPumpTimesDayAddress(_ui8pumpNumber));
    uint8_t _ui8valueTimesDayOld = _ui8valueTimesDay;
    //myrtc.updateTime();
    pumpDosingDay(_ui8valueTimesDay, _ui8pumpNumber);

    bool keyPressed = false;

    while (getKey() != NONE)
    {
        /* code */
    }
    while (true)
    {
        byte keyValeuStr = getKey();

        if (keyValeuStr == UP)
        {
            Serial.println("UP Clicked");
            //
            _ui8valueTimesDay = _ui8valueTimesDay + 1;
            keyPressed = true;
        }

        if (keyValeuStr == DOWN)
        {
            Serial.println("DOWN Clicked");
            if (_ui8valueTimesDay > 0)
            {
                _ui8valueTimesDay = _ui8valueTimesDay - 1;
            }
            else
            {
                _ui8valueTimesDay = 255;
            }

            keyPressed = true;
        }

        if (keyValeuStr == ESC)
        {
            Serial.println("ESC Clicked");
            while (getKey() == ESC)
            {
                /* code */
            }
            break;
        }

        if (keyValeuStr == ENTER)
        {
            Serial.println("ENTER Clicked");
            while (getKey() == ENTER)
            {
                /* code */
            }

            EEPROM.update(getPumpTimesDayAddress(_ui8pumpNumber), _ui8valueTimesDay);

            break;
        }

        if (_ui8valueTimesDayOld != _ui8valueTimesDay)
        {
            /* code */
            Serial.println("Pump value ML" + (String)_ui8valueTimesDay);
            pumpDosingDay(_ui8valueTimesDay, _ui8pumpNumber);
            _ui8valueTimesDayOld = _ui8valueTimesDay;
        }

        if (keyPressed)
        {
            keyPressed = false;
            while (getKey() != NONE)
            {
                /* code */
            }
        }
        delay(100);
    }
}

void pumpConfigMilliter(uint8_t _ui8pumpNumber)
{

    Serial.println("Configuration pump milliliter " + _ui8pumpNumber);

    uint8_t _ui8valueMl = EEPROM.read(getPumpMilliliterAddress(_ui8pumpNumber));
    uint8_t _ui8valueMlOld = _ui8valueMl;
    myrtc.updateTime();
    pumpConfigMilliliterLCD(_ui8valueMl, _ui8pumpNumber);

    bool keyPressed = false;
    // bool startCalibration = false;
    // bool finishCalibration = false;

    while (getKey() != NONE)
    {
        /* code */
    }
    while (true)
    {
        byte keyValeuStr = getKey();

        if (keyValeuStr == UP)
        {
            Serial.println("UP Clicked");
            //
            _ui8valueMl = _ui8valueMl + 1;
            keyPressed = true;
        }

        if (keyValeuStr == DOWN)
        {
            Serial.println("DOWN Clicked");
            if (_ui8valueMl > 0)
            {
                _ui8valueMl = _ui8valueMl - 1;
            }
            else
            {
                _ui8valueMl = 255;
            }

            keyPressed = true;
        }

        if (keyValeuStr == ESC)
        {
            Serial.println("ESC Clicked");
            while (getKey() == ESC)
            {
                /* code */
            }
            break;
        }

        if (keyValeuStr == ENTER)
        {
            Serial.println("ENTER Clicked");
            while (getKey() == ENTER)
            {
                /* code */
            }

            EEPROM.update(getPumpMilliliterAddress(_ui8pumpNumber), _ui8valueMl);
            pumpConfigTimesDay(_ui8pumpNumber);
            break;
        }

        if (_ui8valueMlOld != _ui8valueMl)
        {
            /* code */
            Serial.println("Pump value ML" + (String)_ui8valueMl);
            pumpConfigMilliliterLCD(_ui8valueMl, _ui8pumpNumber);
            _ui8valueMlOld = _ui8valueMl;
        }

        if (keyPressed)
        {
            keyPressed = false;
            while (getKey() != NONE)
            {
                /* code */
            }
        }
        delay(100);
    }
}

void menuSelectPumpConfig()
{
    Serial.println("Func config Pump");
    editPumpCal(0);
    _ui8cursorPosition = 0;
    uint8_t _ui8cursorPositionOld = _ui8cursorPosition;

    bool keyPressed = false;

    while (getKey() != NONE)
    {
        /* code */
    }
    while (true)
    {
        byte keyValeuStr = getKey();
        if (keyValeuStr == RIGHT)
        {

            Serial.println("RIGHT Clicked");
            if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 8;
            }
            else if (_ui8cursorPosition == 0)
            {
                _ui8cursorPosition = 4;
            }
            keyPressed = true;
        }

        if (keyValeuStr == LEFT)
        {
            Serial.println("LEFT Clicked");
            if (_ui8cursorPosition == 8)
            {
                _ui8cursorPosition = 4;
            }
            else if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 0;
            }
            keyPressed = true;
        }

        if (keyValeuStr == ESC)
        {
            Serial.println("ESC Clicked");
            while (getKey() == ESC)
            {
                /* code */
            }
            break;
        }

        if (keyValeuStr == ENTER)
        {
            Serial.println("ENTER Clicked");
            while (getKey() == ENTER)
            {
                /* code */
            }

            if (_ui8cursorPosition == 0)
            {
                pumpConfigMilliter(1);
            }

            if (_ui8cursorPosition == 4)
            {
                pumpConfigMilliter(2);
            }

            if (_ui8cursorPosition == 8)
            {
                pumpConfigMilliter(3);
            }

            break;
        }

        if (_ui8cursorPositionOld != _ui8cursorPosition)
        {
            /* code */
            editPumpCal(_ui8cursorPosition);
            _ui8cursorPositionOld = _ui8cursorPosition;
        }

        if (keyPressed)
        {
            keyPressed = false;
            while (getKey() != NONE)
            {
                /* code */
            }
        }

        //delay(100);
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//menu pump run
//
//******************************************************************

void pumpRunLCD(uint8_t pumpNumber, String status)
{
    //Pn Dosing Volume:
    // Num: 1 -- 0010ml
    printLDCMessage("Pump rum:", 0, 0, true);
    lcd.noBlink();
    lcd.noCursor();
    printLDCMessage("P:" + (String)pumpNumber + " -- " + status, 0, 1, false);
}

void pumpRun(uint8_t _ui8pumpNumber)
{

    Serial.println("Run pump  " + _ui8pumpNumber);

    pumpRunLCD(_ui8pumpNumber, "OFF");

    bool keyPressed = false;

    while (getKey() != NONE)
    {
        /* code */
    }
    while (true)
    {
        byte keyValeuStr = getKey();

        if (keyValeuStr == UP)
        {
            Serial.println("UP Clicked");
            //
            digitalWrite(getPumpPin(_ui8pumpNumber), LOW);
            pumpRunLCD(_ui8pumpNumber, "ON");
            keyPressed = true;
        }

        if (keyValeuStr == DOWN)
        {
            Serial.println("DOWN Clicked");
            digitalWrite(getPumpPin(_ui8pumpNumber), HIGH);
            pumpRunLCD(_ui8pumpNumber, "OFF");

            keyPressed = true;
        }

        if (keyValeuStr == ESC)
        {
            Serial.println("ESC Clicked");
            while (getKey() == ESC)
            {
                /* code */
            }
            digitalWrite(getPumpPin(_ui8pumpNumber), HIGH);
            break;
        }

        if (keyValeuStr == ENTER)
        {
            Serial.println("ENTER Clicked");
            while (getKey() == ENTER)
            {
                /* code */
            }
            break;
        }

        if (keyPressed)
        {
            keyPressed = false;
            while (getKey() != NONE)
            {
                /* code */
            }
        }
        delay(100);
    }
}

void menuSelectPumpRun()
{
    Serial.println("Func config Pump");
    editPumpCal(0);
    _ui8cursorPosition = 0;
    uint8_t _ui8cursorPositionOld = _ui8cursorPosition;

    bool keyPressed = false;

    while (getKey() != NONE)
    {
        /* code */
    }
    while (true)
    {
        byte keyValeuStr = getKey();
        if (keyValeuStr == RIGHT)
        {

            Serial.println("RIGHT Clicked");
            if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 8;
            }
            else if (_ui8cursorPosition == 0)
            {
                _ui8cursorPosition = 4;
            }
            keyPressed = true;
        }

        if (keyValeuStr == LEFT)
        {
            Serial.println("LEFT Clicked");
            if (_ui8cursorPosition == 8)
            {
                _ui8cursorPosition = 4;
            }
            else if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 0;
            }
            keyPressed = true;
        }

        if (keyValeuStr == ESC)
        {
            Serial.println("ESC Clicked");
            while (getKey() == ESC)
            {
                /* code */
            }
            break;
        }

        if (keyValeuStr == ENTER)
        {
            Serial.println("ENTER Clicked");
            while (getKey() == ENTER)
            {
                /* code */
            }

            if (_ui8cursorPosition == 0)
            {
                pumpRun(1);
            }

            if (_ui8cursorPosition == 4)
            {
                pumpRun(2);
            }

            if (_ui8cursorPosition == 8)
            {
                pumpRun(3);
            }

            break;
        }

        if (_ui8cursorPositionOld != _ui8cursorPosition)
        {
            /* code */
            editPumpCal(_ui8cursorPosition);
            _ui8cursorPositionOld = _ui8cursorPosition;
        }

        if (keyPressed)
        {
            keyPressed = false;
            while (getKey() != NONE)
            {
                /* code */
            }
        }

        //delay(100);
    }
}