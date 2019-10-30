#include <Arduino.h>
#include <stdio.h>
#include "virtuabotixRTC.h"

// const int kCePin = 2;   // Chip Enable
// const int kIoPin = 3;   // Input/Output
// const int kSclkPin = 4; // Serial Clock

// const int kCePin = _defChipEnableRTC;   // Chip Enable
// const int kIoPin = _defIORTC;   // Input/Output
// const int kSclkPin = _defCLKRTC; // Serial Clock

virtuabotixRTC myrtc(CLK_RTC, IO_RTC, CE_RTC);
//virtuabotixRTC myrtc(kSclkPin, kIoPin, kCePin);



String getDate()
{
    myrtc.updateTime();

    String monthTmpStr;
    String dayTmpStr;
    String yearTmpStr = String(myrtc.year);
    if (myrtc.dayofmonth < 10)
    {
        dayTmpStr = "0" + String(myrtc.dayofmonth);
    }
    else
    {
        dayTmpStr = String(myrtc.dayofmonth);
    }

    if (myrtc.month < 10)
    {
        monthTmpStr = "0" + String(myrtc.month);
    }
    else
    {
        monthTmpStr = String(myrtc.month);
    }

    return dayTmpStr + "/" + monthTmpStr + "/" + yearTmpStr;
}

String getTime()
{
    myrtc.updateTime();
    String minTmpStr;
    String secTmpStr;
    String hourTmpStr;

    if (myrtc.hours < 10)
    {
        hourTmpStr = "0" + String(myrtc.hours);
    }
    else
    {
        hourTmpStr = String(myrtc.hours);
    }

    if (myrtc.minutes < 10)
    {
        minTmpStr = "0" + String(myrtc.minutes);
    }
    else
    {
        minTmpStr = String(myrtc.minutes);
    }

    if (myrtc.seconds < 10)
    {
        secTmpStr = "0" + String(myrtc.seconds);
    }
    else
    {
        secTmpStr = String(myrtc.seconds);
    }

    return hourTmpStr + ":" + minTmpStr + ":" + secTmpStr;
}

void setDateTime(int sec, int min, int hours, int dayWeek, int day, int month, int year)
{

    // seconds, minutes, hours, day of the week, day of the month, month, year
    //myrtc.setDS1302Time(00, 59, 23, 6, 10, 1, 2014);
    myrtc.setDS1302Time(sec, min, hours, dayWeek, day, month, year);
}
