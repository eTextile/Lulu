# Lulu_MCU

Lulu is small electronic board made for light injection into optic fibers.

## About The project
Lulu is a smal e-textile solution that facilitate the use of optics fibers in textile and fashion design.
This solution featuring a system for light injection into the optic fibers and a communication bus that alow easy light programing.


![alt tag](https://farm8.staticflickr.com/7762/18261111032_ac43080403_z_d.jpg)
![alt tag](https://farm6.staticflickr.com/5506/29792500474_7d4b125e57_z_d.jpg)

     _______   _______   _______
    |       | |       | |       |             ___/\/\/\___ GND
    | LULU  | | LULU  | | LULU  |            |    1-5 MΩ
    |_______| |_______| |_______|            |
    ____|||_______|||_______|||_______ 3.3V  |
    _____||________||________||______________|___ Data
    ______|_________|_________|_______ GND


## Lulu hardware
- MCU: ATTiny10
[![Lulu by Maurin 0b0275a0c920353b - Upverter](https://upverter.com/Maurin/0b0275a0c920353b/Lulu/embed_img/15136192700000/)](https://upverter.com/Maurin/0b0275a0c920353b/Lulu/#/)

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
## TPI programmer (NOT ICSP)
https://www.olimex.com/Products/AVR/Programmers/AVR-ISP-MK2/resources/AVR-ISP-MK2.pdf

### TPI pin mapping

     DATA 1 - - 2 VTARGET
    CLOCK 3 - - 4 NA
    RESET 5 - - 6 GND

### Wiring the ATTiny10 to ICSP programmer

| ATTINY10 - PIN   | PIN FONCTION |  ICSP-connector |
|------------------|--------------|-----------------|
|  1-PB0           |   TPIDATA    |  1-DATA         |
|  2-GND           |   GND        |  6-GND          |
|  3-PB1           |   TPICLK     |  3-CLOCK        |
|  4-PB2           |   NC         |  4-NA           |
|  5-VCC           |   +5V        |  2-VTARGET      |
|  6-PB3           |   RESET      |  5-RESET        |

- Check if you are in the dialout group
    cd /etc/udev/rules.d

- Read the chip ID
    avrdude -p t10 -P usb -c avrispmkii -B5

- Flash the chip
    avrdude -p t10 -P usb -c avrispmkii -B5 -U flash:w:test.elf

## REFs
- http://irq5.io/2017/09/09/writing-code-for-the-attiny10/
- http://electronut.in/attiny10-hello/

## TODO
