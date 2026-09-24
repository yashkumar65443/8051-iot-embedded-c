# 8051 Microcontroller Embedded C Projects

This repository contains embedded C firmware projects and introductory laboratory exercises for the **8051 Microcontroller** developed in **Keil µVision (C51)** for the Pantech Embedded Systems & IoT curriculum.

---

## 📁 Repository Structure

```
├── EEPROM/                           # I2C Serial EEPROM Project
│   ├── EEPROM.c                      # C source code (I2C bit-banging & UART)
│   ├── EEPROM.uvproj                 # Keil µVision Project file
│   └── Objects/
│       └── EEPROM.hex                # Compiled Intel HEX file
│
├── LCD/                              # 16x2 Character LCD Project (4-bit mode)
│   ├── LCD.c                         # C source code (4-bit LCD driver)
│   ├── LCD.uvproj                    # Keil µVision Project file
│   └── Objects/
│       └── LCD.hex                   # Compiled Intel HEX file
│
├── labs/                             # GPIO Laboratory Experiments
│   ├── led-blinking/                 # Lab 1: All-LED Blinking
│   │   ├── blinkled.c                # Toggles Port 2 LEDs ON/OFF
│   │   ├── ledblinking.uvproj
│   │   └── Objects/ledblinking.hex
│   ├── scrolling-led/                # Lab 2: LED Chaser / Running LED
│   │   ├── scroll.c                  # Left & Right bitwise shift on Port 2
│   │   ├── scrolling.uvproj
│   │   └── Objects/scrolling.hex
│   └── switch-interfacing/           # Lab 3: Switch Input to LED Output
│       ├── switch.c                  # Reads Port 0 inputs and drives Port 2
│       ├── switch.uvproj
│       └── Objects/switch.hex
│
├── .gitignore
└── README.md
```

---

## 🚀 Projects Overview

### 1. EEPROM Interfacing (`EEPROM/`)
* **Protocol**: Software bit-banged **I2C** (`SCL = P2.0`, `SDA = P2.1`)
* **Operation**: Writes ASCII `'8'`, `'0'`, `'5'`, `'1'` to memory address `0x0000`, waits for write-cycle completion, reads back the 4 bytes, and transmits them over **UART @ 9600 Baud** (Timer 1, Mode 2 @ 11.0592 MHz) using `printf`.

### 2. 16x2 Alphanumeric LCD (`LCD/`)
* **Protocol**: 4-bit mode interfacing on **Port 0** (`RS = P0.0`, `RW = P0.1`, `EN = P0.2`, `D4-D7 = P0.4-P0.7`).
* **Operation**: Initializes HD44780 controller in 4-bit mode (`0x28`) and displays:
  * **Line 1**: `"Hello World"`
  * **Line 2**: `"ESD -IOT"`

---

## 🔬 GPIO Laboratory Experiments (`labs/`)

### Lab 1: LED Blinking (`labs/led-blinking/`)
* **Target**: Port 2 (`P2`)
* **Description**: Alternates Port 2 between `0x00` and `0xFF` using a software delay loop to blink 8 LEDs simultaneously.

### Lab 2: Scrolling / Chaser LED (`labs/scrolling-led/`)
* **Target**: Port 2 (`P2`)
* **Description**: Demonstrates bitwise shifting:
  * `left()`: Shifts `0x01` leftwards (`j <<= 1`) up to `0x80`.
  * `right()`: Shifts `0x80` rightwards (`j >>= 1`) down to `0x01`.
  * Generates a Knight Rider / running LED pattern.

### Lab 3: Switch Input to LED Output (`labs/switch-interfacing/`)
* **Target**: Input on Port 0 (`P0`), Output on Port 2 (`P2`)
* **Description**: Configures Port 0 as an input port by writing `0xFF` (`P0 = 0xFF;`), then continuously reads switch states in a `while(1)` loop and mirrors their logic levels to Port 2 LEDs (`led = sw;`).

---

## 🛠️ Tools & Prerequisites

* **IDE / Compiler**: [Keil µVision (C51)](https://www.keil.com/c51/)
* **Simulation**: Proteus VSM (for circuit simulation without hardware)
* **Flash Programmer**: Flash Magic / ProgISP / USBASP
* **Crystal Frequency**: 11.0592 MHz (standard for 8051 UART baud generation)

---

## 🔨 How to Build

1. Open **Keil µVision**.
2. Go to **Project** > **Open Project...** and select any `.uvproj` file.
3. Press **F7** (or click *Build Target*) to compile and generate updated `.hex` binaries.
4. Load the generated `.hex` from the corresponding `Objects/` directory into your programmer or simulator.
