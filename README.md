# Smart Environment Monitor & Security Station

This project is a **Finite State Machine (FSM)** based embedded system developed using Arduino. It is designed to monitor environmental conditions (temperature, light intensity, and flame detection) while providing a robust, remote-controlled security layer.

## Technical Specifications
* **Architecture:** Modular C++ implementation utilizing a Finite State Machine (FSM) for predictable and reliable state management.
* **Hardware Interfacing:** Integration of multiple analog and digital sensors including:
    * **LCD (16x02):** Real-time data visualization.
    * **Ultrasonic Sensor (HC-SR04):** Distance-based security triggers.
    * **Stepper Motor:** 28BYJ-48 with ULN2003 driver for mechanical locking.
    * **Analog Sensors:** LM35 (Temperature), LDR (Light), and Flame sensors.
* **User Control:** IR protocol integration for remote mode switching.
* **Audio Feedback:** Pulse-width modulation (PWM) driven frequency generation for melodic system alerts.

## Engineering Focus
* **Firmware Reliability:** Implementing non-blocking code structures to ensure real-time responsiveness.
* **Hardware-Software Integration:** Efficiently processing sensor data for automated system triggers.
* **Scalable Design:** Focused on modularity to allow the addition of further monitoring modules.

## Developer
* **Hasan Ali Kinas** - Electronics and Communication Engineering Student at Izmir Institute of Technology.
