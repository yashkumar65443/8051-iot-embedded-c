# 8051 & ARM7 (LPC2148) Embedded C & IoT Firmware Repository

A comprehensive collection of embedded C firmware projects and laboratory exercises for **8051 Microcontrollers (AT89C51 / AT89S52)** and **32-bit ARM7TDMI-S (NXP LPC2148)**, developed in **Keil µVision** for the Pantech Embedded Systems & IoT (ESD - IoT) curriculum.

---

## 📁 Repository Structure

```
├── ARM7-LPC2148/                     # 32-Bit ARM7 (NXP LPC2148) Projects
│   └── UART-Demo/                    # UART0 Serial Transceiver @ 9600 Baud
│       ├── uartdemo.c                # C source code (PINSEL0, U0LCR, U0DLL, U0THR/RBR)
│       ├── Startup.s                 # ARM7 startup assembly code
│       ├── uartdemo.uvproj           # Keil µVision Project file
│       └── uartdemo.hex              # Pre-compiled Intel HEX binary
│
├── EEPROM/                           # 8051 I2C Serial EEPROM Interfacing
│   ├── EEPROM.c                      # C source code (I2C bit-banging & UART)
│   ├── EEPROM.uvproj                 # Keil µVision Project file
│   └── Objects/EEPROM.hex            # Pre-compiled Intel HEX binary
│
├── Home-Automation/                  # 8051 UART / Bluetooth Home Automation System
│   ├── HOME.c                        # C source code (Serial command parser & relay control)
│   ├── HOME.uvproj                   # Keil µVision Project file
│   └── Objects/HOME.hex              # Pre-compiled Intel HEX binary
│
├── LCD/                              # 8051 16x2 Alphanumeric LCD Driver (4-bit Mode)
│   ├── LCD.c                         # C source code (HD44780 4-bit mode driver)
│   ├── LCD.uvproj                    # Keil µVision Project file
│   └── Objects/LCD.hex               # Pre-compiled Intel HEX binary
│
├── SPI-ADC/                          # 8051 MCP3202 12-Bit SPI ADC Interfacing
│   ├── SPI-ADC.c                     # C source code (SPI bit-banging & channel read)
│   ├── STARTUP.A51                   # 8051 startup assembly file
│   ├── SPI-ADC.uvproj                # Keil µVision Project file
│   └── Objects/SPI-ADC.hex           # Pre-compiled Intel HEX binary
│
├── UART-Transmit/                    # 8051 Serial UART String Transmission
│   ├── Main.c                        # C source code (Register-level UART TX)
│   ├── UART.uvproj                   # Keil µVision Project file
│   └── Objects/UART.hex              # Pre-compiled Intel HEX binary
│
├── UART-Echo/                        # 8051 Full-Duplex UART Echo Server
│   ├── Main.c                        # C source code (Serial RX and immediate TX)
│   ├── UART.uvproj                   # Keil µVision Project file
│   └── Objects/UART.hex              # Pre-compiled Intel HEX binary
│
├── labs/                             # 8051 Introductory GPIO Experiments
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
├── .gitignore                        # Filters Keil C51 & ARM intermediate artifacts
└── README.md                         # Documentation
```

---

## ⚡ ARM7 (NXP LPC2148) Projects

### UART0 Serial Communication (`ARM7-LPC2148/UART-Demo/`)
* **Target MCU**: NXP **LPC2148** (32-bit ARM7TDMI-S, 60 MHz CCLK, 30 MHz PCLK via `VPBDIV = 0x02`)
* **Pin Configuration**: `P0.0 = TXD0`, `P0.1 = RXD0` (configured via `PINSEL0 = 0x00000005`)
* **Baud Rate Configuration**: **9600 Baud** (8N1 frame format via `U0LCR = 0x83`, Divisor Latch `U0DLL = 0xC3` (195) for 30 MHz PCLK)
* **Description**: Implements full-duplex UART0 drivers (`UART0_Txchar`, `UART0_Rxchar`, `UART0_SendString`) using polling on Line Status Register (`U0LSR`) flags (`THRE` and `RDR`). Continuously transmits `"HELLO WORLD\r\n"`.

