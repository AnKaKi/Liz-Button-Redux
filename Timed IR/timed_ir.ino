#include <Adafruit_ESP8266.h>

#include <Wire.h>
#include <ds3231.h>
#include <IRremote.h>
 
struct ts t; 
const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
IRsend irsend; // IRSEND pin on my board is 3
decode_results results;

 void setup(){
  Serial.begin(115200);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  Serial.begin(115200);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);
  
  /*----------------------------------------------------------------------------
  In order to synchronise your clock module, insert timetable values below !
  ----------------------------------------------------------------------------*/
  t.hour=9; 
  t.min=0;
  t.sec=0;
  t.mday=10;
  t.mon=4;
  t.year=2020;
 
  DS3231_set(t); 
}

void loop(){
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
  // Can read the code of IR input
  // if (irrecv.decode(&results)) {
  //   if (results.decode_type == NEC) {
  //     Serial.print("NEC: ");
  //   } else if (results.decode_type == SONY) {
  //     Serial.print("SONY: ");
  //   } else if (results.decode_type == RC5) {
  //     Serial.print("RC5: ");
  //   } else if (results.decode_type == RC6) {
  //     Serial.print("RC6: ");
  //   } else if (results.decode_type == UNKNOWN) {
  //     Serial.print("UNKNOWN: ");
  //   }
  //   Serial.println(results.value, HEX);
  //   Serial.println(results.value);
  //   irrecv.resume(); // Receive the next value
  // }
  if(t.hour == 9 && t.min == 0 && t.sec == 10){
    for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xa90, 12); // Sony TV power code
      delay(40);
    }
  }
}
