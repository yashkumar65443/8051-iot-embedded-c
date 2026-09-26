# Multi-Architecture Embedded Systems & IoT Firmware Repository

A complete collection of embedded C/C++ firmware projects and laboratory exercises spanning **5 microcontroller architectures** (**8051**, **ARM7 LPC2148**, **ARM Cortex-M4 LPC4088**, **Microchip PIC16F877A**, and **ESP8266 NodeMCU**), developed for the Pantech Embedded Systems & IoT (ESD - IoT) curriculum.

---

## 📁 Complete Repository Structure

```
├── 8051 Projects (Root & labs/)
│   ├── EEPROM/                                 # I2C Serial EEPROM (24Cxx) + UART
│   ├── Home-Automation/                        # UART / Bluetooth Appliance Control
│   ├── LCD/                                    # 16x2 Character LCD (4-bit mode)
│   ├── SPI-ADC/                                # MCP3202 12-Bit SPI ADC Interfacing
│   ├── UART-Transmit/                          # Register-level UART String Transmitter
│   ├── UART-Echo/                              # Full-Duplex UART Echo Server
│   └── labs/                                   # Introductory 8051 GPIO Labs
│       ├── led-blinking/                       # Lab 1: All-LED Blinking
│       ├── scrolling-led/                      # Lab 2: LED Chaser / Bit-Shifter
│       └── switch-interfacing/                 # Lab 3: Switch Input to LED Output
│
├── ARM7-LPC2148/                               # 32-Bit ARM7TDMI-S (NXP LPC2148 @ 60MHz)
│   ├── UART-Demo/                              # UART0 Transceiver @ 9600 Baud
│   ├── LCD-16x2/                               # 16x2 LCD in 8-Bit Mode (Port 1)
│   └── DHT11-ESP8266-ThingSpeak/               # DHT11 Sensor + ESP8266 Cloud Upload
│
├── ARM-Cortex-M4-LPC4088/                      # 32-Bit ARM Cortex-M4 (NXP LPC4088 @ 120MHz)
│   ├── LED-Blinking/                           # GPIO Port 4 (P4.0 - P4.7) LED Blinking
│   ├── LED-with-Switch/                        # Switch Input (P4.8-P4.15) to LED (P4.0-P4.7)
│   ├── Buzzer/                                 # Buzzer Control on GPIO P0.26
│   ├── LCD-16x2/                               # 16x2 LCD in 4-Bit Mode (P0.4/P0.5 & P4.28-P4.31)
│   ├── UART0/                                  # UART0 Serial Echo @ 9600 Baud (P0.2/P0.3)
│   └── DHT11-Sensor/                           # Hardware Timer-based DHT11 Temperature/Humidity
│
├── PIC16F877A/                                 # 8-Bit Microchip PIC16F877A (MPLAB / HI-TECH C)
│   ├── LED-Blinking/                           # Multi-Port (PORTA - PORTE) LED Blinking
│   ├── LCD-and-7Segment/                       # 16x2 LCD (8-bit) & 4x7-Segment Multiplexed Counter
│   ├── Relay-and-Buzzer-UART/                  # Serial Menu-Controlled Relay & Buzzer System
│   └── USART/                                  # Hardware USART Echo & printf() Integration
│
├── ESP8266-IoT/                                # Wi-Fi SoC (Arduino IDE / Blynk Cloud)
│   └── Blynk-Google-Assistant/                 # Blynk + Google Assistant Smart Home Automation
│
├── .gitignore                                  # Filters Keil, ARM, and MPLAB build artifacts
└── README.md                                   # Documentation
```

---

## 🔒 Security & Credentials Configuration

Sensitive credentials have been masked with safe placeholders before publishing. Before compiling or flashing the IoT cloud projects, replace the placeholders with your own keys:

1. **[`ESP8266-IoT/Blynk-Google-Assistant/HOMEGOOGLE.ino`](ESP8266-IoT/Blynk-Google-Assistant/HOMEGOOGLE.ino)**
   * `YOUR_BLYNK_AUTH_TOKEN` → Your Blynk Project Auth Token
   * `YOUR_WIFI_SSID` → Your 2.4 GHz Wi-Fi Network Name
   * `YOUR_WIFI_PASSWORD` → Your Wi-Fi Password

2. **[`ARM7-LPC2148/DHT11-ESP8266-ThingSpeak/DHT11.c`](ARM7-LPC2148/DHT11-ESP8266-ThingSpeak/DHT11.c)**
   * `YOUR_WIFI_SSID` & `YOUR_WIFI_PASSWORD` in `AT+CWJAP` command (`command_ESP_3`)
   * `YOUR_THINGSPEAK_API_KEY` in the HTTP `GET /update?api_key=...` string (`command_ESP_7`)

---

## 🖥️ Architecture Breakdown

