/*
 * Project: Smart Environment Monitor & Security Station
 * Phase: 3.1 - Conflict-Free Hardware Integration
 * Developer: Hasan Ali Kinas
 */

#include <LiquidCrystal.h>
#include <Stepper.h>

// LCD Pin Definitions (Kept original as requested)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Sensor & Actuator Pin Definitions
const int trigPin = 7;
const int echoPin = 13;
const int buzzerPin = 6;

// Stepper Configuration (Using A0 as a digital pin to avoid conflict with LCD Pin 11)
const int stepsPerRevolution = 4096;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, A0); 

enum SystemState { STARTUP, MONITORING, ARMED, ALARM, EMERGENCY };
SystemState currentState = STARTUP;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  // Initialize Stepper
  myStepper.setSpeed(2); // 10 RPM
  
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM STARTING");
  
  delay(1500); 
  currentState = MONITORING; 
  lcd.clear();
}

void loop() {
  int currentDistance = readDistance();

  switch(currentState) {
    case MONITORING:
      handleMonitoringState(currentDistance);
      if (currentDistance > 0 && currentDistance < 10) {
        currentState = ALARM;
        lcd.clear();
        lockMechanism(); // Move stepper once upon state change
      }
      break;
      
    case ALARM:
      handleAlarmState();
      playAlarmSound(); 
      break;
  }
  delay(50);
}

int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void lockMechanism() {
  // Rotate 90 degrees to simulate a security lock
  myStepper.step(512); 
}

void playAlarmSound() {
  // Alert sound using PWM frequency sweeping
  for (int hz = 440; hz < 1000; hz += 25) {
    tone(buzzerPin, hz, 20);
    delay(5);
  }
}

void handleMonitoringState(int dist) {
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(dist);
  lcd.print(" cm    ");
  lcd.setCursor(0, 1);
  lcd.print("Status: SECURE ");
  noTone(buzzerPin);
}

void handleAlarmState() {
  lcd.setCursor(0, 0);
  lcd.print("!! INTRUDER !!");
  lcd.setCursor(0, 1);
  lcd.print("LOCK ENGAGED   ");
}
