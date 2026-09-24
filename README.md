# 8051 Microcontroller Embedded C Projects

This repository contains embedded C firmware projects for the **8051 Microcontroller** developed in **Keil µVision**, featuring I2C EEPROM interfacing and 16x2 LCD display control.

---

## 📁 Repository Structure

```
├── EEPROM/
│   ├── EEPROM.c          # C source code for I2C communication & UART transmission
│   ├── EEPROM.uvproj     # Keil µVision Project file
│   └── Objects/
│       └── EEPROM.hex    # Compiled Intel HEX file ready for flashing
├── LCD/
│   ├── LCD.c             # C source code for 16x2 LCD in 4-bit mode
│   ├── LCD.uvproj        # Keil µVision Project file
│   └── Objects/
│       └── LCD.hex       # Compiled Intel HEX file ready for flashing
├── .gitignore
└── README.md
```

---

## 1. EEPROM Interfacing (`EEPROM/`)

### Overview
Demonstrates software bit-banged **I2C communication** between an 8051 microcontroller (AT89C51/AT89S52) and an external I2C serial EEPROM (such as 24C02/24C04/24C16/24C64).

### Key Features
* **Bit-Banged I2C Protocol**:
  * `SCL` (Serial Clock) connected to **P2.0**
  * `SDA` (Serial Data) connected to **P2.1**
* **Operation Flow**:
  1. Writes 4 characters (`'8'`, `'0'`, `'5'`, `'1'`) to EEPROM address `0x0000`.
  2. Reads back the 4 bytes from address `0x0000`.
  3. Outputs the retrieved characters over **UART** at **9600 Baud** (Timer 1, Mode 2 @ 11.0592 MHz crystal) using `printf`.

---

## 2. 16x2 Alphanumeric LCD (`LCD/`)

### Overview
Demonstrates interfacing a standard HD44780-compatible **16x2 LCD** to an 8051 microcontroller in **4-bit mode** to minimize GPIO pin usage.

### Key Features
* **Pin Configuration**:
  * `RS` (Register Select) connected to **P0.0**
  * `RW` (Read/Write) connected to **P0.1**
  * `EN` (Enable) connected to **P0.2**
  * Data lines (`D4-D7`) connected to upper nibble of Port 0 (`P0.4 - P0.7`)
* **Display Messages**:
  * **Line 1**: `"Hello World"`
  * **Line 2**: `"ESD -IOT"`

---

## 🛠️ Tools & Prerequisites

* **IDE / Compiler**: [Keil µVision (C51)](https://www.keil.com/c51/)
* **Simulation**: Proteus VSM (optional, for schematic simulation)
* **Flash Programmer**: ProgISP, Flash Magic, or USBASP (depending on 8051 variant)
* **Crystal Frequency**: 11.0592 MHz

---

## 🚀 How to Build

1. Open Keil µVision.
2. Go to **Project** > **Open Project...** and select `EEPROM.uvproj` or `LCD.uvproj`.
3. Click **Build Target (F7)** to compile and generate updated `.hex` binaries.
4. Load the generated `.hex` file from the `Objects/` directory onto your hardware or simulator.
