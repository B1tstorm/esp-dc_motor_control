# DC Motor control

## Whats needed
1. ESP32
2. DC-Motor
3. L293D Motor Driver
4. Powersupply (5V USB Adapter / Battery)
5. Breadboard (for convenience)

## How to use example
- Connect [ESP32 PIN D5](https://esphome.io/devices/nodemcu_esp32.html) with [L293D PIN 2 (input 1)](https://www.ti.com/lit/ds/symlink/l293.pdf)
- Connect L293D's PIN 1 (enable) & PIN 8 (Vcc) with the 5V from your powersupply. **NOTE: the ESP32's 3.3V GPIO Output isn't enough for the enable PIN 1 from the L293D, thats why we use the 5V from the supply**.
- Connect L293D's PIN 4 or 5 with GND
- Connect your DC Motor. One wire to L293D's PIN 3 (output 1) and one to L293D's PIN 6 (output 2)
- Connect your Powersupply to a breadboard
- Connect the ESP32 to your Computer
- Open terminal and go to your folder where you cloned the project
- Make sure you have the idf.py tool installed at this terminal session (`get_idf`)
- write `idf.py build flash monitor`
- Have fun ;-)

## Folder contents

The project **dc_motor_control** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
