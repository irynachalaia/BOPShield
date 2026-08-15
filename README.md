# BOPShield

### Experimental Ball-on-Plate Platform for Control Engineering

BOPShield is an experimental educational Ball-on-Plate system developed within the **AutomationShield initiative** at the **Slovak University of Technology in Bratislava**.

The platform was developed as part of my Bachelor's thesis and is designed for education and experimentation in automatic control, mathematical modelling, and feedback control.

## Overview
The project was inspired by the well-known Ball-on-Plate mechatronic experiment, various implementations of which are publicly available. The principle of the system is based on controlling the position of a ball by changing the inclination angle of a platform along two axes. Changing the platform orientation causes the ball to move, while the control system is responsible for either stabilising the ball at a desired position or guiding it along a predefined trajectory.
<p align="center">
<img width="360" height="350" alt="photo_2026-08-14_22-14-22" src="https://github.com/user-attachments/assets/c003f9ba-00bf-4bdd-9bc4-d3da36b7924a" />
</p>

The main objectives of the BOPShield project were:
- Design and development of the BOPShield platform, including the selection of suitable mechanical and electronic components, electrical circuit and PCB design, system assembly, and testing of the basic functionality.
- Development and implementation of an API for Arduino IDE, enabling interaction with the BOPShield hardware and implementation of control algorithms.
- Development of a mathematical model of the system and identification of unknown system parameters.
- Design and implementation of PID and LQ/LQI controllers for system stabilisation and trajectory tracking using Arduino IDE and MATLAB/Simulink.

## Hardware and Mechanical Design

BOPShield uses a two-axis platform actuated by two servo motors, with each servo controlling the platform inclination along one of two perpendicular axes. The rotational motion of the servos is transferred to the platform through mechanical linkages, enabling independent control of its orientation along both axes. The platform is supported by a central structure connected through a universal joint. The servo arms are linked to the platform using threaded rods and ball joints, providing the required freedom of movement while maintaining mechanical stability. The platform itself consists of two main parts: a lower support for the resistive touchscreen and an upper frame that securely holds the sensor in place and prevents the ball from leaving the active surface. The entire device is designed as an Arduino-compatible add-on module. A custom printed circuit board (PCB) was developed to integrate the electronic components and provide the connections required for sensing, actuation, and overall operation of the BOPShield system.
<p align="center">
<img width="390" height="370" alt="photo_2026-08-14_22-28-20" src="https://github.com/user-attachments/assets/c25b3a4f-5469-4558-bd14-8b4c5beafb70" />
</p>

## PCB Design

The BOPShield electronics were implemented using two custom-designed printed circuit boards (PCBs).

The main PCB integrates the core electronic components of the system, including push buttons, a potentiometer, resistors, capacitors, a diode, and the electrical connections required for communication between the individual components. A two-layer PCB design was used to achieve a compact layout and efficient routing while maintaining the required connectivity between the system components.

The secondary PCB was designed as an interface between the resistive touchscreen used for ball-position sensing and the main BOPShield electronics. Since the touchscreen is equipped with an FPC cable, the interface board provides a convenient transition between the sensor and the main PCB using Molex and JST connectors. The board converts the FPC connections into individual wires that can be easily connected to the main board.
<p align="center">
<img width="700" height="450" alt="pcb" src="https://github.com/user-attachments/assets/2a0884df-7576-4501-87c1-6175c0faac27" />
</p>

 ## Control Algorithms and Trajectories

BOPShield supports several reference trajectories designed to evaluate both system stabilisation and trajectory-tracking performance:

- Center stabilisation – the controller maintains the ball near the centre of the platform, providing a basic test of system stability and disturbance rejection.

- Circular trajectory tracking – the reference position continuously follows a circular path, allowing the tracking performance of the control system to be evaluated under a smoothly changing reference.

- Elliptical trajectory tracking – the ball follows a more complex elliptical reference trajectory, providing a more demanding test of controller performance.

Two control algorithms were implemented and experimentally evaluated:

- PID controller – a classical feedback controller that determines the control action based on the error between the desired and measured ball positions.
- LQI controller – a state-feedback controller with integral action designed using the mathematical model of the system.
  
The potentiometer is used to adjust the desired speed of the ball along the selected trajectory. By changing the potentiometer position, the user can control how quickly the reference point moves along the predefined path.

 ## Experimental Results and Demonstration
 
The performance of the implemented controllers was evaluated experimentally using data collected directly from the BOPShield platform. During each experiment, the measured X and Y positions of the ball were transmitted to MATLAB/Simulink, where they were recorded and visualised for further analysis. The resulting plots show the actual motion of the ball relative to the desired reference and provide a direct comparison of the tracking performance achieved by the PID and LQI controllers. Experimental evaluation was performed for all three operating modes: centre stabilisation, circular trajectory tracking, and oval trajectory tracking.
| Trajectory | PID controller | LQ controller with integral action |
|---|---|---|
| Centre balancing | <img width="400" height="220" alt="c_pid" src="https://github.com/user-attachments/assets/45f5cafc-fc72-465f-b579-1c7ea200ec44" /> | <img width="400" height="220" alt="lq_c" src="https://github.com/user-attachments/assets/7765228b-5c78-4042-95ac-d4e24c79f939" /> |
| Circular trajectory | <img width="400" height="220" alt="cir_PID" src="https://github.com/user-attachments/assets/4f177ccb-607b-4538-9798-a6ca98f862fe" /> | <img width="400" height="220" alt="lq_cir" src="https://github.com/user-attachments/assets/5ab20396-ad4c-42ae-869e-b46d47c66804" />|
|Oval trajectory |<img width="400" height="220" alt="o_PID" src="https://github.com/user-attachments/assets/88910fa1-1ee3-4a49-ad69-48ce75761e33" />|<img width="400" height="220" alt="lq_ov" src="https://github.com/user-attachments/assets/339902e8-f24b-4b93-808a-e239e18a48c3" />|

https://github.com/user-attachments/assets/2ce4d3ae-77bc-48d3-96e6-bf9a21eeda57


https://github.com/user-attachments/assets/c616295c-fb47-49cb-ac2f-742440809855





