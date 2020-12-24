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
 * - D10 -> dot segment
 * - GND -> common cathode
 */

// one row per number
// one column per segment

const int DIGITS[20][8] = {
  /*0*/ {1,1,1,1,1,1,0,0},
  /*1*/ {0,1,1,0,0,0,0,0},
  /*2*/ {1,1,0,1,1,0,1,0},
  /*3*/ {1,1,1,1,0,0,1,0},
  /*4*/ {0,1,1,0,0,1,1,0},
  /*5*/ {1,0,1,1,0,1,1,0},
  /*6*/ {1,0,1,1,1,1,1,0},
  /*7*/ {1,1,1,0,0,0,0,0},
  /*8*/ {1,1,1,1,1,1,1,0},
  /*9*/ {1,1,1,1,0,1,1,0},
  /*10*/ {1,1,1,1,1,1,0,1},
  /*11*/ {0,1,1,0,0,0,0,1},
  /*12*/ {1,1,0,1,1,0,1,1},
  /*13*/ {1,1,1,1,0,0,1,1},
  /*14*/ {0,1,1,0,0,1,1,1},
  /*15*/ {1,0,1,1,0,1,1,1},
  /*16*/ {1,0,1,1,1,1,1,1},
  /*17*/ {1,1,1,0,0,0,0,1},
  /*18*/ {1,1,1,1,1,1,1,1},
  /*19*/ {1,1,1,1,0,1,1,1},
};

const int PIN_A_SEGMENT = 3;
const int PIN_BUTTON_A = 11; // add
const int PIN_BUTTON_B = 12; // extract
const int PIN_BUTTON_C = 2; // start
const int PIN_RELE = 13;
int buttonA;
int buttonB;
int buttonC;
int counter = 0;

void setup(){
  Serial.begin(9600);
  for (int i=0;i<=7;i++) {
    pinMode(i + PIN_A_SEGMENT, OUTPUT);
  }
  pinMode(PIN_BUTTON_A, INPUT_PULLUP); // button
  pinMode(PIN_BUTTON_B, INPUT_PULLUP); // button
  pinMode(PIN_BUTTON_C, INPUT_PULLUP); // button
  pinMode(PIN_RELE, OUTPUT); // rele
  pinMode(A1, OUTPUT); // speaker
  digitalWrite(PIN_RELE, LOW);
}
void printNumber(int num){
  for (int i=0;i<=7;i++){
     digitalWrite (i + PIN_A_SEGMENT, DIGITS[num][i]);
  }
}

void startTimer() {
  digitalWrite(A1, HIGH);
  delay(500);
  digitalWrite(A1, LOW);
  digitalWrite(PIN_RELE, HIGH);
  delay(counter*60*1000);
  digitalWrite(A1, HIGH);
  delay(500);
  digitalWrite(A1, LOW);
  digitalWrite(PIN_RELE, LOW);
  counter = 0;
}


void loop(){
  printNumber(counter);
  /*for (int i=0; i<=9; i++) {
    printNumber(i);
    delay(500);
  }*/
  buttonA = digitalRead(PIN_BUTTON_A);
  buttonB = digitalRead(PIN_BUTTON_B);
  buttonC = digitalRead(PIN_BUTTON_C);
  if (buttonA ==  LOW && counter > 0) {
    counter = (counter - 1) % 20;
  } else if (buttonB == LOW && counter < 20) {
    counter = (counter + 1) % 20;
  } else if (buttonC == LOW && counter>0) {
    startTimer();
  }
  Serial.println(counter);
  delay(100);  
}
