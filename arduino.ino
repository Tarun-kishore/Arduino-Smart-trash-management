#include <Servo.h>  //servo library

#include "model.h"

Servo servo;
int trigPin = 5;
int echoPin = 6;
int servoPin = 7;
long duration, dist, average;
int prediction;
float arr[1][16];
long aver[3];  //array for average


void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.write(0);  //close cap on power on
  delay(100);
  servo.detach();
  Serial.println("Start\n");
}

void measure() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = (duration / 2) / 29.1;  //obtain distance
}
void loop() {
  for (int i = 0; i <= 2; i++) {  //average distance
    measure();
    aver[i] = dist;
    delay(10);  //delay between measurements
  }
  dist = (aver[0] + aver[1] + aver[2]) / 3;
  prediction = predict(aver[0], aver[1], aver[2],arr);
  // Serial.print(aver[0]);
  // Serial.print(" ");
  // Serial.print(aver[1]);
  // Serial.print(" ");
  // Serial.print(aver[2]);
  // Serial.println("\n");
  // for(int i=0;i<1;i++){
        // for(int j=0;j<16;j++){
          // Serial.print(arr[i][j]);
          // Serial.print(" ");
        // }
        // Serial.println("\n");
      // }
  // prediction = 1;

  Serial.println(dist);
  Serial.println(prediction);

  if (prediction == 1) {
    servo.attach(servoPin);
    delay(1);
    servo.write(0); 
    delay(3000);
    servo.write(150);
    delay(1000);
    servo.detach();

  }
}