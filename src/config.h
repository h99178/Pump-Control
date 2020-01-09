//water leevl sensor olor diagram
//marrom - red vcc
//blue - black gnd
//amarelo - white signal
//preto - green gnd (vcc to high when detect water)

//*********************************************************************************************
//
// Select BOARD
//

#define ARDUINO_NANO //uncomment this line if using arduino NANO
//#define ARDUINO_UNO   ///uncomment this line if using arduino UNO

//
//#############################################################################################









//*********************************************************************************************
//
// Global Variables
//

bool systemStatus = false; //refill enable/disable
bool refillPumpRunning = false; //flag to indentify if the refill pump is running
long pumpRefillStartTime = 0;

float lastDosing[] = {0, 0, 0};
long timeDosingMillis[] = {0, 0, 0};
long timeStartDosing[] = {0, 0, 0};
bool dosginPumpRunning[] = {false, false, false}; //flag to indentify if the dosing pump is running
int timesRunningdosingPump[] = {0, 0, 0}; //count how many times the dosing pump was activated
int timesRunningResillPump = 0; //count how many times the refill pump was activated

long lastTimeUpdateLCD = 0; //store the last time update LCD time date
long timeCheckDosingPump = 0;

//
//#############################################################################################









//*********************************************************************************************
//
// Global Defines
//

#define PUMP_QUANTITY 3 //number of pumps
#define ANTI_FLOOD_TIMEOUT 3000 //anti flood timeout difined in milliseconds

//keyboard numbers
#define NONE 0        //none
#define LEFT 1        // left button
#define UP 2          // up button
#define RIGHT 3       //right button
#define DOWN 4        // down button
#define ENTER 5       // enter button
#define ESC 6         // esc button

//EEPROM address
#define PUMP_1_CALIBRATION 0 //address to store pump 1 calibration value
#define PUMP_2_CALIBRATION 1 //address to store pump 2 calibration value
#define PUMP_3_CALIBRATION 2 //address to store pump 3 calibration value

#define PUMP_1_MILLILITER 3 //address to store pump 1 milliliter value
#define PUMP_2_MILLILITER 4 //address to store pump 2 milliliter value
#define PUMP_3_MILLILITER 5 //address to store pump 3 milliliter value

#define PUMP_1_TIMESDAY 6 //address to store pump 1 times a day value
#define PUMP_2_TIMESDAY 7 //address to store pump 2 times a day value
#define PUMP_3_TIMESDAY 8 //address to store pump 3 times a day value

//
//#############################################################################################









//*********************************************************************************************
//
//Arduino NANO
//

#ifdef ARDUINO_NANO

#define SENSOR_PIN 3     // the number of the pushbutton pin
#define PUMP_PIN 2       //refill pump activation
#define LED_PIN 13       // the number of the LED pin
#define LED_STRIP_DATA 4 //led stip data
#define SELECT_BUTTON 5  //botao para controle

//clock RTC
#define CE_RTC 2  // Chip Enable RTC
#define IO_RTC 3  // Input/Output RTC
#define CLK_RTC 4 // Serial Clock RTC

//key board
#define KEYPAD_PIN A0 //keypad pin

//pumps pin
#define PUMP_1_PIN 7
#define PUMP_2_PIN 8
#define PUMP_3_PIN 9

#endif

//
//#############################################################################################









//*********************************************************************************************
//
//Arduino UNO
//

#ifdef ARDUINO_UNO

#define SENSOR_PIN D6     // the number of the pushbutton pin
#define PUMP_PIN D5       //pump activation
#define LED_PIN 13        // the number of the LED pin
#define LED_STRIP_DATA D7 //led stip data
#define SELECT_BUTTON D8  //botao para controle


//clock RTC
#define CE_RTC D2  // Chip Enable RTC
#define IO_RTC D3  // Input/Output RTC
#define CLK_RTC D4 // Serial Clock RTC

//key board
#define KEYPAD_PIN A0 //keypad pin

//pumps pin
#define PUMP_1_PIN 7
#define PUMP_2_PIN 8
#define PUMP_3_PIN 9

#endif

//
//#############################################################################################



// const byte NONE = 0;
// const byte LEFT = 1;
// const byte UP = 2;
// const byte RIGHT = 3;
// const byte DOWN = 4;
// const byte ENTER = 5;
// const byte ESC = 6;
