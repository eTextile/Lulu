# Lulu-star / Hardware
**Programming light into textile**

## Hardware design
This branch is using a 200mA power LED.

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

**References**
- https://learn.adafruit.com/pixie-3-watt-smart-chainable-led-pixels/design
- http://www.instructables.com/id/Power-LED-s---simplest-light-with-constant-current/
- https://scienceprog.com/building-simple-constant-current-power-led-driver/
- http://www.pcbheaven.com/userpages/LED_driving_and_controlling_methods/?topic=worklog&p=3

![alt tag](./DOCs/driver_00.png)

#### Circuit part list
| Part                         | REF                       | Package                | Weblink                | Price per unit |
| ---------------------------- | ------------------------- | -----------------------| -----------------------|--------------- |
| Power LED                    | OSRAM 200mA (white)       |                        |                        | $0.65          |
| Q1 - large N-channel MOSFET  | IRLML2060TRPBF            | SOT-23                 |                        | €0,133         |
| T1 - small NPN transistor    | MMBT2222A                 | SOT-23                 |                        | €0,044         |
| R1                           | Approximately 47k-ohm     |                        |                        |                |
| R2 - current set resistor    | 2.9 ohms 1/4 watt         |                        |                        |                |


- R2 is used to set the current limit and this doesn't depends on the voltage supply VDD.
- Q1 is used as a variable resistor. Q1 starts out turned on by R1.
- T1 is used as an over-current sensing switch, and R2 is the "sense resistor" or "set resistor" that triggers T1 when too much current is flowing. 
- The main current flow is through the LED's, through Q1, and through R2. When too much current flows through R2, T1 will start to turn on, which starts turning off Q1. Turning off Q1 reduces the current through the LED's and R2. So we've created a "feedback loop", which continuously tracks the current and keeps it exactly at the set point at all times. 

The NPN transistors T1 have a specified 0.6V drop between base and emitter when on.
This means the voltage across their respective shunt resistors R2 will always be 0.6V.
According to Ohm’s law, this means that the current through them will be 0.6[V]/1.9[Ohm], or about 200mA.
If the current were to decrease, the base voltage would decrease proportionally, resulting in the NPN having more resistance between its collector and emitter, thus causing a higher voltage on the collector (recognize the voltage divider formed between the NPNs and their R1 pull-ups?).
But this would result in a higher voltage on the FET gate, causing it to become less resistive between source and drain and as a result, higher current through the LED.
The same logic can be applied in the opposite direction. The conclusion is that this circuit is self-regulating the LED current


### PCB
To facilitate forkable design the PCB is made with Upverter an online PCB router software.
We are looking for a shape that allow zero waste in the panelization process.
- [Circle shape](https://upverter.com/DataPaulette/5193c940bede1099/Lulu-star_20/ "Made with Upvetrter, online PCB router software"). The circle shape correspond to the more common eTextile PCB but doesn't fit the zero waste.
- [Triangle shape](https://upverter.com/DataPaulette/08fe1452dfd87b08/Lulu-star_21/ "Made with Upvetrter, online PCB router software"). Triangle is a shape that fit the three wire connectors and the zero waste panelization process.

#### Part list
| Part                 | REF                      | Weblink                | Price per unit |
| -------------------- | ------------------------ | -----------------------|--------------- |
| Brass tube           | 2 mm Hole 5-10 mm Length | http://ebay.com        | $0.05          |
| JTE                  | 1.5 / 8 mm               |                        |                |
| Optical fibres PMMA  | 0.25 mm x 35 pce         |                        |                |
| Optical fibres TPU   | 1.5, 2, 3 mm             |                        |                |

https://www.leds-and-more.de/catalog/15mm-lwl-lichtwellenleiter-lichtleiter-seitlich-leuchtend-p-1937.html?osCsid=2me5dl4q5amcvgb6tnbqfd87i5

## TODO
- [ ] Find a 0.5W side LEDs
- [ ] Chose between a small single LED driver & linear constant current circuitry
- [ ] Optimize the power LED heat dissipation
- [ ] Identifying distributors in Europe