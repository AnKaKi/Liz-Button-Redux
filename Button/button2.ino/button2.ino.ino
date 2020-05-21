//#include <avr/sleep.h>
//
//int buttonPin = 2;
//boolean isSleeping = false;
//
//void setup() {         
//    Serial.begin(9600); 
//    pinMode(buttonPin, INPUT_PULLUP);
//    delay(100);
//    Serial.println("I'm up...");
//    Serial.println(digitalRead(2));
//    attachInterrupt(digitalPinToInterrupt(buttonPin), goToSleep, LOW); //attaching wakeup to interrupt 0 on pin 2
//    delay(1000);
////    detachInterrupt(0);
//}
//
//void loop() {
//  Serial.println("Awake");
////    int buttonState = digitalRead(buttonPin);
////    Serial.println(buttonState);
////    delay(1000);              // wait 1 sec
//}
//
//void goToSleep() {
//    Serial.println("Power Button pressed...");
//    Serial.flush();
//    detachInterrupt(0);
//    sleep_enable(); // only enabling sleep mode, nothing more
//    attachInterrupt(0,wakeUp, LOW); 
//    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // setting sleep mode to max pwr saving
//   
//    sleep_mode();
//    Serial.println("Checkpoint!"); // gets executed after interrupt
//    Serial.flush();
//    sleep_disable();
//    detachInterrupt(0);
//    Serial.println("Ok");
//}
//
//void wakeUp () {
//    Serial.println("Wakeup Interrupt Fired");
//    attachInterrupt(0,goToSleep, LOW); 
//    detachInterrupt(0);
//
//}

#include <avr/sleep.h>//this AVR library contains the methods that controls the sleep modes
#define interruptPin 2 //Pin we are going to use to wake up the Arduino

boolean isAwake = false;
int soundPin = 9; //Pin that buzzer I/O is attached to 


void setup() {
  Serial.begin(9600);//Start Serial Comunication
  pinMode(LED_BUILTIN,OUTPUT);//We use the led on pin 13 to indecate when Arduino is asleep
  pinMode(interruptPin,INPUT_PULLUP);//Set pin d2 to input using the buildin pullup resistor
  digitalWrite(LED_BUILTIN,HIGH);//turning LED on
  
//   delay(1000);//wait 5 seconds before going to sleep
   Going_To_Sleep();
   pinMode(soundPin, OUTPUT); //setting the predefined pin as the output for the buzzer
    beep(50);
    beep(50);
}

void loop() {
  
  Serial.println(isAwake);
  Serial.flush();
  Serial.println(digitalRead(2));
  Serial.flush();

  if(isAwake == true && digitalRead(2) == 0){
      Serial.println("Made it");
      Going_To_Sleep();
  }
  delay(100);
}

void Going_To_Sleep(){
    isAwake = false;
    sleep_enable();//Enabling sleep mode
    Serial.println("Sleeping");

    attachInterrupt(0, wakeUp, FALLING);//attaching a interrupt to pin d2

    if(isAwake == false){
      Serial.println("false");
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);//Setting the sleep mode, in our case full sleep
      digitalWrite(LED_BUILTIN,LOW);//turning LED off
      delay(100); //wait a second to allow the led to be turned off before going to sleep
      sleep_cpu();//activating sleep mode
      Serial.println("just woke up!");//next line of code executed after the interrupt 
      Serial.flush();
  //    digitalWrite(LED_BUILTIN,HIGH);//turning LED on
      detachInterrupt(0);
   } else{
        Serial.println("true");
        beep(1000);

   }
    
  }

void wakeUp(){
  Serial.println("Interrupt Fired");//Print message to serial monitor
  beep(100);
  sleep_disable();//Disable sleep mode
  isAwake = true;

  Serial.println("HI");
//  detachInterrupt(0); //Removes the interrupt from pin 2;
}

void beep(unsigned char delayMs){
  analogWrite(soundPin, 20); //Sets pin output to high (buzzer on)
  delay(delayMs); //The ammount of time the buzzer will sound. For the example it is 50 milliseconds
  analogWrite(soundPin, 0); //Sets pin output to low (buzzer off)
  delay(delayMs); // The ammount of time the buzzer will not sound. For this example it is the same amount of time as it is on
}
