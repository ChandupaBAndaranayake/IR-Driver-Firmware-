**LED Control System with IR Remote**
- This project implements an LED control system using an AVR microcontroller. The system allows you to control the brightness and color of LEDs using an infrared (IR) remote. It supports four white LEDs and three RGB LEDs.

**Components**
- ATMEGA328p chip
- Arduino UNO barod to flash the code or UART module for serial communication
- IR sensor (connected to PB0)
- 4 white LEDs (connected to PD3, PD5, PD6, PB3)
- 3 RGB LEDs (Red: PD2, Green: PD4, Blue: PD7)
- IR remote control

**Features**
- Increase and decrease the brightness of white LEDs.
- Toggle through RGB LED colors.
- Control the LEDs using an IR remote.
- Serial output for debugging and status updates.
  
**Hardware Connections**
- IR Sensor: Connect the data pin of the IR sensor to PB0.
- White LEDs:
- W_1: PD3
- W_2: PD5
- W_3: PD6
- W_4: PB3
- RGB LEDs:
- Red: PD2
- Green: PD4
- Blue: PD7

**Software Components**
- uart.h: Header file for UART communication.
- IRremote.h: Header file for IR remote communication.
  
**Code Overview**
- The main functionalities are implemented in the following functions:

**Initialization Functions:**

- init_bulbs(): Initializes the I/O ports for the LEDs.
- init_serial(): Initializes the UART for serial communication.
- IR_init(): Initializes the IR sensor.
- LED Control Functions:

- Turn_On_LEDS(): Turns on the LEDs in sequence.
- Turn_OFF_LEDS(): Turns off the LEDs in sequence.
- RGB_LED_ON(): Toggles the RGB LEDs.
- RGB_LED_OFF(): Turns off the RGB LEDs.
- White_LED_Off(): Turns off the white LEDs.
- set_All_LED_OFF(): Turns off all LEDs.
- set_White_LED_ON(uint8_t index): Sets a specific white LED on.
- set_RGB_LED_ON(int ledPin): Sets a specific RGB LED on.
- updateLEDs(): Updates the LED states based on the current index and toggling state.

**Remote Control Functions:**

- Vol_Up(): Increases the brightness or toggles RGB LEDs.
- Vol_Down(): Decreases the brightness or toggles RGB LEDs.
- Channel_Down(): Reduces the brightness of the current white LED.

**Main Loop:**

- Checks for IR remote codes and calls the appropriate functions to control the LEDs.
- IR Remote Control
  - Volume Up (V_U): Increase brightness or toggle RGB LEDs.
  - Volume Down (V_D): Decrease brightness or toggle RGB LEDs.
  - Channel Down (C_D): Reduce brightness of the current white LED.

**How to Use**

- Connect the Hardware: Connect the IR sensor and LEDs to the specified pins on the AVR microcontroller.
- Compile and Upload the Code: Use an AVR programmer to compile and upload the code to the microcontroller.
- Run the System: Power on the system. Use the IR remote to control the LEDs.
- Monitor via Serial Output: Open a serial monitor to view debugging information and status updates.

**Dependencies**
- AVR-GCC for compiling the code.
- AVRDUDE for uploading the code to the microcontroller.
- uart.h and IRremote.h libraries for UART and IR remote communication.

**Notes**
- Ensure the correct configuration of the F_CPU macro for your microcontroller clock frequency.
- Adjust the pin connections as per your specific hardware setup.
- This project demonstrates the integration of IR remote control with an AVR microcontroller to manage an array of LEDs, providing a practical application for home automation or decorative lighting control.





