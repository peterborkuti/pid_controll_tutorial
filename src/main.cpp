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
int pwm = 0;

void count() {
    counter++;
}

void setPWM() {
    pwm = random(100, 255);
    analogWrite(MOTORA1, pwm);
}

void setup() {
  Serial.begin(9600);
  pinMode(ENCODER, INPUT_PULLUP);
  pinMode(MOTORA1, OUTPUT);
  pinMode(MOTORA2, OUTPUT);

  digitalWrite(MOTORA2, LOW);
  setPWM();

  attachInterrupt(digitalPinToInterrupt(ENCODER), count, RISING);
}

void loop() {
    Serial.print(pwm);
    Serial.print(",");
    Serial.println(counter);

    counter = 0;

    if (random(100) < 30) {
        setPWM();
    }

    delay(500);
}
