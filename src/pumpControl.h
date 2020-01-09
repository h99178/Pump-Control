
void blinkLED(int value, int onoff)
{

    for (int i; i <= value; i++)
    {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
    }
    if (onoff > 0)
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }
}


void pumpControl()
{
    // read the state of the pushbutton value:
    int sensorState = digitalRead(SENSOR_PIN);
    int buttonState = digitalRead(SELECT_BUTTON);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (sensorState == LOW && systemStatus == true)
    {
        // turn LED on:
        if (!refillPumpRunning)
        {
            refillPumpRunning = true;
            digitalWrite(LED_PIN, HIGH);
            digitalWrite(PUMP_PIN, HIGH);
            pumpRefillStartTime = millis();
            Serial.println("Pump activated");
            timesRunningResillPump++;
            Serial.println("count pump " + String(timesRunningResillPump));
        }
    }
    else
    {

        digitalWrite(LED_PIN, LOW);  // turn LED off
        digitalWrite(PUMP_PIN, LOW); // turn refill pump off:
        refillPumpRunning = false;
    }

    if (buttonState == LOW)
    {

        digitalWrite(LED_PIN, HIGH);
    }

    if (buttonState == LOW)
    {
        int menuState = 1;//++;

        while (true)
        {
            delay(200);
            if (digitalRead(SELECT_BUTTON) == LOW)
            {
                menuState++;
            }
            else
            {
                break;
            }
        }

        if (menuState == 1)
        {
            systemStatus = false;
            digitalWrite(PUMP_PIN, LOW);
            blinkLED(1, 0);
        }

        if (menuState > 1)
        {
            systemStatus = true;
            blinkLED(5, 0);
        }
        menuState = 0;
    }
}
