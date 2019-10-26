
#include <Arduino.h>

int sensorState = 0; // variable for reading the pushbutton status
int buttonState = 1;
int menuState = 0;

void blinkLED(int value, int onoff)
{

    for (int i; i <= value; i++)
    {
        digitalWrite(ledPin, HIGH);
        delay(100);
        digitalWrite(ledPin, LOW);
        delay(100);
    }
    if (onoff > 0)
    {
        digitalWrite(ledPin, HIGH);
    }
    else
    {
        digitalWrite(ledPin, LOW);
    }
}

void pumpControl()
{
    //timer to prevent flood
    if (counter >= timePump)
    {
        systemStatus = false;
        digitalWrite(pumpPin, LOW);
        Serial.println("Timeout pump");
        Serial.println("System turned OFF");
    }

    // read the state of the pushbutton value:
    sensorState = digitalRead(sensorPin);
    buttonState = digitalRead(selectButton);

    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (sensorState == LOW && systemStatus == true)
    {
        // turn LED on:
        digitalWrite(ledPin, HIGH);
        digitalWrite(pumpPin, HIGH);
        Serial.println("Pump activated");
    }
    else
    {
        // turn LED off:
        digitalWrite(ledPin, LOW);
        digitalWrite(pumpPin, LOW);
        counter=0;
    }


    if (buttonState == LOW)
    {

        digitalWrite(ledPin, HIGH);
    }

    if (buttonState == LOW)
    {
        menuState++;

        while (true)
        {
            delay(200);
            if (digitalRead(selectButton) == LOW)
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
            digitalWrite(pumpPin, LOW);
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
