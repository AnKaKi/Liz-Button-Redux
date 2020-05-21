#include <avr/sleep.h>

int buttonPin = 2;
boolean isSleeping = false;

void setup() {         
    Serial.begin(9600); 
    pinMode(buttonPin, INPUT_PULLUP);
    delay(100);
    Serial.println("I'm up...");
    
    attachInterrupt(digitalPinToInterrupt(buttonPin), toggleSleepState, LOW); //attaching wakeup to interrupt 0 on pin 2
    Serial.println("Attached");
}

void loop() {
    Serial.println(digitalRead(2));
    delay(1000);
//    int buttonState = digitalRead(buttonPin);
//    Serial.println(buttonState);
//    delay(1000);              // wait 1 sec
}

void toggleSleepState() {

    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    // If interrupts come faster than 20ms, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time > 200)
    {
        // toggle state of sleep
        isSleeping = !isSleeping;

        if (isSleeping == true) {
            Serial.println("goToSleep");
            goToSleep();
        }
        else {
            Serial.println("wakeUp");
            wakeUp();
        }
    }
    last_interrupt_time = interrupt_time;
}

void goToSleep() {
    detachInterrupt(digitalPinToInterrupt(2));
    Serial.println("Power Button pressed...");
    Serial.flush();    
    Serial.println("Hi");
    Serial.flush();

    sleep_enable(); // only enabling sleep mode, nothing more
    Serial.println("HI");
    Serial.flush();

    set_sleep_mode(SLEEP_MODE_PWR_DOWN); // setting sleep mode to max pwr saving    
    Serial.println("ok");
    Serial.flush();
    attachInterrupt(digitalPinToInterrupt(buttonPin), toggleSleepState, LOW); //attaching wakeup to interrupt 0 on pin 2

    sleep_mode();
    Serial.println("Checkpoint!"); // gets executed after interrupt
    Serial.flush();
    sleep_disable();
    detachInterrupt(0);
    Serial.println("Ok");
}

void wakeUp () {
    detachInterrupt(digitalPinToInterrupt(2));
    Serial.println("Wakeup Interrupt Fired");
    attachInterrupt(digitalPinToInterrupt(buttonPin), toggleSleepState, LOW); //attaching wakeup to interrupt 0 on pin 2
}
