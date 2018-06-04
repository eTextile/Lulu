# Lulu-star / Hardware
**Programming light into textile**

## Hardware design
This branch is using a 200-350mA power LED.

Lulu-star have three connections.
- [+] 3.3 to 60 Voltes
- [PWM] I/O PIN
- [-] GND

![alt tag](https://raw.githubusercontent.com/eTextile/Lulu/master/docs/pictures/footprint_connection.jpg)

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

Easy to programmed, Lulu-star is using the Arduino IDE standard functions.
No library required.

    digitalWrite(LED_PIN, state);
    analogWrite(LED_PIN, val);


### LED driver
##### Constant Current Source

![alt tag](./DOCs/driver_00.png)

Resistor R1 is used to set the current limit and this doesn't depends on the voltage supply VDD.
The equation for this can be given as 'R1=0.7/Required current'.
- https://learn.adafruit.com/pixie-3-watt-smart-chainable-led-pixels/design
- http://www.instructables.com/id/Circuits-for-using-High-Power-LED-s/

### PCB
To facilitate forkable design the PCB is made with Upverter an online PCB router software.
We are looking for a shape that allow zero waste in the panelization process.

The circle shape correspond to the more common eTextile PCB but doesn't fit the zero waste.
- [Circle shape PCB](https://upverter.com/DataPaulette/5193c940bede1099/Lulu-star_20/ "Made with Upvetrter, online PCB router software").
Triangle is a shape that fit the three wire connectors and the zero waste panelization process.
- [triangle shape PCB](https://upverter.com/DataPaulette/08fe1452dfd87b08/Lulu-star_21/ "Made with Upvetrter, online PCB router software").

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
- [ ] Find a 0.5W side LEDs
- [ ] Chose between a small single LED driver & linear constant current circuitry
- [ ] Optimize the power LED heat dissipation
- [ ] Identifying distributors in Europe