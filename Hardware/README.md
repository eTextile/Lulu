# Lulu-star / Hardware
**Programming light into textile**

## Project content

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
| Brass tube           | 2 mm Hole X 10 mm Length | http://ebay.com        | $0.05          |
| JTE                  | 1.5 / 8 mm               |                        |                |
| Optical fibres PMMA  | 0.25 mm x 35 pce         |                        |                |
| Optical fibres TPU   | 1.5, 2, 3 mm             |                        |                |

## TODO
- [ ] Find a partner to develop the electronic
- [ ] Find a 0.5W side LEDs
- [ ] Chose between a small single LED driver & linear constant current circuitry
- [ ] Optimize the power LED heat dissipation
- [ ] Identifying distributors in Europe