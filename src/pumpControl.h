
#include <Arduino.h>

int sensorState = 0; // variable for reading the pushbutton status
int buttonState = 1;
int menuState = 0;

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
    //timer to prevent flood
    if (counter >= TIME_OUT_PUMP)
    {
        systemStatus = false;
        digitalWrite(PUMP_PIN, LOW);
        Serial.println("Timeout pump");
        Serial.println("System turned OFF");
    }

    // read the state of the pushbutton value:
    sensorState = digitalRead(SENSOR_PIN);
    buttonState = digitalRead(SELECT_BUTTON);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (sensorState == LOW && systemStatus == true)
    {
        // turn LED on:
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(PUMP_PIN, HIGH);
        Serial.println("Pump activated");
    }
    else
    {
        // turn LED off:
        digitalWrite(LED_PIN, LOW);
        digitalWrite(PUMP_PIN, LOW);
        counter=0;
    }


    if (buttonState == LOW)
    {

        digitalWrite(LED_PIN, HIGH);
    }

    if (buttonState == LOW)
    {
        menuState++;

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
