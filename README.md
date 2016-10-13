# Lucette

Textile lumineux réalisés en collaboration avec Alice Heit designer textile. Objets d’exception pour les repas de fêtes, ce tissus mêle intimement tradition et innovation. Il est animé d’un motif changeant, dont les lentes variations accompagnent les différents temps du repas. Une attention particulière est portée à l’intégration de électronique qui disparaît totalement au profit d’une esthétique simple. Le tissu, composé de fils d’ortie brute et des fils transparents très fins, présente une structure double épaisseur, à l’intérieur de laquelle sont entrelacées les fibres optiques lumineuses. Ces tissus sont des pièces uniques réalisés sur mesure.

![alt tag](https://farm8.staticflickr.com/7762/18261111032_ac43080403_z_d.jpg)
### Le site d'Alice : <a href="https://araneafilum.wordpress.com/" rel="nofollow">araneafilum.wordpress.com/</a>

## Caractéristiques de la carte Lucette
- Interrupter ON/OFF
- Microcontroller Atmeg328
- Contrôleur 16 PWM 12bits (TLC5940)
- Courant de sortie 120 mA / 3.3V max
- Chargeur lithium-ion intégré

## Configurer l'IDE Arduino
 - La première étape consiste à installer la librairie TLC5940 dans le répertoire : Documents/Arduino/libraries/Tlc5940
 - La doc sur arduino.cc : http://www.arduino.cc/playground/learning/TLC5940
 - Le lien directe de la lib sur google code : http://code.google.com/p/tlc5940arduino/downloads/detail?name=Tlc5940_r014_2.zip&can=2&q=
 - Type de carte : Arduino Pro or Pro Mini (3.3V, 8MHz) / ATmega328
 - Pour envoyer un programme c'est comme avec une Arduino mais il faut appuyer sur le bouton reset de la carte au moment d'envoyer le programme.

## Les broches/pin de l'ATmega328
### La broche digital 2
Cette broche est connectée a la broche XERR du TLC5940, elle est active si le TLC est en surchauffe ou si une connexion entre un actionneur et la puce est interrompu 
 - #define XERR 2 // pin to catch TLC error (PD2)

### La broche digital 5
 - Cette broche est connectée à une LED pour pouvoir afficher les ERREURS captées par la broche XERR.
 - Elle est aussi utile pour debugger visuellement un programme avec la fonction digitalWrite(ledPin, HIGH/LOW);
 - #define ledPin 5 // pin to display TLC error

### Les broches A2, A1, D6, D7, D8
 - Ces broches sont utilisables pour ajouter des capteurs, par exemple un bouton pour activer la lecture, etc.
 - Elles sont accessibles sur le coté de la carte (cf: capture d'écran ci-joint).

### Les fonctions de la librairie
- La librairie TLC5940 comporte un ensemble de fonctions qui permettent de programmer l'intencité du courant sur chaque sorties
- Tlc.set( channel, valeur 12 bit ); // [0,4095]
- Tlc.update();
- Voir les exemples fournis avec cette librairie
 - Documents/Arduino/libraries/Tlc5940/examples

## Les données importantes
- Avant de brancher une LED il faut relever le courant MAXIMUM qu'elle consomme, puis en fonction de cette valeur ajuster la résistance R5 sur la carte (cf: capture d'écran ci-joint).
 - La formule qui permet de calculer la valeur de cette résistance est a la page 14 du datasheet : http://www.ti.com/lit/gpn/tlc5940

# TODO
- add auto-reset
