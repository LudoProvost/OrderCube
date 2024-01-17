int pwmPin = 9;
int dutyCycle = 0;

// LED should slowly get brighter. wait, then dim, and repeat.

void setup() {
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  for (int i = 0; i <= 255; i++) {
    dutyCycle = i;
    analogWrite(pwmPin, dutyCycle);
    delay(10);  // Adjust as needed for the desired speed
  }

  delay(1000);  // Optional pause

  for (int i = 255; i >= 0; i--) {
    dutyCycle = i;
    analogWrite(pwmPin, dutyCycle);
    delay(10);  // Adjust as needed for the desired speed
  }

  delay(1000);  // Optional pause
}
