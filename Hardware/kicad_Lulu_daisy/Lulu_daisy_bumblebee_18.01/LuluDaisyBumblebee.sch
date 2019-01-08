EESchema Schematic File Version 4
LIBS:power
LIBS:device
LIBS:74xx
LIBS:audio
LIBS:interface
LIBS:LuluDaisyBumblebee-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED:SK6812MINI D0
U 1 1 5BFFEDC1
P 3500 2150
F 0 "D0" H 3841 2196 50  0000 L CNN
F 1 "SK6812MINI" H 3841 2105 50  0000 L CNN
F 2 "LEDs_custom:LED_SK6812MINI_PLCC4_3.5x3.5mm_P1.75mm_CUSTOM" H 3550 1850 50  0001 L TNN
F 3 "https://cdn-shop.adafruit.com/product-files/2686/SK6812MINI_REV.01-1-2.pdf" H 3600 1775 50  0001 L TNN
	1    3500 2150
	1    0    0    -1  
$EndComp
$Comp
L pspice:CAP C0
U 1 1 5BFFEEB8
P 3500 2700
F 0 "C0" H 3322 2654 50  0000 R CNN
F 1 "CAP" H 3322 2745 50  0000 R CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3500 2700 50  0001 C CNN
F 3 "~" H 3500 2700 50  0001 C CNN
	1    3500 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	3500 2950 2900 2950
Wire Wire Line
	2900 2950 2900 1850
Wire Wire Line
	2900 1850 3500 1850
$Comp
L Connector:Conn_01x01_Male H2
U 1 1 5C0175DC
P 4500 2700
F 0 "H2" H 4600 2751 50  0000 L CNN
F 1 "MountingHole_Pad" H 4600 2660 50  0000 L CNN
F 2 "Connecetors_sewing:bee_pad" H 4500 2700 50  0001 C CNN
F 3 "~" H 4500 2700 50  0001 C CNN
	1    4500 2700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4300 2700 3950 2700
Wire Wire Line
	3950 2700 3950 2450
Wire Wire Line
	3950 2450 3500 2450
Connection ~ 3500 2450
$Comp
L Connector:Conn_01x01_Male H1
U 1 1 5C01812F
P 4000 2150
F 0 "H1" H 4100 2201 50  0000 L CNN
F 1 "MountingHole_Pad" H 4100 2110 50  0000 L CNN
F 2 "Connecetors_sewing:bee_pad" H 4000 2150 50  0001 C CNN
F 3 "~" H 4000 2150 50  0001 C CNN
	1    4000 2150
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x01_Male H4
U 1 1 5C018158
P 2900 1650
F 0 "H4" H 3000 1701 50  0000 L CNN
F 1 "MountingHole_Pad" H 3000 1610 50  0000 L CNN
F 2 "Connecetors_sewing:bee_pad" H 2900 1650 50  0001 C CNN
F 3 "~" H 2900 1650 50  0001 C CNN
	1    2900 1650
	0    1    1    0   
$EndComp
Connection ~ 2900 1850
$Comp
L Connector:Conn_01x01_Male H3
U 1 1 5C0181A9
P 3200 1950
F 0 "H3" H 3300 2001 50  0000 L CNN
F 1 "MountingHole_Pad" H 3300 1910 50  0000 L CNN
F 2 "Connecetors_sewing:bee_pad" H 3200 1950 50  0001 C CNN
F 3 "~" H 3200 1950 50  0001 C CNN
	1    3200 1950
	0    1    1    0   
$EndComp
$EndSCHEMATC
