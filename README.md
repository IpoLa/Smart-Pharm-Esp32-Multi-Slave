ESP-NOW Broadcast Demo By Akram Mezaache

This project demonstrates how to utilize ESP-NOW, a communication protocol developed by Espressif Systems, to broadcast messages between ESP32 devices. The code is designed to run on two or more ESP32 devices, enabling them to send and receive messages wirelessly using ESP-NOW.
Features:

    ESP-NOW Communication: Utilizes ESP-NOW for efficient and low-latency communication between ESP32 devices.
    Message Broadcasting: Broadcasts messages to all devices in range, enabling simultaneous control of multiple devices.
    Pushbutton Control: Toggles an LED on each device using a pushbutton, with the state synchronized across all devices.

Hardware Requirements:

    Two or more ESP32 devices
    LED and pushbutton connected to GPIO pins (specified in the code)

Usage:

    Upload the provided code to each ESP32 device.
    Ensure that the devices are within range and connected to the same network.
    Press the pushbutton on any device to toggle the LED state. The state change will be broadcasted to all devices.
    Observe the synchronized behavior of LEDs across all devices.

Code Overview:

    Setup: Initializes the ESP32 devices, configures ESP-NOW, and sets up the pushbutton and LED pins.
    Receive Callback: Handles incoming messages and updates the LED state accordingly.
    Sent Callback: Provides feedback on the status of message transmission.
    Broadcast Function: Sends a message to all devices in range.
    Loop: Monitors the pushbutton state and broadcasts messages accordingly.

Note:

    Ensure that the devices are properly configured to communicate via ESP-NOW and are within range of each other.
    Customize the GPIO pins for the LED and pushbutton according to your hardware setup.

Disclaimer:

This code is provided for educational purposes and may require modifications to suit specific use cases or hardware configurations. Use it responsibly and ensure compliance with local regulations.

For more information on ESP-NOW and ESP32 development, refer to the official documentation and resources provided by Espressif Systems.

Author: Akram Mezaache

Date: March 17 2024
