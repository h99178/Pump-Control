
//marrom - red vcc
//blue - black gnd
//amarelo - white signal
//preto - green gnd (vcc to high when detect water)

#define SENSOR_PIN       3 // the number of the pushbutton pin
#define PUMP_PIN         2 //pump activation
#define LED_PIN          13 // the number of the LED pin
#define LED_STRIP_DATA    4 //led stip data
#define SELECT_BUTTON    5 //botao para controle
#define TIME_OUT_PUMP       10 //time to avoid pump flood 10 ~= 3 seconds
#define COUNTER_ANTI_FLOOD  0//count for pump timer anti-flood


//clock RTC 
#define CE_RTC           2   // Chip Enable RTC
#define IO_RTC           3   // Input/Output RTC
#define CLK_RTC          4   // Serial Clock RTC

//key board 
#define KEYPAD_PIN       A0 //keypad pin
#define NONE        0 //none 
#define LEFT        1 // left button
#define UP          2 // up button
#define RIGHT       3 //right button
#define DOWN        4 // down button
#define ENTER       5 // enter button
#define ESC         6 // esc button


int counter = COUNTER_ANTI_FLOOD; //count for pump timer anti-flood
bool systemStatus = false; //refill enable/disable


// const byte NONE = 0;
// const byte LEFT = 1;
// const byte UP = 2;
// const byte RIGHT = 3;
// const byte DOWN = 4;
// const byte ENTER = 5;
// const byte ESC = 6;


