const int DigiPin = 2;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(DigiPin, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(DigiPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(5000);                       // wait for a second
  digitalWrite(DigiPin, LOW);    // turn the LED off by making the voltage LOW
  delay(2000);                       // wait for a second
}
