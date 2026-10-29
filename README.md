# Automated Pick-and-Place Robotic Arm with Conveyor System

An Arduino-based automation project that integrates a servo-driven robotic arm, dual conveyor belts, DC gear motors, and an infrared (IR) sensor to demonstrate automated object handling and sorting.

This project was developed as a university engineering project to explore embedded systems, robotics, mechanical fabrication, motor control, and industrial automation.

## Project Overview

Traditional material handling and sorting can require repetitive manual work. This project demonstrates a low-cost automated system that detects an object on a conveyor, coordinates conveyor movement, and uses a robotic arm to pick up and transfer the object to a designated location.

The system combines mechanical components with an Arduino-based control system to demonstrate the fundamental principles of automated pick-and-place operations.

## Key Features

- **IR-based object detection:** Detects objects using a digital infrared sensor.
- **Automated pick-and-place:** Controls the robotic arm through a programmed sequence of movements.
- **Four-axis servo control:** Operates the base, shoulder, elbow, and gripper using four servo motors.
- **Dual conveyor system:** Uses two conveyor belts driven by DC gear motors.
- **Motor speed and direction control:** Uses an L298N motor driver and Arduino output signals.
- **Embedded control:** Coordinates sensor input, motor operation, and servo movement through Arduino C++.
- **Mechanical fabrication:** Integrates a fabricated frame, conveyor rollers, shafts, couplings, and bearings.

## System Architecture

```text
          Objects on Conveyor
                   |
                   v
             +-----------+
             | IR Sensor |
             +-----------+
                   |
                   v
             +-----------+
             | Arduino   |
             |   Uno     |
             +-----------+
               |       |
          Servo Signals  Motor Control
               |       |
               v       v
        +-----------+  +----------------+
        | Robotic   |  | L298N Driver   |
        | Arm       |  +----------------+
        |           |       |        |
        | Base      |       v        v
        | Shoulder  |   Conveyor A  Conveyor B
        | Elbow     |
        | Gripper   |
        +-----------+
```

*Conceptual system architecture; not a detailed electrical wiring diagram.*

## Hardware Components

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno | 1 | Main embedded controller |
| Servo motors | 4 | Control the base, shoulder, elbow, and gripper |
| DC gear motors | 2 | Drive the conveyor belts |
| L298N motor driver | 1 | Control DC motor direction and enable signals |
| IR sensor module | 1 | Detect objects on the conveyor |
| Conveyor belts | 2 | Transport objects through the system |
| 12 V DC power supply | 1 | Supply power to the DC motor system |
| 5 V power supply | 1 | Supply power to the servo system |
| Prototype PCB and jumper wires | As required | Electrical connections |
| Mechanical frame | 1 assembly | Support the complete system |
| Threaded rods, couplings, and bearings | As required | Support and transmit conveyor motion |
| Gripper assembly | 1 | Grip and release objects |

Additional electrical components include a miniature circuit breaker and insulated copper wiring, as documented in the project presentation.

## Software and Technologies

- **Programming language:** Arduino C++
- **Development environment:** Arduino IDE
- **Microcontroller:** Arduino Uno (ATmega328P)
- **Servo library:** `Servo.h`
- **Sensor interface:** Digital input
- **Motor control:** Digital direction signals and PWM enable signals
- **Control approach:** Sequential, rule-based automation

## Pin Configuration

The following table reflects the current Arduino source code.

| Component | Arduino pin | Function |
|---|---:|---|
| Base servo | D3 | Base rotation |
| Shoulder servo | D5 | Shoulder movement |
| Elbow servo | D6 | Elbow movement |
| Gripper servo | D9 | Gripper opening and closing |
| IR sensor | D2 | Object detection |
| Motor A input 1 | D8 | Right conveyor direction |
| Motor A input 2 | D7 | Right conveyor direction |
| Motor A enable | D11 | Right conveyor enable/PWM |
| Motor B input 1 | D12 | Left conveyor direction |
| Motor B input 2 | D13 | Left conveyor direction |
| Motor B enable | D10 | Left conveyor enable/PWM |


## Working Principle

### 1. System initialization

When the Arduino starts, the program initializes the servo motors, configures the motor driver and IR sensor pins, and moves the robotic arm to its initial position.

The left conveyor then starts moving to transport objects.

### 2. Object detection

The IR sensor continuously monitors its detection area.

In the current program:

- `LOW` indicates that an object has been detected and triggers the handling sequence.
- `HIGH` allows the loop to continue without initiating the pick-and-place sequence.

