#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
IRsend irsend; // IRSEND pin on my board is 3
decode_results results;

 void setup(){
  Serial.begin(115200);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
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
   for (int i = 0; i < 3; i++) {
      irsend.sendSony(0xa90, 12); // Sony TV power code
      delay(40);
    }
    delay(1000);
}
