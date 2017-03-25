#include <Arduino.h>

/**
 * PID control tutorial
 *
 * Motor driver connected to D6-D7
 * Encoder connected to D2
 */

#define ENCODER 2
#define MOTORA1 6
#define MOTORA2 7

volatile long counter = 0;
int pwm = 10;

void count() {
    counter++;
}

void setup() {
  Serial.begin(9600);
  pinMode(ENCODER, INPUT_PULLUP);
  pinMode(MOTORA1, OUTPUT);
  pinMode(MOTORA2, OUTPUT);

  analogWrite(MOTORA1, pwm);
  digitalWrite(MOTORA2, LOW);

  attachInterrupt(digitalPinToInterrupt(ENCODER), count, RISING);

  delay(500);
}

int setPoint = 15;

void loop() {
    Serial.print("SP:");
    Serial.print(setPoint);
    Serial.print(",");
    Serial.print("PWM:");
    Serial.print(pwm);
    Serial.print(",");
    Serial.print("counter:");
    Serial.println(counter);

    int err = setPoint - counter;

    pwm += err;

    analogWrite(MOTORA1, pwm);

    counter = 0;

    delay(500);
}
