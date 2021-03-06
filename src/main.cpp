#include <Arduino.h>
//#include "lcd.h"
#include "config.h"
#include "pumpControl.h"
#include "keypad.h"
#include "menu.h"
//#include "dateTime.h"

int analogPin = A0;
int val = 0;

void setup()
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  // initialize the pushbutton pin as an input:
  pinMode(analogPin, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP); //
  pinMode(sensorPin, INPUT_PULLUP);    //water level sensor

  lcdInit();
  //setupRTC();

  // initialize timer1
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 34286;          // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12);  // 256 prescaler
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  interrupts();           // enable all interrupts
}

ISR(TIMER1_OVF_vect) // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  TCNT1 = 34286; // preload timer

  if (systemStatus == 0)
  {
    digitalWrite(ledPin, digitalRead(ledPin) ^ 1);
  }

  counter = counter + 1;
  //Serial.println(counter);
  if (systemStatus && counter >= timePump)
  {
    Serial.println("Stop pump refill " + String(counter));
    systemStatus = false;
    digitalWrite(pumpPin, LOW);
  }
}

void loop()
{

  printTime(1);
  for (size_t i = 0; i < 41; i++)
  {
    if (getKey() == ENTER)
    {
      menuMain();
    }
    delay(25);
    pumpControl();
  }
}
