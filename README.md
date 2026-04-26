## Smart Environment Monitor & Security Station

This project is a high-reliability **Finite State Machine (FSM)** based embedded system developed using Arduino. It integrates real-time environmental monitoring with a mechanical security layer, optimized for responsiveness and thermal stability.

## Phase 5.0: Final Integrated Build
The system has evolved from a basic FSM to a fully integrated station that resolves common embedded systems conflicts such as blocking I/O and voltage fluctuations.

## 🛠 Technical Specifications
- **Architecture:** Modular C++ implementation utilizing a deterministic Finite State Machine (FSM) for predictable state transitions.
- **Non-blocking Actuation:** A custom "Time-Slicing" stepper logic is implemented to ensure the **IR Receiver** remains responsive during physical motor movement, bypassing the blocking limitations of standard libraries.
- **Hardware Interfacing:** - **LCD (16x02):** Visualizes system metrics and FSM states.
    - **Ultrasonic Sensor (HC-SR04):** High-precision intruder detection.
    - **Stepper Motor (28BYJ-48):** Physical locking mechanism driven by ULN2003.
    - **IR Receiver (1838T):** Remote command interface for Arm/Disarm functions.
    - **LM35 Precision Sensor:** Analog temperature monitoring calibrated for industrial ranges.
    - **Active Buzzer:** Audio feedback for system initialization and alarm triggers.

## 🔬 Engineering Breakthroughs (Focus Area)

### 1. Thermal & Signal Stability
To prevent temperature drift caused by motor-induced voltage ripples, the system utilizes Arduino's **Internal 1.1V Reference**. This ensures the **LM35** readings remain accurate within ±0.5°C, even when the 9V battery voltage fluctuates under load.

### 2. Multi-Sampling Algorithm
Analog inputs (LM35) are processed through a **20-sample moving average filter** to eliminate high-frequency noise from the stepper motor's electromagnetic interference.

### 3. Power Optimization
A `releaseMotor()` function is implemented to de-energize stepper coils immediately after reaching the target position. This prevents the ULN2003 driver from overheating and extends the lifespan of the external 9V battery.

## 🔌 Hardware Pinout (Phase 5.0)
| Component | Arduino Pin | Note |
| :--- | :--- | :--- |
| **LCD (RS, EN, D4-D7)** | 12, 11, 5, 4, 3, 2 | Standard 4-bit mode |
| **HC-SR04 (Trig, Echo)** | 7, A2 | Proximity Sensing |
| **IR Receiver** | A1 | Remote Interface |
| **Active Buzzer** | A3 | Audio Feedback |
| **LM35 Sensor** | A5 | High-Stability Input |
| **Stepper (IN1-IN4)** | 8, 10, 9, A0 | ULN2003 Driver |

## 📈 Development Roadmap
- [x] **Phase 1:** LCD and FSM Core Logic.
- [x] **Phase 2:** Distance Sensing and State Transitions.
- [x] **Phase 3:** Actuator Integration and External Power Architecture.
- [x] **Phase 4:** IR Remote Integration & Non-blocking Logic implementation.
- [x] **Phase 5:** Final Sensor Fusion, Audio Alerts, and Internal Vref Calibration.

## 👨‍💻 Developer
**Hasan Ali Kinas** Electronics and Communication Engineering Student  
Izmir Institute of Technology (IYTE)
