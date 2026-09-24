# 8051 Microcontroller Embedded C & IoT Firmware Repository

A comprehensive collection of embedded C firmware projects and introductory laboratory exercises for the **8051 Microcontroller (AT89C51 / AT89S52 / AT89C52)**, developed in **Keil µVision (C51)** for the Pantech Embedded Systems & IoT (ESD - IoT) curriculum.

---

## 📁 Repository Structure

```
├── EEPROM/                           # I2C Serial EEPROM Interfacing
│   ├── EEPROM.c                      # C source code (I2C bit-banging & UART)
│   ├── EEPROM.uvproj                 # Keil µVision Project file
│   └── Objects/EEPROM.hex            # Pre-compiled Intel HEX binary
│
├── LCD/                              # 16x2 Alphanumeric LCD Driver (4-bit Mode)
│   ├── LCD.c                         # C source code (HD44780 4-bit mode driver)
│   ├── LCD.uvproj                    # Keil µVision Project file
│   └── Objects/LCD.hex               # Pre-compiled Intel HEX binary
│
├── SPI-ADC/                          # MCP3202 12-Bit SPI ADC Interfacing
│   ├── SPI-ADC.c                     # C source code (SPI bit-banging & channel read)
│   ├── STARTUP.A51                   # 8051 startup assembly file
│   ├── SPI-ADC.uvproj                # Keil µVision Project file
│   └── Objects/SPI-ADC.hex           # Pre-compiled Intel HEX binary
│
├── UART-Transmit/                    # Serial UART String Transmission
│   ├── Main.c                        # C source code (Register-level UART TX)
│   ├── UART.uvproj                   # Keil µVision Project file
│   └── Objects/UART.hex              # Pre-compiled Intel HEX binary
│
├── UART-Echo/                        # Full-Duplex UART Echo Server
│   ├── Main.c                        # C source code (Serial RX and immediate TX)
│   ├── UART.uvproj                   # Keil µVision Project file
│   └── Objects/UART.hex              # Pre-compiled Intel HEX binary
│
├── labs/                             # Introductory GPIO Experiments
│   ├── led-blinking/                 # Lab 1: All-LED Blinking
│   │   ├── blinkled.c                # Toggles Port 2 LEDs ON/OFF
│   │   ├── ledblinking.uvproj
│   │   └── Objects/ledblinking.hex
│   ├── scrolling-led/                # Lab 2: LED Chaser / Running LED
│   │   ├── scroll.c                  # Left & Right bitwise shifts across Port 2
│   │   ├── scrolling.uvproj
│   │   └── Objects/scrolling.hex
│   └── switch-interfacing/           # Lab 3: Switch Input to LED Output
│       ├── switch.c                  # Reads Port 0 inputs and mirrors to Port 2
│       ├── switch.uvproj
│       └── Objects/switch.hex
│
├── .gitignore                        # Filters Keil intermediate artifacts
└── README.md                         # Documentation
```

---

## 🚀 Projects Overview

### 1. I2C EEPROM Interfacing (`EEPROM/`)
* **Communication Protocol**: Software bit-banged **I2C**
* **Pin Configuration**: `SCL = P2.0`, `SDA = P2.1`
* **Description**: Writes 4 ASCII characters (`'8'`, `'0'`, `'5'`, `'1'`) to an external 24Cxx EEPROM at address `0x0000`. After a 10 ms write-cycle delay, it reads back the 4 bytes and prints them over **UART @ 9600 Baud** using `printf`.

### 2. 16x2 Character LCD in 4-Bit Mode (`LCD/`)
* **Hardware Interface**: HD44780-compatible LCD connected to **Port 0**
* **Pin Configuration**: `RS = P0.0`, `RW = P0.1`, `EN = P0.2`, `D4-D7 = P0.4 - P0.7`
* **Description**: Splits each 8-bit command and ASCII character into two 4-bit nibbles to save microcontroller pins. Initializes the LCD in 4-bit, 2-line mode (`0x28`) and displays `"Hello World"` on Line 1 and `"ESD -IOT"` on Line 2.

### 3. SPI 12-Bit ADC Interfacing (`SPI-ADC/`)
* **Sensor / ADC Chip**: Microchip **MCP3202** (Dual-channel 12-bit ADC)
* **Communication Protocol**: Software bit-banged **SPI**
* **Pin Configuration**: `CS = P2.4`, `CLK = P2.5`, `DO (MISO) = P2.6`, `DI (MOSI) = P2.7`
* **Description**: Commands the MCP3202 in single-ended mode, reads the 12-bit converted analog value ($0 - 4095$ range, $\approx 1.22\text{ mV}$ precision), and transmits the reading over UART to a terminal screen.

### 4. Serial UART Transmit (`UART-Transmit/`)
* **Baud Rate**: **9600 Baud** (Timer 1, Mode 2 8-bit auto-reload, `TH1 = 0xFD` @ 11.0592 MHz)
* **Pin Configuration**: `TX = P3.1`, `RX = P3.0`
* **Description**: Demonstrates direct hardware register manipulation (`SBUF`, `TI`) to stream strings (`"Hello World!! \n\r"`) to a host PC without the overhead of `printf`.

### 5. Full-Duplex UART Echo Server (`UART-Echo/`)
* **Baud Rate**: **9600 Baud**
* **Pin Configuration**: `TX = P3.1`, `RX = P3.0`
* **Description**: Implements a bi-directional serial transceiver. Polling the `RI` (Receive Interrupt) flag, it captures incoming ASCII characters from terminal software (PuTTY / Tera Term / Serial Monitor) and immediately transmits them back over `TX`.

---

## 🔬 GPIO Laboratory Experiments (`labs/`)

| Experiment | Port(s) | Description |
| :--- | :--- | :--- |
| **Lab 1: LED Blinking** | Port 2 (`P2`) | Toggles all 8 LEDs between `0x00` and `0xFF` using software delay loops. |
| **Lab 2: Scrolling LED** | Port 2 (`P2`) | Implements a running chaser pattern via bitwise left (`<<= 1`) and right (`>>= 1`) shifting. |
| **Lab 3: Switch Interfacing** | Port 0 (In) & Port 2 (Out) | Sets Port 0 as input (`P0 = 0xFF;`) and copies switch states directly to Port 2 LEDs in real time. |

---

## 🛠️ Tools & Prerequisites

* **IDE / Compiler**: [Keil µVision (C51)](https://www.keil.com/c51/)
* **Hardware Simulation**: Proteus VSM
* **Flash Programmer**: Flash Magic, ProgISP, or USBASP
* **Crystal Oscillator**: 11.0592 MHz (standard for 8051 zero-error UART baud rates)

---

## 🔨 How to Build

1. Open **Keil µVision**.
2. Click **Project** > **Open Project...** and select any `.uvproj` file from any directory.
3. Press **F7** to build the project.
4. Load the generated `.hex` binary from the `Objects/` folder into your physical programmer or Proteus simulator schematic.
