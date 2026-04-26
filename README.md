# Smart Environment Monitor & Security Station
This project is a Finite State Machine (FSM) based embedded system developed using Arduino. It is designed to monitor environmental conditions while providing a robust, mechanical security layer.

## Technical Specifications
Architecture: Modular C++ implementation utilizing a Finite State Machine (FSM) for predictable and reliable state management.

Hardware Interfacing: Integration of multiple analog and digital sensors including:

LCD (16x02): Real-time system status and data visualization.

Ultrasonic Sensor (HC-SR04): Non-contact distance measurement for intruder detection.

Stepper Motor (28BYJ-48): Controlled via ULN2003 driver for physical locking mechanisms.

IR Receiver (1838T): Remote control interface for system arming/disarming.

Audio Feedback: Pulse-width modulation (PWM) driven frequency sweeps for industrial-grade alerts.

## Power Management (Engineering Focus)
A critical aspect of this project is the distributed power architecture. To prevent Brownout Resets caused by the high current draw of the stepper motor, the system utilizes:

Dual Power Rails: The Arduino logic is powered via USB, while the Stepper Motor is powered by an external 9V battery.

Common Ground Logic: All ground lines are tied together to ensure signal integrity across the sensing and actuation layers.

## Development Roadmap
[x] Phase 1: LCD and FSM Core Logic

[x] Phase 2: Distance Sensing and State Transitions

[x] Phase 3: Actuator Integration (Stepper & Buzzer) and Power Stability

[/] Phase 4: IR Remote Access Control and User Interfacing (Phase 4.9: Logic Verified & Conflict Resolved)
> **Technical Note (Phase 4.9):** During IR integration, a timing conflict was identified between the `Stepper.h` library and `IRremote`. The blocking nature of stepper movements caused IR signal loss. Current stable version (Phase 4.9) utilizes a validated FSM logic with temporary stepper bypass to ensure 100% remote responsiveness.

[ ] Phase 5: Environmental Sensor Fusion (LDR, LM35, Flame)

## Developer
Hasan Ali Kinas – Electronics and Communication Engineering Student at Izmir Institute of Technology.
