# Lulu-daisy / Arduino firmware
**Programming light into textile**

## Project content
Lulu-daisy provide a tiny PCB with an addressable LED and an optic fiber connector.

## Hardware design

     _______
    |       |___GND____
    | POWER |___VCC__  |
    |_______|        | |
        ||           | |
        ||           | |
     ___||____       | |
    |         |      | |      _______       _______
    |    A    |------I-|-----|       |-----|       |-----
    |    R    |-DATA---|-----| LULU  |-----| LULU  |-----
    |    D    |--------I-----|_______|-----|_______|-----
    |    U    |
    |    I    |
    |    N    |
    |    O    |
    |_________|


# TODO
-Choose the onboard LED WS2812-mini, Dotstar, etc.
-Add an Arduino code example
- ...