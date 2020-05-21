#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
IRsend irsend; // IRSEND pin on my board is 3
decode_results results;
int counter = 0;
int interruptPin = 2;
boolean isAwake = true;

 void setup(){
  Serial.begin(115200);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode(interruptPin,INPUT_PULLUP);//Set pin d2 to input using the buildin pullup resistor

}

void loop(){
  if(digitalRead(2) == 0){
      isAwake = !isAwake;
   }
//Button   Hex
//Power   A90
//1   10
//2   810
//3   410
//4   C10
//5   210
//6   A10
//7   610
//8   E10
//9   110
//0   910
//Enter   D10
//Menu    70
//Channel Up  90
//Channel Down  890
//Volume Up 490
//Volume Down C90
//Mute    290
//Sleep   6D0

void sendNumber(int n){
  if (n == 1){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x10, 12); // Sony TV power code
      delay(40);
    }
  } else if (n == 2){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x810, 12); // Sony TV power code
      delay(40);
    }
  }else if (n == 3){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x410, 12); // Sony TV power code
      delay(40);
    }
  }else if (n == 4){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xC10, 12); // Sony TV power code
      delay(40);
    }
  }else if (n == 5){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x210, 12); // Sony TV power code
      delay(40);
    }
  }else if (n == 6){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xA10, 12); // Sony TV power code
      delay(40);
    }
  }else if (n == 7){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x610, 12); // Sony TV power code
      delay(40);
    }
  }else if (n == 8){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xE10, 12); // Sony TV power code
      delay(40);
    }
  }else if (n == 9){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x110, 12); // Sony TV power code
      delay(40);
    }
  }else if (n == 0){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x910, 12); // Sony TV power code
      delay(40);
    }
  }
}
