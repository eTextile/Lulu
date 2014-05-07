lucette_seq
===========
/////////// Caractéristiques de la carte :
	- 16 voies 12bits PWM (TLC5940)
	- courant de sortie max 120 mA / 3.3V
	- microcontroller Atmeg328
	- interface série
	- chargeur lithium-ion intégré : recharge de la batterie par mini USB
	- interrupter ON/OFF

/////////// Configurer l'IDE Arduino 
La première étape consiste à installer la librairie TLC5940 dans le répertoire
	- Documents/Arduino/libraries/Tlc5940
La doc sur arduino.cc
	- http://www.arduino.cc/playground/learning/TLC5940
Le lien directe de la lib sur google code
	- http://code.google.com/p/tlc5940arduino/downloads/detail?name=Tlc5940_r014_2.zip&can=2&q=
Choisir le type de carte dans le menu de l'IDE Arduino
	- Arduino Pro or Pro Mini (3.3V, 8MHz) / ATmega328
Pour envoyer un programme c'est comme avec une Arduino mais il faut appuyer sur le bouton reset de la carte au moment d'envoyer le programme.

/////////// Les broches/pin de l'ATmega328
// La broche 2
Cette broche est connectée a la broche XERR du TLC5940. elle est active si le TLC est en surchauffe ou si une connexion entre un actionneur et la puce est interrompu 
	#define XERR      2     // pin to trigger TLC error (PD2)

// La broche 5
Cette broche est connectée à une LED pour pouvoir ficher les ERREURS captées par la broche XERR.
Elle est aussi utile pour debugger visuellement un programme avec la fonction digitalWrite(ledPin, HIGH/LOW);
	#define ledPin      5    // pin to display TLC error

// Les broches A2, A1, D6, D7, D8
Ces broches sont utilisables pour ajouter des capteurs, par exemple un bouton pour activer la lecture, etc.
Elles sont accessibles sur le coté de la carte (cf: capture d'écran ci-joint).

/////////// Les fonctions de la librairie
Pour commencer tu peux jouer avec les fonctions suivantes pour moduler le courant sur chaque sorties
	- Tlc.set( channel, valeur 12 bit ); // [0,4095]
	- Tlc.update();
La librairie comporte des exemples utiles
	- Documents/Arduino/libraries/Tlc5940/examples

/////////// Les données importantes
Avant de brancher un vibreur il faut calculer le courant MAXIMUM qu'il consomme et en fonction de cette valeur ajuster la résistance R5 sur la carte (cf: capture d'écran ci-joint).
La formule qui permet de calculer la valeur de cette résistance est a la page 14 du datasheet
	- http://www.ti.com/lit/gpn/tlc5940

/////////// Les détails de l'électronique de la carte 
Les fonctions de chacune des broches de la carte sont annotées en blanc sur celle-ci
les fichiers sources de la carte et les docs des composants utilisés sont téléchargeables plus bas
