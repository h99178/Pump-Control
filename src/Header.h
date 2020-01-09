
//func.h
void checkKeyboad();
int getPumpCalAddress(int pumpNumber);
int getPumpMilliliterAddress(int pumpNumber);
int getPumpTimesDayAddress(int pumpNumber);
int getPumpPin(int pumpNumber);
int calcRunTime(int hourStart, int minStart, int secStart, int hourEnd, int minEnd, int secEnd);
float getTimeNowSeconds();
bool checkTimeToDosing(int pumpNumber, int timesDay);
void runPumpDosing(int pumpDosingNumber);
void checkDosingPumpToRun();
void updateTimeDateLCD();
void interruptDosingPump();
void interruptRefillPump();
void inictialiationDosingPump();

//menu.h
void menuSelectPumpConfig();
void printTime(int caseMenu);
void editDate(String dateValue, uint8_t _ui8cursorPositionTmp);
void editTime(String dateValue, uint8_t _ui8cursorPositionTmp);
void editDateTime(int line);
void editPump(int line);
String funcPreareDate(int dayTmp, int monthTmp, int yearTmp);
String funcPreareTime(int hourTmp, int minTmp, int secTmp);
void menuEditDate();
void menuEditTime();
void printPumpRefill();
void menuEditPump1();
void menuEditPump2();
void callMenu(int menuNumber);
void callSelectedMenu(int menuNumber);
void menuMain();
void editPumpCal(uint8_t _ui8cursorPositionTmp);
void PumpCalLCD(uint8_t _ui8valueCalibrate, uint8_t pumpNumber);
void pumpCalibrate(uint8_t _ui8pumpNumber);
void menuSelectPumpCal();
void pumpConfigMilliliterLCD(uint8_t _ui8milliliter, uint8_t pumpNumber);
void pumpDosingDay(uint8_t _ui8timesDay, uint8_t pumpNumber);
void pumpConfigTimesDay(uint8_t _ui8pumpNumber);
void pumpConfigMilliter(uint8_t _ui8pumpNumber);
void menuSelectPumpConfig();
void pumpRunLCD(uint8_t pumpNumber, String status);
void pumpRun(uint8_t _ui8pumpNumber);
void menuSelectPumpRun();
void statusLCD();

//dateTime.h
String getDate();
String getTime();
void setDateTime(int sec, int min, int hours, int dayWeek, int day, int month, int year);

//kaypad.h
byte getKey();

//lcd.h
void lcdInit();
void printArrowLeft(int line, int cursor);
void printArrowRight(int line, int cursor);
void printArrowUp(int line, int cursor);
void printArrowDown(int line, int cursor);
void printLDCMessage(String msg, int cursor, int line, bool clean);

//pumpControll.h
void blinkLED(int value, int onoff);
void refillPumpStatusLCD(String status);
void pumpControl();