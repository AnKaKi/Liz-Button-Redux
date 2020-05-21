//For set up, plug the I/O pin on the buzzer into any number pin on the arduino and ground to ground
int soundPin = 9; //Pin that buzzer I/O is attached to 

void setup() {
  pinMode(soundPin, OUTPUT); //setting the predefined pin as the output for the buzzer
  beep(50);
  beep(50);
}

void loop() {
  
}

void beep(unsigned char delayMs){
  analogWrite(soundPin, 20); //Sets pin output to high (buzzer on)
  delay(delayMs); //The ammount of time the buzzer will sound. For the example it is 50 milliseconds
  analogWrite(soundPin, 0); //Sets pin output to low (buzzer off)
  delay(delayMs); // The ammount of time the buzzer will not sound. For this example it is the same amount of time as it is on
}
