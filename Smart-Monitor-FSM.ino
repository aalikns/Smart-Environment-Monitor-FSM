/*
 * Project: Smart Environment Monitor & Security Station
 * Phase: 4.9 - Logic Validation & FSM Stability
 * Status: STABLE (Motor Disabled for Debugging)
 * Developer: Hasan Ali Kinas
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <IRremote.hpp> 

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int trigPin = 7;
const int echoPin = A2; 
const int irReceiverPin = A1;

#define CMD_1 0x45 // ARM
#define CMD_2 0x46 // DISARM / RESET

enum SystemState { DISARMED, MONITORING, ALARM };
SystemState currentState = DISARMED;

unsigned long lastSenseTime = 0;
unsigned long lastLCDTime = 0;
int currentDist = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  IrReceiver.begin(irReceiverPin, ENABLE_LED_FEEDBACK);
  
  lcd.print("LOGIC TEST 4.9");
  delay(1000); 
  lcd.clear();
}

void loop() {
  if (IrReceiver.decode()) {
    uint8_t cmd = IrReceiver.decodedIRData.command;
    if (cmd != 0) {
      handleIR(cmd);
    }
    IrReceiver.resume();
  }

  switch(currentState) {
    case DISARMED:
      updateLCD("STATUS: PASSIVE", "PRESS 1 TO ARM");
      break;
    case MONITORING:
      if (millis() - lastSenseTime > 300) {
        currentDist = readDistance();
        updateLCD("Dist: " + String(currentDist) + " cm", "Status: ARMED");
        if (currentDist > 0 && currentDist < 12) { 
          currentState = ALARM;
          lcd.clear();
        }
        lastSenseTime = millis();
      }
      break;
    case ALARM:
      updateLCD("!! INTRUDER !!", "PRESS 2 TO RESET");
      break;
  }
}

void handleIR(uint8_t cmd) {
  if (cmd == CMD_1 && currentState == DISARMED) {
    currentState = MONITORING;
    lcd.clear();
  } else if (cmd == CMD_2) {
    currentState = DISARMED;
    lcd.clear();
  }
}

int readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 25000); 
  if (duration == 0) return 999;
  return duration * 0.034 / 2;
}

void updateLCD(String l1, String l2) {
  if (millis() - lastLCDTime > 500) {
    lcd.setCursor(0, 0);
    lcd.print(l1 + "                ");
    lcd.setCursor(0, 1);
    lcd.print(l2 + "                ");
    lastLCDTime = millis();
  }
}
