
## Lucette
Le projet Luce est à l’origine du développement de la carte électronique Lucette.
Cette petite carte qui fonctionne sur batterie rechargeable permet de contrôler plusieurs Lulu.

![alt tag](https://farm2.staticflickr.com/1562/25915319424_2622f2de8f_z_d.jpg)

### Lucette caractéristiques
- Interrupter ON/OFF
- Microcontroller Atmeg328
- Contrôleur 16 PWM 12bits (TLC5940)
- Courant de sortie max : 3.3V - 60 mA
- Chargeur lithium-ion intégré

### Configurer l'IDE Arduino
- Installer la [librairie TLC5940](http://code.google.com/p/tlc5940arduino/downloads/detail?name=Tlc5940_r014_2.zip&can=2&q=) dans le répertoire : Documents/Arduino/libraries/Tlc5940
- La [doc du TLC5940](http://www.arduino.cc/playground/learning/TLC5940) sur arduino.cc
- Sélectionner le type de carte : Arduino Pro or Pro Mini (3.3V, 8MHz) / ATmega328

###Les broches/pin de l'ATmega328
- La broche digital 2 : cette broche est connectée a la broche XERR du TLC5940, elle est active si le TLC est en surchauffe ou si une connexion entre un actionneur et la puce est interrompu 
```
#define XERR 2 // pin to catch TLC error
```
- La broche digital 5 : Cette broche est connectée à une LED pour afficher les ERREURS captées par la broche XERR. Elle est aussi utile pour debugger visuellement un programme avec la fonction digitalWrite(ledPin, HIGH/LOW);
```
#define ledPin 5 // pin to display TLC error
```
- Les broches A2, A1, D6, D7, D8 : ces broches sont accessibles sur le coté de la carte pour permettre l'ajout de capteurs.

### Les fonctions de la librairie
La librairie TLC5940 comporte un ensemble de fonctions qui permettent de programmer l'intencité de chaqu'une des LEDs
```
Tlc.set(channel, valeur); // valeur = [0, 4095]
Tlc.update();
```
- Voir les exemples fournis avec cette librairie
 - Documents/Arduino/libraries/Tlc5940/examples

### Les données importantes
- Avant de brancher une LED il faut relever le courant MAXIMUM qu'elle consomme, puis en fonction de cette valeur ajuster la résistance R5 sur la carte (cf: capture d'écran ci-joint).
 - La formule qui permet de calculer la valeur de cette résistance est a la page 14 du datasheet : http://www.ti.com/lit/gpn/tlc5940

## TODO
- add auto-reset
- add unused pins on the edge of the PCB
