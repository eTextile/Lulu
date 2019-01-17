# Lulu-star

### Programming light into textile
This file is listing a group of examples that can be a starting point to make a project out of the Lulu-star hardware.

Microcontroleurs such as Adafruit Gemma, Trinketor or DIGISPERK are cool components to get a nice eTextile integration.

## DIGISPARK specifications

** UNDER MACKINTOSH YOU WILL NEED A USB HUB TO PROGRAM THE DIGISPARK BOARD! **
- Instaling Digispark support for Arduino
  - Add this link to the Arduino Préférences : http://digistump.com/package_digistump_index.json
  - Look for Digispark into the Arduino bord manager

    Digispark digital I/O PINs
    - Pin 0 → I2C SDA, PWM (LED_BUILTIND on Model B)
    - Pin 1 → PWM (LED_BUILTIN on Model A)
    - Pin 2 → I2C SCK, Analog
    - Pin 3 → Analog In (also used for USB+ when USB is in use)
    - Pin 4 → PWM, Analog (also used for USB- when USB is in use)
    - Pin 5 → Analog In

## Adafruit Gemma specifications

- Instaling Gemma support for Arduino
  - Add this link to the Arduino Préférences : https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
  - Look for Gemma into the Arduino bord manager

** THE SKETCH UPLOADING PROCESS IS NOT AS STANDARD ARDUINO BOARD **
...


#### Lulu_blink
Blinking a single lulu board

#### Lulu_fade
Fading a single lulu board (FIXME)

#### Lulu_fade_with_sensor
Fading the Lulu in combination with a light sensor (TODO)

#### Lulu_...