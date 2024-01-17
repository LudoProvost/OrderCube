#include <CapacitiveSensor.h>
CapacitiveSensor Sensor = CapacitiveSensor(4,6);
long val;
bool pos; //true means on
int dutyCycle = 0;
int count = 0;

#define led 9

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  val = Sensor.capacitiveSensor(30);
  Serial.print("pos: ");
  Serial.print(pos);
  Serial.print("       count: ");
  Serial.print(count);
  Serial.print("       dutyCycle: ");
  Serial.print(dutyCycle);
  Serial.print("\n");
  if (val >= 1000 && !pos) {
    count = 0;  //resets counter
    dutyCycle = 0;  //resets duty cycle
    pos = !pos;
    delay(25);
  }
  else if (val >= 1000 && pos) {
    digitalWrite(led, LOW);
    pos = !pos;
    delay(25);
  }
  
  if (pos){
    analogWrite(led, dutyCycle);
    if (count >= 2 && dutyCycle < 255) {      //count is the number of 10ms delays encountered, 23 for 230ms
      dutyCycle += 1;     //inc dutyCycle
      count = 0;      // restart count
    }
    if (dutyCycle < 255) {
      count += 1; //inc count
    }
  }

  delay(10);
}

void gradualDimming() {
  for (int i = 0; i <= 255; i++) {
    if (Sensor.capacitiveSensor(30) >= 1000) {
      pos = !pos;
      return;
    }
    dutyCycle = i;
    analogWrite(led, dutyCycle);
    delay(20); //for gradual dimming over 60sec
  }
  return;
}
