# Lulu / Firmware
**Programming light into textile**

## Project content

## Hardware design
     _______   _______   _______
    |       | |       | |       |             ___/\/\/\___ GND
    | LULU  | | LULU  | | LULU  |            |    1-5 MΩ
    |_______| |_______| |_______|            |
    ____|||_______|||_______|||_______ 3.3V  |
    _____||________||________||______________|___ Data
    ______|_________|_________|_______ GND

### ATTiny10 pin mapping
             (PCINT0/TPIDATA/OC0A/ADC0/AIN0) PB0 -|    |- PB3 (RESET/PCINT3/ADC3)
                                             GND -|    |- VCC
    (PCINT1/TPICLK/CLKI/ICP0/OC0B/ADC1/AIN1) PB1 -|    |- PB2 (T0/CLKO/PCINT2/INT0/ADC2)

## Programming
### Softwear setup
#### avrdude 6.3
    avrdude -v
    sudo add-apt-repository ppa:ubuntuhandbook1/apps
    sudo apt-get update
    sudo apt-get install avrdude avrdude-doc

    sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc

#### Compiling & linking
    avr-gcc -mmcu=attiny10 -DF_CPU=1000000 -g -Os test.c -o test.elf
    avr-size --mcu=attiny10 -C test.elf

### Hardwear setup
#### TPI programmer (NOT ICSP)
https://www.olimex.com/Products/AVR/Programmers/AVR-ISP-MK2/resources/AVR-ISP-MK2.pdf

#### TPI pin mapping
     DATA 1 - - 2 VTARGET
    CLOCK 3 - - 4 NA
    RESET 5 - - 6 GND

#### Wiring the ATTiny10 to TPI programmer (AVR-ISP-MK2)
| ATTINY10 - PIN   | PIN FONCTION |  TPI-connector  |
|------------------|--------------|-----------------|
|  1-PB0           |   TPIDATA    |  1-DATA         |
|  2-GND           |   GND        |  6-GND          |
|  3-PB1           |   TPICLK     |  3-CLOCK        |
|  4-PB2           |   NC         |  4-NA           |
|  5-VCC           |   +5V        |  2-VTARGET      |
|  6-PB3           |   RESET      |  5-RESET        |

Check if you are in the dialout group

    cd /etc/udev/rules.d

Read the chip ID

    avrdude -p t10 -P usb -c avrispmkii -B5

Flash the chip

    avrdude -p t10 -P usb -c avrispmkii -B5 -U flash:w:test.elf

## One-wire protocol
The standard 1-wire protocol uses only two lines: power and ground. Data is
transmitted to and from slave devices by a master device by toggling the power
line low for short periods of time. The slave devices maintain their power
during these short losses using a diode-capacitor rectifier circuit. However,
this protocol is not suitable for devices requiring more than a few hundred
microamps due to the fact that a large pullup resistor is used on the power
line and drawing too much current causes an unacceptable voltage drop.

## Modified One-wire protocol
This device uses a modified version of the protocol that sacrifices the bi-directionality of the protocol to fit in 1k of flash memory.
This protcol has been modified from the actual 1-wire specification to be simpler to use with a 100KHz tick rate on the master 
in addition to necessary modifications due to the loss of bidirectionality.

### Protocol synopsis
 * A reset is performed by holding the line low for 480uS. This device will
   listen for a continuously low input for the full 480uS without any additional
   edges. The master should allow the line to float for another 480uS. Normally,
   the presence pulse would be read during this time. However, there is no
   presence pulse in this system.
 * Following a reset, A falling edge must occur within 70uS. This marks the
   start of the LSB of the transmitted byte.
 * To write a 0, the master brings the line low for 60uS. The slave will sample
   between 20-30uS following the falling edge. Following this, the master will
   allow the line to float for 10uS before beginning the next bit.
 * To write a 1, the master brings the line low for 10uS and releases it. The
   slave will sample between 20-30uS following the falling edge. The master will
   allow the line to float for 60uS after the initial low pulse.
 * A transaction consists of the reset pulse following by 8 write pulses.

# REFs
- https://github.com/kcuzner/onewire-leds.git (Forked)
- http://irq5.io/2017/09/09/writing-code-for-the-attiny10/
- http://electronut.in/attiny10-hello/
- https://github.com/ytai/pixie

# TOTEST
- https://github.com/neuoy/OneWireArduinoSlave

# TODO
- 