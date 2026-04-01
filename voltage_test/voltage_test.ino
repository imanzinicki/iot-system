#include <Servo.h>

#define TRIG 9
#define ECHO 10

#define RED 3
#define GREEN 4
#define BLUE 5

#define BUZZER 7

Servo myServo;

long duration;
int distance;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  pinMode(BUZZER, OUTPUT);

  myServo.attach(6);

  Serial.begin(9600);
}

int getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);
  distance = duration * 0.034 / 2;

  return distance;
}

void handleAlert(int d) {
  if (d > 50) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(BUZZER, LOW);
  } 
  else if (d > 20) {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
    digitalWrite(BUZZER, millis() % 300 < 150);
  } 
  else {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(BUZZER, millis() % 150 < 75);
  }
}

void loop() {
  for (int angle = 0; angle <= 180; angle += 8) {
    myServo.write(angle);

    int d = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(d);

    handleAlert(d);

    delay(100);
  }

  for (int angle = 180; angle >= 0; angle -= 8) {
    myServo.write(angle);

    int d = getDistance();

    Serial.print(angle);
    Serial.print(",");
    Serial.println(d);

    handleAlert(d);

    delay(100);
  }
}