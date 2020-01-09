#include <LiquidCrystal_PCF8574.h>
#include <Wire.h>

LiquidCrystal_PCF8574 lcd(0x27);
int show = -1;

void lcdInit()
{
    int error;
    Wire.begin();
    Wire.beginTransmission(0x27);
    error = Wire.endTransmission();

    if (error == 0)
    {
        //Serial.println(": LCD found.");
        show = 0;
        lcd.begin(16, 2); // initialize the lcd
    }
}

int arrowMidle[8] = {
    0,
    0,
    0,
    31,
    31,
    0,
    0,
    0};
int arrowLeft[8] = {
    3,
    6,
    12,
    31,
    31,
    12,
    6,
    3};

int arrowRight[8] = {
    24,
    12,
    6,
    31,
    31,
    6,
    12,
    24};

int arrowUp[] = {
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

int arrowDown[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
};

void printArrowLeft(int line, int cursor)
{
    lcd.createChar(0, arrowLeft);
    lcd.createChar(1, arrowMidle);
    lcd.setCursor(cursor, line);
    lcd.print((char)0);
    lcd.print((char)1);
}
void printArrowRight(int line, int cursor)
{
    lcd.createChar(2, arrowRight);
    lcd.createChar(1, arrowMidle);
    lcd.setCursor(cursor, line);
    lcd.print((char)1);
    lcd.print((char)2);
}

void printArrowUp(int line, int cursor)
{
    lcd.createChar(3, arrowUp);
    lcd.setCursor(cursor, line);
    lcd.print((char)3);

}

void printArrowDown(int line, int cursor)
{
    lcd.createChar(4, arrowDown);
    lcd.setCursor(cursor, line);
    lcd.print((char)4);

}

void printLDCMessage(String msg, int cursor, int line, bool clean)
{
    lcd.setBacklight(255);
    lcd.home();
    if (clean)
    {
        lcd.clear();
    }

    lcd.setCursor(cursor, line);
    lcd.print(msg);

}
