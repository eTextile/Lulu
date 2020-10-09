EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Lulu_star"
Date "2018-08-21"
Rev "2.1.2"
Comp "https://lulu.etextile.org/"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L power:+3.3V #PWR0101
U 1 1 5B7C4702
P 5800 3250
F 0 "#PWR0101" H 5800 3100 50  0001 C CNN
F 1 "+3.3V" H 5815 3423 50  0000 C CNN
F 2 "" H 5800 3250 50  0001 C CNN
F 3 "" H 5800 3250 50  0001 C CNN
	1    5800 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5B7C4F4F
P 5150 5000
F 0 "#PWR0102" H 5150 4750 50  0001 C CNN
F 1 "GND" H 5155 4827 50  0000 C CNN
F 2 "" H 5150 5000 50  0001 C CNN
F 3 "" H 5150 5000 50  0001 C CNN
	1    5150 5000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5B7C8445
P 5800 4650
F 0 "R2" H 5870 4696 50  0000 L CNN
F 1 "2.7 Ohm" H 5870 4605 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5730 4650 50  0001 C CNN
F 3 "~" H 5800 4650 50  0001 C CNN
	1    5800 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:LED_PAD LED1
U 1 1 5B7C84D4
P 5800 3550
F 0 "LED1" V 5846 3692 50  0000 L CNN
F 1 "LED_PAD" V 5755 3692 50  0000 L CNN
F 2 "Lulu_footprints:Lulu_side_LED" H 5800 3550 50  0001 C CNN
F 3 "https://github.com/eTextile/Lulu/blob/master/Hardware/DOCs/OSRAM_OSLON.pdf" H 5800 3550 50  0001 C CNN
	1    5800 3550
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_NMOS_GSD Q1
U 1 1 5B7C8ADD
P 5700 4050
F 0 "Q1" H 5905 4096 50  0000 L CNN
F 1 "Q_NMOS_GSD" H 5905 4005 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5900 4150 50  0001 C CNN
F 3 "https://github.com/eTextile/Lulu/blob/master/Hardware/DOCs/irlml2060pbf.pdf" H 5700 4050 50  0001 C CNN
	1    5700 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NPN_BEC T1
U 1 1 5B7C8DF6
P 5250 4400
F 0 "T1" H 5441 4446 50  0000 L CNN
F 1 "Q_NPN_BEC" H 5441 4355 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 5450 4500 50  0001 C CNN
F 3 "https://github.com/eTextile/Lulu/blob/master/Hardware/DOCs/MMBT2222A.pdf" H 5250 4400 50  0001 C CNN
	1    5250 4400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4850 4050 5150 4050
Wire Wire Line
	5800 3700 5800 3850
Wire Wire Line
	5800 3250 5800 3400
Wire Wire Line
	5800 4250 5800 4400
Wire Wire Line
	5450 4400 5800 4400
Connection ~ 5800 4400
Wire Wire Line
	5800 4400 5800 4500
Wire Wire Line
	5150 4600 5150 4900
Wire Wire Line
	5150 4200 5150 4050
Connection ~ 5150 4050
Wire Wire Line
	5150 4050 5500 4050
Wire Wire Line
	5800 4800 5800 4900
Wire Wire Line
	5800 4900 5150 4900
Connection ~ 5150 4900
Wire Wire Line
	5150 4900 5150 5000
Wire Wire Line
	4550 4050 4350 4050
Text Label 4100 4050 0    50   ~ 0
PWM
Wire Wire Line
	6000 3550 6700 3550
Text Label 6350 3550 0    50   ~ 0
thermal
Entry Wire Line
	5800 3550 5900 3650
$Comp
L power:GND #PWR0103
U 1 1 5B7C9260
P 7050 5000
F 0 "#PWR0103" H 7050 4750 50  0001 C CNN
F 1 "GND" H 7055 4827 50  0000 C CNN
F 2 "" H 7050 5000 50  0001 C CNN
F 3 "" H 7050 5000 50  0001 C CNN
	1    7050 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 5000 7050 4750
Text Label 7050 4800 0    50   ~ 0
thermal
$Comp
L Connector:Conn_01x03_Female J1
U 1 1 5B7D3F18
P 7250 4200
F 0 "J1" H 7277 4226 50  0000 L CNN
F 1 "Conn_01x03_Female" H 7277 4135 50  0000 L CNN
F 2 "Lulu_footprints:Lulu_brass_tube_pad" H 7250 4200 50  0001 C CNN
F 3 "~" H 7250 4200 50  0001 C CNN
	1    7250 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 4100 6750 4100
Text Label 6750 4300 0    50   ~ 0
PWM
$Comp
L power:GND #PWR0104
U 1 1 5B7D4527
P 6650 5000
F 0 "#PWR0104" H 6650 4750 50  0001 C CNN
F 1 "GND" H 6655 4827 50  0000 C CNN
F 2 "" H 6650 5000 50  0001 C CNN
F 3 "" H 6650 5000 50  0001 C CNN
	1    6650 5000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0105
U 1 1 5B7D46B5
P 6750 3900
F 0 "#PWR0105" H 6750 3750 50  0001 C CNN
F 1 "+3.3V" H 6765 4073 50  0000 C CNN
F 2 "" H 6750 3900 50  0001 C CNN
F 3 "" H 6750 3900 50  0001 C CNN
	1    6750 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 3900 6750 4100
$Comp
L Device:R R1
U 1 1 5B7CC755
P 4700 4050
F 0 "R1" V 4493 4050 50  0000 C CNN
F 1 "47 K" V 4584 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4630 4050 50  0001 C CNN
F 3 "~" H 4700 4050 50  0001 C CNN
	1    4700 4050
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5B90D0C4
P 4350 4400
F 0 "R3" V 4143 4400 50  0000 C CNN
F 1 "10 K" V 4234 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4280 4400 50  0001 C CNN
F 3 "~" H 4350 4400 50  0001 C CNN
	1    4350 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 4250 4350 4050
Connection ~ 4350 4050
Wire Wire Line
	4350 4050 4050 4050
$Comp
L power:GND #PWR0106
U 1 1 5B90D60D
P 4350 5000
F 0 "#PWR0106" H 4350 4750 50  0001 C CNN
F 1 "GND" H 4355 4827 50  0000 C CNN
F 2 "" H 4350 5000 50  0001 C CNN
F 3 "" H 4350 5000 50  0001 C CNN
	1    4350 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 4550 4350 5000
Wire Wire Line
	6650 4200 6650 5000
Wire Wire Line
	7050 4300 6750 4300
Wire Wire Line
	6650 4200 7050 4200
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20MU U1
U 1 1 5E567FCD
P 3150 4350
F 0 "U1" H 2610 4396 50  0000 R CNN
F 1 "ATtiny85-20MU" H 2610 4305 50  0000 R CNN
F 2 "Package_DFN_QFN:QFN-20-1EP_4x4mm_P0.5mm_EP2.25x2.25mm" H 3150 4350 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 3150 4350 50  0001 C CNN
	1    3150 4350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