---

## 🚀 8051 Projects Overview

### 1. I2C EEPROM Interfacing (`EEPROM/`)
* **Communication Protocol**: Software bit-banged **I2C**
* **Pin Configuration**: `SCL = P2.0`, `SDA = P2.1`
* **Description**: Writes 4 ASCII characters (`'8'`, `'0'`, `'5'`, `'1'`) to an external 24Cxx EEPROM at address `0x0000`. After a 10 ms write-cycle delay, it reads back the 4 bytes and prints them over **UART @ 9600 Baud** using `printf`.

### 2. Home Automation via UART / Bluetooth (`Home-Automation/`)
* **Communication Protocol**: **UART @ 9600 Baud** (compatible with PC Serial Terminal, HC-05 Bluetooth, or ESP8266 Wi-Fi)
* **Pin Configuration**: `Lamp = P0.0`, `Fan = P0.1`, `TX = P3.1`, `RX = P3.0`
* **Command Mapping**:
  * `'1'` → Turns **Lamp ON** (`P0.0 = 1`)
  * `'2'` → Turns **Lamp OFF** (`P0.0 = 0`)
  * `'3'` → Turns **Fan ON** (`P0.1 = 1`)
  * `'4'` → Turns **Fan OFF** (`P0.1 = 0`)
  * Any other character → Replies `"choose 1,2,3,4"`

### 3. 16x2 Character LCD in 4-Bit Mode (`LCD/`)
* **Hardware Interface**: HD44780-compatible LCD connected to **Port 0**
* **Pin Configuration**: `RS = P0.0`, `RW = P0.1`, `EN = P0.2`, `D4-D7 = P0.4 - P0.7`
* **Description**: Splits each 8-bit command and ASCII character into two 4-bit nibbles to save microcontroller pins. Initializes the LCD in 4-bit, 2-line mode (`0x28`) and displays `"Hello World"` on Line 1 and `"ESD -IOT"` on Line 2.

### 4. SPI 12-Bit ADC Interfacing (`SPI-ADC/`)
* **Sensor / ADC Chip**: Microchip **MCP3202** (Dual-channel 12-bit ADC)
* **Communication Protocol**: Software bit-banged **SPI**
* **Pin Configuration**: `CS = P2.4`, `CLK = P2.5`, `DO (MISO) = P2.6`, `DI (MOSI) = P2.7`
* **Description**: Commands the MCP3202 in single-ended mode, reads the 12-bit converted analog value ($0 - 4095$ range, $\approx 1.22\text{ mV}$ precision), and transmits the reading over UART to a terminal screen.

### 5. Serial UART Transmit (`UART-Transmit/`)
* **Baud Rate**: **9600 Baud** (Timer 1, Mode 2 8-bit auto-reload, `TH1 = 0xFD` @ 11.0592 MHz)
* **Pin Configuration**: `TX = P3.1`, `RX = P3.0`
* **Description**: Demonstrates direct hardware register manipulation (`SBUF`, `TI`) to stream strings (`"Hello World!! \n\r"`) to a host PC without the overhead of `printf`.

### 6. Full-Duplex UART Echo Server (`UART-Echo/`)
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

* **IDE / Compiler**: [Keil µVision (C51 & MDK-ARM)](https://www.keil.com/)
* **Hardware Simulation**: Proteus VSM
* **Flash Programmer**: Flash Magic (for NXP LPC2148 & 8051) / ProgISP / USBASP

---

## 🔨 How to Build

1. Open **Keil µVision**.
2. Click **Project** > **Open Project...** and select any `.uvproj` file from any directory.
3. Press **F7** to build the project.
4. Load the generated `.hex` binary into your physical programmer or Proteus simulator schematic.
