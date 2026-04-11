/*
 * Project: Smart Environment Monitor & Security Station
 * Phase: 2.0 - Distance Sensing & State Transition
 * Developer: Hasan Ali Kinas
 */

#include <LiquidCrystal.h>

// LCD Pin Definitions
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Sensor Pin Definitions
const int trigPin = 9;
const int echoPin = 10;

// FSM States
enum SystemState {
  STARTUP,
  MONITORING,
  ARMED,
  ALARM,
  EMERGENCY
};

SystemState currentState = STARTUP;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  // Hardware Pin Configuration
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
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
      // Trigger Alarm if an object is closer than 10cm
      if (currentDistance > 0 && currentDistance < 10) {
        currentState = ALARM;
        lcd.clear();
      }
      break;
      
    case ALARM:
      handleAlarmState();
      break;
      
    case ARMED:
      // To be implemented in next phase
      break;

    case EMERGENCY:
      // To be implemented in next phase
      break;
  }
  
  delay(100); // Stability delay for LCD refresh
}

// Function to calculate distance using HC-SR04 physics logic
int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  // Distance Calculation: (Time * Speed of Sound) / 2
  // v = 0.034 cm/us
  int distanceCm = duration * 0.034 / 2;
  return distanceCm;
}

void handleMonitoringState(int dist) {
  lcd.setCursor(0, 0);
  lcd.print("Dist: ");
  lcd.print(dist);
  lcd.print(" cm    "); // Clear old digits
  
  lcd.setCursor(0, 1);
  lcd.print("Status: SECURE ");
}

void handleAlarmState() {
  lcd.setCursor(0, 0);
  lcd.print("!! INTRUDER !!");
  lcd.setCursor(0, 1);
  lcd.print("STATE: ALARM   ");
}