### 1. 8051 Microcontroller (`AT89C51 / AT89S52` — Keil C51)
| Module | Pins Used | Key Concepts |
| :--- | :--- | :--- |
| **`EEPROM/`** | `SCL=P2.0`, `SDA=P2.1` | Software bit-banged I2C master reading/writing 24Cxx EEPROM + UART output |
| **`Home-Automation/`** | `Lamp=P0.0`, `Fan=P0.1` | UART command listener (`'1'`–`'4'`) controlling appliance relays |
| **`LCD/`** | `P0.0-P0.2`, `P0.4-P0.7` | HD44780 16x2 LCD driver in 4-bit nibble mode |
| **`SPI-ADC/`** | `P2.4 - P2.7` | Bit-banged SPI communication with Microchip MCP3202 12-bit ADC |
| **`UART-Transmit/`** | `TX=P3.1`, `RX=P3.0` | Register-level (`SBUF`, `TI`) serial string streaming @ 9600 Baud |
| **`UART-Echo/`** | `TX=P3.1`, `RX=P3.0` | Full-duplex serial transceiver polling `RI` and `TI` |
| **`labs/`** | `P0`, `P2` | LED blinking, bitwise shift LED chaser, and DIP switch input mirroring |

---

### 2. ARM7TDMI-S (`NXP LPC2148` — Keil MDK-ARM)
| Module | Pins Used | Key Concepts |
| :--- | :--- | :--- |
| **`UART-Demo/`** | `P0.0 (TXD0)`, `P0.1 (RXD0)` | 32-bit `PINSEL0`, `VPBDIV=0x02` (30 MHz PCLK), `U0LCR`, `U0DLL=195` (9600 Baud) |
| **`LCD-16x2/`** | `P1.16 (RS)`, `P1.17 (EN)`, `P1.18-P1.25 (D0-D7)` | 8-bit parallel LCD control using `IOSET1` and `IOCLR1` registers |
| **`DHT11-ESP8266-ThingSpeak/`** | `P1.16 (DHT11)`, `P0.0/P0.1 (UART0 @ 115200)` | Single-wire DHT11 sensor acquisition + ESP8266 AT command sequence to push temperature & humidity to **ThingSpeak Cloud** |

---

### 3. ARM Cortex-M4 (`NXP LPC4088 / LPC1788` — Keil MDK-ARM)
| Module | Pins Used | Key Concepts |
| :--- | :--- | :--- |
| **`LED-Blinking/`** | `P4.0 - P4.7` | Power control `LPC_SC->PCONP`, `LPC_IOCON`, and `LPC_GPIO4->DIR/PIN` |
| **`LED-with-Switch/`** | `P4.0-P4.7 (LED)`, `P4.8-P4.15 (SW)` | Reading upper byte switch inputs and shifting right (`>>= 8`) to lower byte LEDs |
| **`Buzzer/`** | `P0.26` | Periodic GPIO toggling for piezoelectric buzzer control |
| **`LCD-16x2/`** | `P0.4 (RS)`, `P0.5 (EN)`, `P4.28-P4.31 (D4-D7)` | 4-bit mode LCD interfacing at 120 MHz CCLK |
| **`UART0/`** | `P0.2 (TXD0)`, `P0.3 (RXD0)` | Cortex-M4 UART0 echo server at 9600 Baud (`DLL=195` @ 30 MHz PCLK) |
| **`DHT11-Sensor/`** | `P4.0 (DHT11)`, `P0.2/P0.3 (UART0 @ 115200)` | Precision microsecond (`LPC_TIM1`) and millisecond (`LPC_TIM2`) hardware timers for DHT11 protocol timing |

---

### 4. Microchip PIC16F877A (`8-Bit PIC` — MPLAB IDE / HI-TECH C)
| Module | Pins Used | Key Concepts |
| :--- | :--- | :--- |
| **`LED-Blinking/`** | `PORTA` – `PORTE` | Disabling analog comparators/ADC (`ADCON1 = 0x07`) and configuring `TRISx` direction registers |
| **`LCD-and-7Segment/`** | `PORTD`, `PORTE`, `PORTA` | Includes both a 16x2 8-bit LCD driver (`Lcd.c`) and a 4-digit multiplexed 7-segment display counter (`led.c`) |
| **`Relay-and-Buzzer-UART/`** | `RB0 (Buzzer)`, `RB1-RB2 (Relays)`, `RC6/RC7 (USART)` | Interactive UART console menu (`'1'`–`'6'`) to switch relays and buzzer ON/OFF |
| **`USART/`** | `RC6 (TX)`, `RC7 (RX)` | Hardware USART setup (`TXSTA`, `RCSTA`, `SPBRG`) and custom `putch()` hook for `printf()` |

---

### 5. ESP8266 / NodeMCU (`IoT Wi-Fi SoC` — Arduino IDE)
| Module | Libraries | Key Concepts |
| :--- | :--- | :--- |
| **`Blynk-Google-Assistant/`** | `ESP8266WiFi.h`, `BlynkSimpleEsp8266.h` | Connects NodeMCU to Blynk Cloud for voice-activated relay control via Google Assistant & IFTTT |

---

## 🛠️ Required Toolchains

* **8051 Projects**: [Keil C51 (µVision)](https://www.keil.com/c51/)
* **ARM7 & ARM Cortex-M4 Projects**: [Keil MDK-ARM (µVision)](https://www.keil.com/arm/mdk.asp)
* **PIC16F877A Projects**: Microchip MPLAB IDE v8 / MPLAB X with HI-TECH PICC Compiler
* **ESP8266 Projects**: Arduino IDE with ESP8266 Board Package & Blynk Library
