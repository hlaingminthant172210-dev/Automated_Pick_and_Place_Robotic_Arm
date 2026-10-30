# Automated Pick-and-Place Robotic Arm with Dual Conveyor System

**An Arduino-based automation system combining embedded programming, robotic manipulation, motor control, and mechanical fabrication.**

This project demonstrates an automated material-handling system built around an Arduino Uno, a four-servo robotic arm, two conveyor belts, DC gear motors, and an infrared (IR) sensor.

Developed as a university engineering project, the system combines mechanical construction with embedded C++ programming to demonstrate object detection, conveyor coordination, and automated pick-and-place operations.

**My role:** I built the complete project, including mechanical fabrication, hardware integration, electrical connections, Arduino programming, and system integration.

## Project at a Glance

| Category | Details |
|---|---|
| Project type | Embedded Systems / Robotics / Industrial Automation |
| Controller | Arduino Uno (ATmega328P) |
| Programming language | Arduino C++ |
| Robotic arm | Four servo motors |
| Conveyor system | Two conveyor belts with DC gear motors |
| Object detection | Digital IR sensor |
| Motor driver | L298N |
| Development environment | Arduino IDE |
| Project context | University engineering project |


## My Contribution

I developed the project from the mechanical assembly through to the embedded control system.

My responsibilities included:

- **Mechanical fabrication and assembly:** Constructing and assembling the robotic arm, conveyor mechanisms, supporting frame, shafts, couplings, and bearings.
- **Embedded programming:** Writing Arduino C++ code to coordinate the IR sensor, servo motors, and conveyor motors.
- **Sensor integration:** Connecting the IR sensor and using its digital output to initiate the handling sequence.
- **Motor control:** Integrating the L298N motor driver to control the conveyor motors.
- **Robotic arm control:** Programming the base, shoulder, elbow, and gripper movements.
- **Hardware integration:** Bringing the mechanical components, electrical connections, and control software together into one system.
- **System troubleshooting:** Working with the interactions between mechanical movement, motor operation, sensor signals, and programmed timing.

This project gave me practical experience with the relationship between mechanical systems and embedded control.

## How It Works

The system uses a predefined sequence to coordinate object detection, conveyor movement, and robotic arm operation.

### 1. Initialization

The Arduino initializes the sensor and motor-control pins, attaches the servo motors, and moves the robotic arm toward its initial position.

The left conveyor starts moving to transport an object toward the detection area.

### 2. Object Detection

An IR sensor monitors the detection area.

When the sensor output becomes `LOW`, the program interprets this as object detection and initiates the handling sequence.

The actual detection polarity depends on the sensor module and its configuration.

### 3. Conveyor Coordination

After detecting an object, the Arduino stops the left conveyor, executes a short delay, starts the right conveyor, and begins the programmed robotic arm sequence.

### 4. Pick-and-Place Operation

The four servo motors control the robotic arm:

- **Base:** Rotates the arm toward the picking and placement positions.
- **Shoulder:** Raises and lowers the arm.
- **Elbow:** Adjusts the arm's reach and positioning.
- **Gripper:** Opens and closes to release or grasp the object.

The programmed sequence lowers the arm, closes the gripper, raises the object, moves toward the placement position, releases the object, and returns toward the initial position.

### 5. Return to Operation

The program coordinates the conveyor motors using predefined delays before continuing its detection loop.

The system is based on fixed movement angles and sequential control rather than feedback-based robotic positioning.

## System Architecture

```text
                 Object
                   |
                   v
             +-----------+
             | IR Sensor |
             +-----------+
                   |
             Digital Input
                   |
                   v
             +-----------+
             | Arduino   |
             |   Uno     |
             +-----------+
                |     |
       Servo Control   Motor Control
                |     |
                v     v
        +-----------+  +-------------+
        | Robotic   |  | L298N Motor |
        | Arm       |  | Driver      |
        |           |  +-------------+
        | Base      |     |       |
        | Shoulder  |     v       v
        | Elbow     | Conveyor A  Conveyor B
        | Gripper   |
        +-----------+
```

*This is a conceptual architecture diagram, not an electrical wiring schematic.*

## Hardware Components

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno | 1 | Main controller |
| Servo motors | 4 | Control the robotic arm |
| DC gear motors | 2 | Drive the conveyor belts |
| L298N motor driver | 1 | Control DC motor operation |
| IR sensor module | 1 | Detect objects |
| Conveyor belts | 2 | Transport objects |
| 12 V DC supply | 1 | Supply the DC motor system |
| 5 V supply | 1 | Supply the servo system |
| Prototype PCB and jumper wires | As required | Electrical connections |
| Mechanical frame | 1 assembly | Support the system |
| Shafts, couplings, and bearings | As required | Support and transmit mechanical motion |
| Gripper assembly | 1 | Grasp and release objects |

