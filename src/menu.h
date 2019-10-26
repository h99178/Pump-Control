#include "lcd.h"
#include "dateTime.h"

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
            while (getKey() != RIGHT)
            {
                /* code */
            }
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
            while (getKey() != LEFT)
            {
                /* code */
            }
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
            while (getKey() != UP)
            {
                /* code */
            }
        }

        if (keyValeuStr == DOWN)
        {
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
            while (getKey() != DOWN)
            {
                /* code */
            }
        }

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
            setDateTime(secTmp, minTmp, hourTmp, 1, dayTmp, monthTmp, yearTmp);
            while (getKey() == ENTER)
            {
                /* code */
            }
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

        //editDate(funcPreareDate(dayTmp, monthTmp, yearTmp), _ui8cursorPosition);
        //delay(100);
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
            while (getKey() == RIGHT)
            {
                Serial.println("Right " + String(_ui8cursorPosition));
                delay(100);
            }

            if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 7;
            }
            else if (_ui8cursorPosition == 1)
            {
                _ui8cursorPosition = 4;
            }
        }

        if (keyValeuStr == LEFT)
        {
            while (getKey() == LEFT)
            {
                Serial.println("Left " + String(_ui8cursorPosition));
                delay(100);
            }

            if (_ui8cursorPosition == 7)
            {
                _ui8cursorPosition = 4;
            }
            else if (_ui8cursorPosition == 4)
            {
                _ui8cursorPosition = 1;
            }
        }

        if (keyValeuStr == UP)
        {
            while (getKey() == UP)
            {
                /* code */
            }
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
        }

        if (keyValeuStr == DOWN)
        {
            while (getKey() == DOWN)
            {
                /* code */
            }

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
        }

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
            setDateTime(secTmp, minTmp, hourTmp, 1, dayTmp, monthTmp, yearTmp);
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
        counter = 0;

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
        menuEditPump2();
        break;

    default:
        break;
    }
}

void menuMain()
{
    int pageNumber = 1;
    int numberOfmenu = 4; //quantidade de menus na funcao callMenu()

    while (pageNumber != 0)
    {
        while (getKey() != NONE)
        {
            /* code */
        }

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
    }
}