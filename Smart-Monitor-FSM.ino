/*
 * Project: Smart Environment Monitor & Security Station
 * Phase: 1.0 - LCD & FSM Initialization
 * Developer: Hasan Ali Kinas
 */

#include <LiquidCrystal.h>

// LCD Pin Definitons
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Finite State Machine (FSM) States
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
  
  // First Opening Screen
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM STARTING");
 
  
  delay(2000); // A short delaying
  currentState = MONITORING; // Switch the system to Monitoring Mode
  lcd.clear();
}

void loop() {
  switch(currentState) {
    case MONITORING:
      displayMonitoringStatus();
      break;
      
    case ARMED:
      // In the next stage
      break;
      
    case ALARM:
      // In the next stage
      break;

    case EMERGENCY:
      // In the next stage
      break;
  }
}

void displayMonitoringStatus() {
  lcd.setCursor(0, 0);
  lcd.print("Mode: MONITORING");
  lcd.setCursor(0, 1);
  lcd.print("Status: OK");
}
