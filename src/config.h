
//marrom - red vcc
//blue - black gnd
//amarelo - white signal
//preto - green gnd (vcc to high when detect water)

#define _defDensorPin 3;    // the number of the pushbutton pin
#define _defPumpPin 2;      //pump activation
#define _defLedPin 13;      // the number of the LED pin
#define _defLedStripData 4; //led stip data
#define _defSelectButton 5; //botao para controle
#define _defTimeOutPump 10; //time to avoid pump flood 10 ~= 3 seconds
#define _defCounterAntiFlood 0;//count for pump timer anti-flood





const int sensorPin = _defDensorPin; // the number of the pushbutton pin
const int pumpPin = _defPumpPin;      //pump activation
const int ledPin = _defLedPin;      // the number of the LED pin
const int ledStripData = _defLedStripData; //led stip data
const int selectButton = _defSelectButton; //botao para controle
const int timePump = _defTimeOutPump; //time to avoid pump flood 10 ~= 3 seconds
int counter = _defCounterAntiFlood; //count for pump timer anti-flood
bool systemStatus = false; //refill enable/disable


const byte keypadPin = A0;

const byte NONE = 0;
const byte LEFT = 1;
const byte UP = 2;
const byte RIGHT = 3;
const byte DOWN = 4;
const byte ENTER = 5;
const byte ESC = 6;


