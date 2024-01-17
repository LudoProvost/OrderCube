#include <CapacitiveSensor.h>
CapacitiveSensor paySensor = CapacitiveSensor(4,6);
CapacitiveSensor serviceSensor = CapacitiveSensor(7,5);
long valPaySensor;
long valServiceSensor;
bool service; //1 is on
bool pay;
char currentState;  //I = idle, S = service, P = pay
int dutyCycle = 0;
int count = 0;
int blue_to_purple_time = 10000; //in millisecond
int avg_exec_time = 70;
int maxCount;

#define RED 3
#define GREEN 8
#define BLUE 2

void setup() {
  Serial.begin(9600);
  currentState = 'I';
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  maxCount = (blue_to_purple_time / 255) / avg_exec_time;
}

void loop() {
  //DEBUG INFO
//  Serial.print("       count: ");
//  Serial.print(count);
//  Serial.print("       dutyCycle: ");
//  Serial.print(dutyCycle);
//  Serial.print("    STATE: ");
//  Serial.print(currentState);
//  Serial.print("\n");
  
  valPaySensor = paySensor.capacitiveSensor(30);
  valServiceSensor = serviceSensor.capacitiveSensor(30);
  delay(50);

  currentState = updateCurrentState();

  updateOutputs();
}

void updateOutputs(){
  switch (currentState) {
    case 'i':
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      break;
    case 's':
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, HIGH);
      analogWrite(RED, dutyCycle);

      if (count >= maxCount && dutyCycle < 255) {
        dutyCycle += 1;
        count = 0;
      }
      if (dutyCycle < 255) {
        count += 1;
      }
      break;
    case 'p':
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      break;
    default:  //not efficient..
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
  }
}

char updateCurrentState(){
  switch (currentState) {
    case 'i':
      if (valServiceSensor >= 1000) {
        dutyCycle = 0;
        return 's';
      }
      else if (valPaySensor >= 1000) {
        return 'p';
      }
      else {
        return 'i';
      }
      break;
    case 's':
      if (valServiceSensor >= 1000) {
        return 'i';
      }
      else if (valPaySensor >= 1000) {
        return 'p';
      }
      else {
        return 's';
      }
      break;
    case 'p':
      if (valServiceSensor >= 1000) {
        dutyCycle = 0;
        return 's';
      }
      else if (valPaySensor >= 1000) {
        return 'i';
      }
      else {
        return 'p';
      }
      break;
    default:
      return 'i';
  }
}