The detection polarity depends on the IR sensor module and its configuration.

### 3. Conveyor coordination

When the sensor output becomes `LOW`, the Arduino:

1. Stops the left conveyor.
2. Waits briefly.
3. Starts the right conveyor.
4. Initiates the robotic arm's pick-and-place sequence.

### 4. Pick operation

The robotic arm moves to its programmed picking position.

1. The base rotates toward the pick position.
2. The shoulder and elbow move downward.
3. The gripper closes to grasp the object.
4. The shoulder and elbow return to their raised positions.

### 5. Place operation

The arm transfers the object to the programmed placement position.

1. The base rotates toward the placement position.
2. The arm lowers toward the placement location.
3. The gripper opens to release the object.
4. The arm returns to its raised position.
5. The base returns to its initial angle.

### 6. Return to conveyor operation

The left conveyor restarts, and the right conveyor stops after the programmed delay. The loop continues monitoring the IR sensor for subsequent objects.

**Current implementation:** The program uses a fixed movement sequence and a single digital IR sensor. It does not currently implement camera-based object recognition, closed-loop position feedback, or IoT connectivity.

## Robotic Arm Position Configuration

The main movement parameters are defined near the beginning of the Arduino program.

| Parameter | Current value |
|---|---:|
| Base pick angle | 1° |
| Base place angle | 160° |
| Shoulder down angle | 105° |
| Shoulder up angle | 60° |
| Elbow down angle | 55° |
| Elbow up angle | 70° |
| Gripper open angle | 60° |
| Gripper close angle | 100° |

These values are initial calibration settings for the assembled mechanism. Actual safe angles depend on the servo models, linkage geometry, and mechanical limits.


## Power and Safety Considerations

- Use a regulated power supply appropriate for the servo motors and DC gear motors.
- Do not power four servos and two DC motors directly from the Arduino's 5 V pin.
- Ensure the motor driver, Arduino, and external supplies have compatible voltage levels and a common signal ground where required by the circuit design.
- Check the L298N module's current and thermal limits against the actual motors.
- Insulate exposed mains wiring and use appropriate electrical protection. Disconnect mains power before modifying the circuit.
- Keep hands clear of the gripper, conveyor belts, shafts, and couplings while the system is operating.
- Test servo angles at low risk and check for mechanical interference before running a complete cycle.

## Current Limitations

The current implementation is a useful foundation for learning embedded automation, but it has several limitations:

- **Single-sensor detection:** The IR sensor does not identify an object's color or exact dimensions.
- **Fixed movement sequence:** Servo angles and timing delays are predefined in the source code.
- **No feedback-based positioning:** The program does not use joint-position feedback or encoder-based conveyor control.
- **Continuous detection loop:** If the IR sensor remains `LOW`, the program may execute the sequence repeatedly. A one-shot trigger, object-clear condition, or state-machine implementation would improve handling.
- **PWM timer interaction:** The D10 motor enable assignment needs verification when using the `Servo.h` library on an Arduino Uno.
- **No network connectivity:** The current version does not include Wi-Fi, MQTT, cloud monitoring, or remote control.

## Future Improvements

Potential extensions include:

- Add a color sensor or camera for more advanced object classification.
- Introduce a finite-state machine to coordinate detection, picking, placement, and conveyor movement.
- Add sensor filtering and object-clear detection to prevent repeated triggers.
- Calibrate servo angles and improve motion smoothness.
- Add conveyor position sensors or encoders for more precise material handling.
- Integrate an ESP32 or another network-capable controller for IoT monitoring.
- Implement MQTT publishing for sensor events and system status.
- Add remote monitoring, fault reporting, and a dashboard.
- Improve mechanical rigidity and optimize the arm's payload capacity.

These are proposed extensions, not features of the current implementation.

## Skills Demonstrated

This project provides practical experience in:

- Embedded C++ programming
- Arduino microcontroller development
- Digital sensor interfacing
- Servo motor control
- DC motor direction and speed control
- Motor-driver integration
- Basic automation logic and sequential control
- Mechanical design, fabrication, and assembly
- Electrical wiring and power-system integration
- Hardware and software troubleshooting


## Project Documentation

The university presentation covers the design objectives, component selection, working principles, mechanical fabrication, calculations, wiring diagrams, and future improvements.

Recommended repository additions:

- `videos/` — demonstration videos showing the robotic arm and conveyor system in operation
- `images/` — photographs of the assembled system and fabrication process
- `wiring/` — a clear, labeled circuit diagram
- `src/` — Arduino source code

