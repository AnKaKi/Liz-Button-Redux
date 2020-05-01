const int buttonPin = 5;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(buttonPin, INPUT);

}

void loop() {
    buttonState = digitalRead(buttonPin);
    if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
    } else {
    // turn LED off:
    digitalWrite(LED_BUILTIN, LOW);
    }
}