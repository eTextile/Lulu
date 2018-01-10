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

## ATTiny10 pin mapping

         (PCINT0/TPIDATA/OC0A/ADC0/AIN0) PB0 -|    |- PB3 (RESET/PCINT3/ADC3)
                                         GND -|    |- VCC
(PCINT1/TPICLK/CLKI/ICP0/OC0B/ADC1/AIN1) PB1 -|    |- PB2 (T0/CLKO/PCINT2/INT0/ADC2)

| MCU PIN | MCU FONCTION |  ICSP    |
|---------|--------------|----------|
|  PB0    |   TPIDATA    |  1-MISO  |
|  GND    |   GND        |  6-GND   |
|  PB1    |   TPICLK     |  3-SCK   |
|  PB2    |   CLKO       |  4-NC    |
|  VCC    |   +5V        |  2-+5V   |
|  PB3    |   RESET      |  5-RESET |

## Setup
    sudo add-apt-repository ppa:ubuntuhandbook1/apps
    sudo apt-get update
    sudo apt-get install avrdude avrdude-doc

    sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude

## Compiling & linking
    avr-gcc -mmcu=attiny10 -DF_CPU=1000000 -g -Os test.c -o test.elf
    avr-size --mcu=attiny10 -C test.elf

## Programming
    avrdude -c usbtiny -p t10
    avrdude -c usbtiny -p t10 -U flash:w:test.elf

## REFs
- http://irq5.io/2017/09/09/writing-code-for-the-attiny10/
- http://electronut.in/attiny10-hello/

## TODO
