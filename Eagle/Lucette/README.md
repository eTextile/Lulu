# Lucette

Le projet Luce est à l’origine du développement de la carte électronique Lucette.
Cette petite carte qui fonctionne sur batterie permet de contrôler plusieurs Lulu.

![alt tag](https://farm2.staticflickr.com/1562/25915319424_2622f2de8f_z_d.jpg)

## Lucette caractéristiques
- Interrupter ON/OFF
- Microcontroller Atmeg328
- Contrôleur 16 PWM 12bits (TLC5940)
- Courant de sortie max : 3.3V - 60 mA
- Chargeur lithium-ion intégré

## Les données importantes
- Avant de brancher une LED il faut relever le courant MAXIMUM qu'elle consomme, puis en fonction de cette valeur ajuster la résistance R5 sur la carte (cf: capture d'écran ci-joint).
 - La formule qui permet de calculer la valeur de cette résistance est a la page 14 du datasheet : http://www.ti.com/lit/gpn/tlc5940

## TODO
- add auto-reset
- add unused pins on the edge of the PCB
