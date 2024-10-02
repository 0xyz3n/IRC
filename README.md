# IRC
 
## Libraries Used
- [DabbleESP32](https://github.com/STEMpedia/DabbleESP32)
- [Wire](https://github.com/espressif/arduino-esp32/blob/master/libraries/Wire/src/Wire.h)
- [Adafruit_PWMServoDriver](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library)

> [!NOTE]
> Use ESP32 board manager v2.0.16 for compiling and flashing this program.

## Overview
This project utilizes an ESP32 microcontroller to control a robotic arm and a two-wheel movement system via a gamepad interface provided by the Dabble app. The code leverages the Adafruit PWM Servo Driver for servo control and the DabbleESP32 library for gamepad input handling.

## Hardware Requirements
1. ESP32 Development Board
2. Servo Driver (PCA9685)
3. 4x DC Motors and Motor Driver (L298N)
4. Servos (for robotic arm)
5. Bluetooth-enabled smartphone with the Dabble app
6. LEDs (for status indication)
7. Miscellaneous components: resistors, wires, breadboard, etc.

## Circuit Diagram
### Motor Connections
- Motor 1 Forward: GPIO 16
- Motor 1 Backward: GPIO 17
- Motor 2 Forward: GPIO 5
- Motor 2 Backward: GPIO 18

### Servo Connections
- Servos connected to the Adafruit PWM Servo Driver
- Servo driver connected to esp32 via SCL & SDA pin (communicstion between ESP32 & servo Driver done via I2C protocol)

> [!CAUTION]
> Never give 5v supply to 3.3v pin as it is not connected with the built-in voltage regulator.

## Code Explanation
### Constants and Global Variables
- motorPin_fwd[]: GPIO pins for forward movement of motors.
- motorPin_bkwrd[]: GPIO pins for backward movement of motors.
- movementDelay: Minimum delay for movement.
- servoMIN, servoMAX: Minimum and maximum pulse lengths for servos.
- min_val[], max_val[], servoDelay[], value[]: Arrays to store servo configuration and state.
- servo: Current selected servo.
- mode: Boolean to toggle between movement mode and robotic arm control mode.
- debug: Boolean to enable/disable debug messages.

### Setup Function
1. Initializes motor pins as outputs.
2. Initializes the Adafruit PWM Servo Driver.
3. Sets up the serial communication for debugging.
4. Starts the Dabble library with the specified Bluetooth name.

### Loop Function
1. Processes input from the Dabble gamepad.
2. Checks which button is pressed and performs actions accordingly:
3. Directional buttons (Up, Down, Left, Right) for movement or servo selection.
4. Square, Circle buttons for servo selection.
5. Cross, Triangle buttons for servo movement.
6. Select button to toggle between movement mode and robotic arm control mode.
7. Start button to stop all movements.
8. Calls processMovement function to handle motor movements.
9. Prints debug information if enabled.

### Helper Functions
- moveServo(bool up): Moves the selected servo up or down within its limits.
- blink(uint8_t n, uint16_t d): Blinks the built-in LED n times with delay d.
- processMovement(byte dirn): Handles the movement logic based on the direction.
- moveMotor(byte motor, byte direction): Controls individual motor based on the direction.

## Functions Documentation

 #### void moveServo(bool up)
 ```
Moves the selected servo up or down.
@params up  Boolean indicating the direction of movement (true for up, false for down).
@return void
```
***

#### void blink(uint8_t n, uint16_t d)
```
Blinks the built-in LED a specified number of times with a specified delay.
@params n  Number of times to blink.
@params d  Delay in milliseconds between blinks.
@return void
```
***

#### void processMovement(byte dirn)
```
Processes the movement based on the direction.
@params dirn  Direction of movement (0 for forward, 1 for backward, 2 for left, 3 for right, -1 for stop).
@return void
```
***

#### void moveMotor(byte motor, byte direction)
```
Moves an individual motor in the specified direction.
@params motor  Motor index (0 or 1).
@params direction  Direction (1 for forward, 0 for stop, 2 for backward).
@return void
```

## Debugging
Enable the `debug` variable to print debug messages to the serial monitor. This can help in troubleshooting and understanding the current state of the system.

> [!WARNING]
> Set correct baud rate for serial monitor before viewing debug data.
