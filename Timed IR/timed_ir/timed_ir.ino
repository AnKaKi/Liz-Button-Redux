#include <Adafruit_ESP8266.h>

#include <Wire.h>
#include <ds3231.h>
#include <IRremote.h>
 
struct ts t; 
const int RECV_PIN = 7;
int counter = 0;
int soundPin = 9;
int interruptPin = 2;
IRrecv irrecv(RECV_PIN);
IRsend irsend; // IRSEND pin on my board is 3
decode_results results;
boolean isAwake;

 void setup(){
  Serial.begin(115200);
  irrecv.enableIRIn();
  irrecv.blink13(true);
  

  pinMode(interruptPin,INPUT_PULLUP);//Set pin d2 to input using the buildin pullup resistor

  Serial.begin(115200);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  
  /*----------------------------------------------------------------------------
  In order to synchronise your clock module, insert timetable values below !
  ----------------------------------------------------------------------------*/
  t.hour=3; 
  t.min=57;
  t.sec=17;
  t.mday=5;
  t.mon=21;
  t.year=2020;
 
  DS3231_set(t); 
  
  pinMode(soundPin, OUTPUT); //setting the predefined pin as the output for the buzzer

  isAwake = true;
}

void loop(){
  if(digitalRead(interruptPin) == 0){
    isAwake = !isAwake;
    if(isAwake == true){
      Serial.println("Awake");
    } else{
      Serial.println("Sleeping");
    }
  }
  if(isAwake == true){
    
    DS3231_get(&t);
    Serial.print("Date : ");
    Serial.print(t.mday);
    Serial.print("/");
    Serial.print(t.mon);
    Serial.print("/");
    Serial.print(t.year);
    Serial.print("\t Hour : ");
    Serial.print(t.hour);
    Serial.print(":");
    Serial.print(t.min);
    Serial.print(".");
    Serial.println(t.sec);
    delay(1000);
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
  
    if(t.hour == 3 && t.min == 50 && t.sec == 5){
      Serial.println("Transmitting: 123");
      sendNumber(1);
      sendNumber(2);
      sendNumber(3);
      beep(100);
    } 
    if(t.hour == 3 && t.min == 50 && t.sec == 10){
      Serial.println("Transmitting: 456");
      sendNumber(4);
      sendNumber(5);
      sendNumber(6);
      beep(100);
     }
    }
    else{
        delay(1000);
    }

}


void sendNumber(int n){
  if (n == 1){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x10, 12); // Sony 1
      delay(40);
    }
  } else if (n == 2){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x810, 12); // Sony 2
      delay(40);
    }
  }else if (n == 3){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x410, 12); // Sony 3
      delay(40);
    }
  }else if (n == 4){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xC10, 12); // Sony 4
      delay(40);
    }
  }else if (n == 5){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x210, 12); // Sony 5
      delay(40);
    }
  }else if (n == 6){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xA10, 12); // Sony 6
      delay(40);
    }
  }else if (n == 7){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x610, 12); // Sony 7
      delay(40);
    }
  }else if (n == 8){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xE10, 12); // Sony 8
      delay(40);
    }
  }else if (n == 9){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x110, 12); // Sony 9
      delay(40);
    }
  }else if (n == 0){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0x910, 12); // Sony 0
      delay(40);
    }
  }
}


void beep(unsigned char delayMs){
  analogWrite(soundPin, 20); //Sets pin output to high (buzzer on)
  delay(delayMs); //The ammount of time the buzzer will sound. For the example it is 50 milliseconds
  analogWrite(soundPin, 0); //Sets pin output to low (buzzer off)
  delay(delayMs); // The ammount of time the buzzer will not sound. For this example it is the same amount of time as it is on
}
