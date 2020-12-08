/**
 * Components:
 * - seven segment display 5611AH
 * - 2x 220 Ohm resistors
 * 
 * Pinout
 * - D3 -> B segment
 * - D4 -> A segment
 * - D5 -> F segment
 * - D6 -> G segment
 * - D7 -> C segment
 * - D8 -> D segment
 * - D9 -> E segment
 * - GND -> common cathode
 */

const int DIGITS[10][7] = {
  /*0*/ {1,1,1,1,1,1,0},
  /*1*/ {0,1,1,0,0,0,0},
  /*2*/ {1,1,0,1,1,0,1},
  /*3*/ {1,1,1,1,0,0,1},
  /*4*/ {0,1,1,0,0,1,1},
  /*5*/ {1,0,1,1,0,1,1},
  /*6*/ {1,0,1,1,1,1,1},
  /*7*/ {1,1,1,0,0,0,0},
  /*8*/ {1,1,1,1,1,1,1},
  /*9*/ {1,1,1,1,0,1,1}
};

const int PIN_A_SEGMENT = 3;
const int PIN_BUTTON_A = 10;
int buttonA = 0;
int counter = 0;

void setup(){
  Serial.begin(9600);
  for (int i=0;i<=6;i++) {
    pinMode(i + PIN_A_SEGMENT, OUTPUT);
  }
  pinMode(PIN_BUTTON_A, INPUT_PULLUP); // button
}
void printNumber(int num){
  for (int i=0;i<=6;i++){
     digitalWrite (i + PIN_A_SEGMENT, DIGITS[num][i]);
  }
}
void loop(){
  printNumber(counter % 9);
  /*for (int i=0; i<=9; i++) {
    printNumber(i);
    delay(500);
  }*/
  buttonA = digitalRead(PIN_BUTTON_A);
  if (buttonA ==  LOW) {
    counter++;
  }
  delay(100);  
}