Additional electrical components include a miniature circuit breaker and insulated copper wiring.

## Software and Technologies

- **Arduino C++** — embedded control programming.
- **Arduino IDE** — development and compilation.
- **Arduino Uno / ATmega328P** — microcontroller platform.
- **Servo.h** — servo motor control.
- **Digital input** — IR sensor interfacing.
- **Digital output and PWM** — DC motor control through the motor driver.
- **Sequential control logic** — coordinating the operating cycle.

## Pin Configuration

The following assignments reflect the current Arduino source code.

| Component | Pin | Purpose |
|---|---|---|
| Base servo | D3 | Base rotation |
| Shoulder servo | D5 | Shoulder movement |
| Elbow servo | D6 | Elbow movement |
| Gripper servo | D9 | Gripper operation |
| IR sensor | D2 | Object detection |
| Conveyor A input 1 | D8 | Motor direction |
| Conveyor A input 2 | D7 | Motor direction |
| Conveyor A enable | D11 | Motor enable/PWM |
| Conveyor B input 1 | D12 | Motor direction |
| Conveyor B input 2 | D13 | Motor direction |
| Conveyor B enable | D10 | Motor enable/PWM |


## Robotic Arm Calibration

The current program uses predefined servo angles to control the arm.

| Movement parameter | Configured angle |
|---|---:|
| Base pick position | 1° |
| Base placement position | 160° |
| Shoulder lowered position | 105° |
| Shoulder raised position | 60° |
| Elbow lowered position | 55° |
| Elbow raised position | 70° |
| Gripper open | 60° |
| Gripper closed | 100° |

These are program settings, not universal operating limits. Safe angles depend on the servo models, linkage geometry, mechanical construction, and available clearance.

## Engineering Challenges and Learning Outcomes

This project brought together several engineering disciplines that must work correctly as one system.

### Embedded Systems
- Interfacing a digital sensor with a microcontroller.
- Controlling multiple servo motors.
- Coordinating motor-driver signals and conveyor operation.
- Implementing sequential automation logic.

### Mechanical Engineering
- Fabricating and assembling the robotic arm and conveyor mechanisms.
- Integrating shafts, couplings, bearings, and structural components.
- Considering mechanical clearance and movement limits.

### Hardware and Software Integration
- Coordinating sensor signals with mechanical actions.
- Managing the timing of several motors.
- Connecting mechanical behavior with programmed movement sequences.
- Understanding how electrical, software, and mechanical decisions affect the complete system.

### Skills Developed

- Arduino C++ programming
- Microcontroller fundamentals
- Digital sensor interfacing
- Servo motor control
- DC motor and motor-driver integration
- Sequential automation
- Mechanical fabrication and assembly
- Hardware–software integration
- Embedded system troubleshooting

## Current Limitations

The current system demonstrates basic automation but has opportunities for further development.

- **Single-sensor detection:** The IR sensor detects an object but does not classify its color, shape, or dimensions.
- **Fixed movement sequence:** The arm uses predefined angles and timing delays.
- **No closed-loop positioning:** The current control approach does not use encoder-based conveyor positioning or joint-position feedback.
- **Repeated triggering:** If the IR sensor remains active, the program may initiate the sequence repeatedly unless additional trigger-handling logic is implemented.
- **PWM compatibility:** The D10 motor-enable assignment requires verification when used with `Servo.h` on the Arduino Uno.
- **No IoT connectivity:** The current version does not include network communication, MQTT, remote monitoring, or cloud integration.

## Future Improvements

Potential extensions include:

- Implement a finite-state machine for clearer control of detection, picking, placement, and conveyor operation.
- Add object-clear detection and trigger handling to prevent repeated cycles.
- Improve servo calibration and motion sequencing.
- Add position sensors or encoders for more precise conveyor control.
- Introduce a color sensor for basic object classification.
- Integrate an ESP32 or another network-capable controller.
- Publish sensor events and system status using MQTT.
- Develop a monitoring dashboard for automation status and fault reporting.

These are proposed improvements, not features of the current implementation.


## Conclusion

This project demonstrates the integration of mechanical fabrication, embedded C++ programming, sensor interfacing, motor control, and sequential automation in a working engineering system.

As a Mechanical Engineering student pursuing Embedded Systems and IoT, I use this project to develop practical experience connecting physical mechanisms with microcontroller-based control.

My next goal is to build on this foundation by improving control reliability, learning more about embedded communication protocols, and eventually integrating connected monitoring capabilities.

**The project represents my practical work at the intersection of Mechanical Engineering, Embedded Systems, and Industrial Automation.**