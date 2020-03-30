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
  if (irrecv.decode(&results)){
        Serial.println(results.decode_type);
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
}
