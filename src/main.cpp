#include <Arduino.h>
#include <EEPROM.h>
#include "config.h"
#include "Header.h"
#include "lcd.h"
#include "dateTime.h"
#include "keypad.h"
#include "func.h"
#include "menu.h"
#include "pumpControl.h"

void setup()
{
  // initialize the LED pin as an output:
  pinMode(LED_PIN, OUTPUT);
  pinMode(PUMP_1_PIN, OUTPUT);
  pinMode(PUMP_2_PIN, OUTPUT);
  pinMode(PUMP_3_PIN, OUTPUT);
  Serial.begin(9600);
  digitalWrite(getPumpPin(1), HIGH);
  digitalWrite(getPumpPin(2), HIGH);
  digitalWrite(getPumpPin(3), HIGH);

  // initialize the pushbutton pin as an input:
  pinMode(KEYPAD_PIN, INPUT_PULLUP);
  pinMode(SELECT_BUTTON, INPUT_PULLUP); //
  pinMode(SENSOR_PIN, INPUT_PULLUP);    //water level sensor

  lcdInit();

  //initialize timer1
  noInterrupts(); // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 34286;          // preload timer 65536-16MHz/256/2Hz
  TCCR1B |= (1 << CS12);  // 256 prescaler
  TIMSK1 |= (1 << TOIE1); // enable timer overflow interrupt
  interrupts();           // enable all interrupts

  //update last pump time to prevent dosing pumping on the inicialization
  inictialiationDosingPump();
}

ISR(TIMER1_OVF_vect) // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
  TCNT1 = 34286; // preload timer

  if (systemStatus == 0)
  {
    digitalWrite(LED_PIN, digitalRead(LED_PIN) ^ 1);
  }

  //stop refill pump if timeout explode
  interruptRefillPump();

  //stop dosing pump base on time calculated from calibration value
  interruptDosingPump();
}

void loop()
{

  //update LCD time and date every 1000 milliseconds
  updateTimeDateLCD();

  //check key pressed on keyboard
  checkKeyboad();

  //refill pumo control
  pumpControl();

  //dosing pump control
  checkDosingPumpToRun();
}
