/*
 * Project: Smart Environment Monitor & Security Station
 * Phase: 5.0 - Final Stable Integration
 * Developer: Hasan Ali Kinas
 * Features: Non-blocking stepper, Audio feedback, Temperature monitoring, IR Control
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Stepper.h>
#include <IRremote.hpp>

// LCD Setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Pin Definitions
const int trigPin = 7, echoPin = A2, irReceiverPin = A1;
const int tempPin = A5;   
const int buzzerPin = A3; 

// Stepper Setup
const int stepsPerRev = 2048;
Stepper myStepper(stepsPerRev, 8, 10, 9, A0);

enum SystemState { DISARMED, ARMING, MONITORING, ALARM };
SystemState currentState = DISARMED;

unsigned long lastSenseTime = 0, lastLCDTime = 0, armingStartTime = 0;
int currentDist = 0;
float temperature = 0.0;
int targetSteps = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK);
  myStepper.setSpeed(15);

  // Startup Sound
  digitalWrite(buzzerPin, HIGH); delay(100); digitalWrite(buzzerPin, LOW);

  lcd.print("STATION PHASE 5");
  delay(1000);
  lcd.clear();
}

void loop() {
  // 1. IR Remote Logic
  if (IrReceiver.decode()) {
    uint8_t cmd = IrReceiver.decodedIRData.command;
    if (cmd != 0) handleIR(cmd);
    IrReceiver.resume();
  }

  // 2. Non-blocking Stepper Movement
  if (targetSteps > 0) { 
    myStepper.step(1); targetSteps--; if(targetSteps == 0) releaseMotor(); 
  }
  else if (targetSteps < 0) { 
    myStepper.step(-1); targetSteps++; if(targetSteps == 0) releaseMotor(); 
  }

  // 3. Sensor & FSM Logic
  if (millis() - lastSenseTime > 450) {
    readSensors();
    
    if (currentState == ARMING && millis() - armingStartTime > 3000) {
      currentState = MONITORING;
      lcd.clear();
    }
    else if (currentState == MONITORING && currentDist > 0 && currentDist < 12) {
      triggerAlarmBuzz();
      currentState = ALARM;
      targetSteps = 512; 
      lcd.clear();
    }
    lastSenseTime = millis();
  }

  // 4. LCD Display Update
  if (millis() - lastLCDTime > 600) {
    updateDisplay();
    lastLCDTime = millis();
  }
}

void handleIR(uint8_t cmd) {
  if (cmd == 0x45 && currentState == DISARMED) { 
    currentState = ARMING; armingStartTime = millis(); lcd.clear();
  } else if (cmd == 0x46) { 
    currentState = DISARMED; targetSteps = -512; lcd.clear();
  }
}

void readSensors() {
  // Ultrasonic Distance
  digitalWrite(trigPin, LOW); delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 25000);
  currentDist = (duration == 0) ? 999 : duration * 0.034 / 2;

  // Stable Temperature Reading
  analogRead(tempPin); 
  delay(10);
  long tempSum = 0;
  for(int i=0; i<20; i++) {
    tempSum += analogRead(tempPin);
    delay(2);
  }
  temperature = ((tempSum / 20.0) * 5.0 * 100.0) / 1024.0;
}

void triggerAlarmBuzz() {
  digitalWrite(buzzerPin, HIGH); delay(400); digitalWrite(buzzerPin, LOW);
}

void releaseMotor() {
  digitalWrite(8, 0); digitalWrite(10, 0); digitalWrite(9, 0); digitalWrite(A0, 0);
}

void updateDisplay() {
  switch(currentState) {
    case DISARMED:
      lcd.setCursor(0,0); lcd.print("TEMP: "); lcd.print(temperature, 1); lcd.print("C     ");
      lcd.setCursor(0,1); lcd.print("PASSIVE [1:ARM]"); break;
    case ARMING:
      lcd.setCursor(0,0); lcd.print("SYSTEM ARMING...");
      lcd.setCursor(0,1); lcd.print("PLEASE WAIT...  "); break;
    case MONITORING:
      lcd.setCursor(0,0); lcd.print("DIST: "); lcd.print(currentDist); lcd.print("cm   ");
      lcd.setCursor(0,1); lcd.print("SAFE [2:DISARM] "); break;
    case ALARM:
      lcd.setCursor(0,0); lcd.print("!! INTRUDER !!  ");
      lcd.setCursor(0,1); lcd.print("2:RESET/UNLOCK  "); break;
  }
}
