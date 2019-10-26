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

// void lcdStart()
// {
//     if (show == 0)
//     {
//         lcd.setBacklight(255);
//         lcd.home();
//         lcd.clear();
//         lcd.print("Hello LCD");
//         delay(1000);

//         lcd.setBacklight(0);
//         delay(400);
//         lcd.setBacklight(255);
//     }
//     else if (show == 1)
//     {
//         lcd.clear();
//         lcd.print("Cursor On");
//         lcd.cursor();
//     }
//     else if (show == 2)
//     {
//         lcd.clear();
//         lcd.print("Cursor Blink");
//         lcd.blink();
//     }
//     else if (show == 3)
//     {
//         lcd.clear();
//         lcd.print("Cursor OFF");
//         lcd.noBlink();
//         lcd.noCursor();
//     }
//     else if (show == 4)
//     {
//         lcd.clear();
//         lcd.print("Display Off");
//         lcd.noDisplay();
//     }
//     else if (show == 5)
//     {
//         lcd.clear();
//         lcd.print("Display On");
//         lcd.display();
//     }
//     else if (show == 7)
//     {
//         lcd.clear();
//         lcd.setCursor(0, 0);
//         lcd.print("*** first line.");
//         lcd.setCursor(0, 1);
//         lcd.print("*** second line.");
//     }
//     else if (show == 8)
//     {
//         lcd.scrollDisplayLeft();
//     }
//     else if (show == 9)
//     {
//         lcd.scrollDisplayLeft();
//     }
//     else if (show == 10)
//     {
//         lcd.scrollDisplayLeft();
//     }
//     else if (show == 11)
//     {
//         lcd.scrollDisplayRight();
//     }
//     else if (show == 12)
//     {
//         lcd.clear();
//         lcd.print("write-");
//     }
//     else if (show > 12)
//     {
//         lcd.print(show - 13);
//     } // if

//     delay(1400);
//     show = (show + 1) % 16;
// }