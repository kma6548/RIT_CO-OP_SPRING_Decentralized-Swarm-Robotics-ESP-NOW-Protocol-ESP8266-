#include <ESP8266WiFi.h>

// Motor control pins
const int motor1Pin1 = 14;// D5  
const int motor1Pin2 = 12; // D6
const int motor2Pin1 = 13;// D7
const int motor2Pin2 = 15; // D8  
//Ultrasonic pins
const int trigPin = 5; //D1
const int echoPin = 4;  //D2
//define sound velocity in cm/uS 
#define SOUND_VELOCITY 0.034
long duration;
float distanceCm;
int flag = 0;
void setup() {
  Serial.begin(115200);

  // Set motor control pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() { 
  moveForward();
  //Checking for obstacle

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  if(distanceCm <= 6.0)
  {
    Serial.print("Obstacle detected");
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);
    flag = 1;
    stopMotors();
    delay(2000);
  }
  if(flag == 1)
  {
    moveLeft();
    delay(1000);
    flag = 0;
    moveForward();
  }
  // Example: Move the motors forward for 2 seconds
  // Serial.print("1");
  // moveForward();
  // Serial.print("2");
  // delay(2000);

  // // Stop the motors for 1 second
  // Serial.print("3");
  // stopMotors();
  // Serial.print("4");
  // delay(1000);

  // // Example: Move the motors backward for 2 seconds
  // moveBackward();
  // delay(2000);

  // // Stop the motors for 1 second
  // stopMotors();
  // delay(1000);

  // // Example: Move the motors left for 2 seconds
  // moveLeft();
  // delay(2000);
}

// Function to move motors forward
void moveBackward() {
  digitalWrite(motor1Pin1, HIGH); // Motor 1 forward
  digitalWrite(motor1Pin2, LOW);  // Motor 2 forward
  digitalWrite(motor2Pin1, HIGH); // Motor 1 forward
  digitalWrite(motor2Pin2, LOW);
}

// Function to move motors backward
void moveForward() {
  digitalWrite(motor1Pin1, LOW); // Motor 1 forward
  digitalWrite(motor1Pin2, HIGH);  // Motor 2 forward
  digitalWrite(motor2Pin1, LOW); // Motor 1 forward
  digitalWrite(motor2Pin2, HIGH);  // Motor 2 forward
}
 
// Function to move motors left
void moveLeft() {
  digitalWrite(motor1Pin1, LOW); // Motor 1 forward
  digitalWrite(motor1Pin2, LOW);  // Motor 2 forward
  digitalWrite(motor2Pin1, LOW); // Motor 1 forward
  digitalWrite(motor2Pin2, HIGH);  // Motor 2 forward
}

// Function to move motors right
void moveRight() {
  digitalWrite(motor1Pin1, LOW); // Motor 1 forward
  digitalWrite(motor1Pin2, HIGH);  // Motor 2 forward
  digitalWrite(motor2Pin1, LOW); // Motor 1 forward
  digitalWrite(motor2Pin2, LOW);  // Motor 2 forward
}

// Function to stop motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);  // Motor 1 stopped
  digitalWrite(motor1Pin2, LOW);  // Motor 2 stopped
  digitalWrite(motor2Pin1, LOW);  // Motor 1 stopped
  digitalWrite(motor2Pin2, LOW);  // Motor 2 stopped
}
 