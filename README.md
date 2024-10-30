# Dhyan Chand Singh

## Overview

This project implements a remote-controlled robot capable of navigating and performing basic military-style operations using a toy gun. The robot can move in various directions, avoid obstacles, and fire a toy gun safely, all controlled through a simple web interface.

## Features

- **Wi-Fi Connectivity**: Connects to a Wi-Fi network for remote control.
- **Obstacle Avoidance**: Uses an ultrasonic sensor to detect and avoid obstacles.
- **Movement Control**: Moves forward, backward, left, right, and can stop.
- **Shooting Mechanism**: Fires a safe toy gun on command.
- **User-Friendly Web Interface**: Control the robot from any device with a web browser.

## Requirements

### Hardware

- NodeMCU (ESP8266) development board
- Motor driver module (e.g., L298N)
- Ultrasonic distance sensor (e.g., HC-SR04)
- DC motors with wheels
- Toy gun (ensure it's safe for use)
- Relay module or transistor for firing the gun

### Software

- Arduino IDE with ESP8266 board package installed

## Setup Instructions

1. **Install Arduino IDE**:
   - Download and install the [Arduino IDE](https://www.arduino.cc/en/software).

2. **Install ESP8266 Board Package**:
   - Open the Arduino IDE.
   - Go to `File` > `Preferences`.
   - In the "Additional Board Manager URLs" field, add:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Go to `Tools` > `Board` > `Board Manager`, search for "ESP8266", and install the package.

3. **Clone or Download the Repository**:
   - Clone this repository or download it as a ZIP file and extract it.

4. **Open the Code**:
   - Open the provided `.ino` file in the Arduino IDE.

5. **Configure Wi-Fi Credentials**:
   - In the code, replace `your_SSID` and `your_PASSWORD` with your actual Wi-Fi credentials.

6. **Upload the Code**:
   - Connect your NodeMCU to your computer.
   - Select the appropriate board and port in the Arduino IDE (`Tools` > `Board` > `NodeMCU 1.0 (ESP-12E Module)` and `Tools` > `Port`).
   - Click the upload button.

7. **Access the Web Interface**:
   - Open the Serial Monitor (`Tools` > `Serial Monitor`) to find the IP address assigned to your NodeMCU.
   - Enter this IP address in a web browser to access the control interface.

## Usage

- The web interface displays controls for moving the robot and firing the toy gun.
- Use the buttons provided to navigate the robot and fire when desired.

## Safety Instructions

- Ensure the toy gun used is compliant with local laws and regulations.
- Always supervise the robot during operation, especially when firing.

## Future Enhancements

- **Autonomous Navigation**: Implement algorithms for autonomous movement and targeting.
- **Camera Integration**: Add a camera for remote surveillance capabilities.
- **Advanced Sensors**: Integrate additional sensors for improved functionality.

## License

This project is licensed under the MIT License. Feel free to modify and use the code for your own projects.
