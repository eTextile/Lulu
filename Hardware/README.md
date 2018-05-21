# Lulu-star / Hardware
**Programming light into textile**

## Project content
This branch is using a 350mA power LED.
Lulu-star have three connections.
- [+] 3.3 to 10 Voltes
- [-] GND
- [PWM] I/O PIN

![alt tag](https://raw.githubusercontent.com/eTextile/Lulu/master/docs/pictures/footprint_connection.jpg)

Easy to programmed, Lulu-star is using the Arduino IDE standard functions. No library required.

    digitalWrite(LED_PIN, state);
    analogWrite(LED_PIN, val);

## Hardware design

      _______
     |       |
     | POWER |-----------------
     |_______|--------------| |
        | |                 | |
      + | | -             + | | -
     ___|_|____             | |
    |         |           __| |__
    |    A    |   PWM    |       |
    |    R    |--------->| LULU  |
    |    D    |          |_______|
    |    U    |             | |
    |    N    |           __| |__
    |    I    |   PWM    |       |
    |    O    |--------->| LULU  |
    |_________|          |_______|
                            | |

### PCB
- [PCB](https://upverter.com/DataPaulette/5193c940bede1099/Lulu-star/ "Made with Upverter, online PCB router software") Made with Upverter, online PCB router software.

### Part list
| Part                 | REF                      | Weblink                | Price per unit |
| -------------------- | ------------------------ | -----------------------|--------------- |
| LED                  | OSRAM 350mA (white)      | http://aliexpress.com  | $0.65          |
| Brass tube           | 2 mm Hole 5-10 mm Length | http://ebay.com        | $0.05          |
| JTE                  | 1.5 / 8 mm               |                        |                |
| Optical fibres PMMA  | 0.25 mm x 35 pce         |                        |                |
| Optical fibres TPU   | 1.5, 2, 3 mm             |                        |                |
| Q2 - MMBT2222A       |                          |                        | €0,044         |
| Q1 - IRLML2060TRPBF  |                          |                        | €0,133         |
| R1 - Resistor        | 47K Ohm 1206             |                        |                |
| R2 - Resistor        |                          |                        |                |
|                      |                          |                        |                |

## TODO
- [ ] Find a partner to develop the electronic
- [ ] Find a 0.5W side LEDs
- [ ] Chose between a small single LED driver & linear constant current circuitry
- [ ] Optimize the power LED heat dissipation
- [ ] Identifying distributors in Europe