EESchema Schematic File Version 4
LIBS:socket_board-cache
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
L Connector:AudioJack3 J5
U 1 1 5DB63E32
P 3450 4400
F 0 "J5" H 3430 4725 50  0000 C CNN
F 1 "AudioJack3" H 3430 4634 50  0000 C CNN
F 2 "Connectors:phone-jack-6.3" H 3450 4400 50  0001 C CNN
F 3 "~" H 3450 4400 50  0001 C CNN
	1    3450 4400
	1    0    0    1   
$EndComp
$Comp
L Connector:DIN-5_180degree J2
U 1 1 5DB63F10
P 7250 2100
F 0 "J2" H 7250 1826 50  0000 C CNN
F 1 "DIN-5_180degree" H 7250 1735 50  0000 C CNN
F 2 "Connectors:DIN5MIDI-OOTDTY" H 7250 2100 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 7250 2100 50  0001 C CNN
	1    7250 2100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Barrel_Jack_Switch J1
U 1 1 5DB640A8
P 3450 1950
F 0 "J1" H 3505 2267 50  0000 C CNN
F 1 "Barrel_Jack_Switch" H 3505 2176 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Wuerth_6941xx301002" H 3500 1910 50  0001 C CNN
F 3 "~" H 3500 1910 50  0001 C CNN
	1    3450 1950
	1    0    0    -1  
$EndComp
$Comp
L Connector:DIN-5_180degree J3
U 1 1 5DB64337
P 7250 3150
F 0 "J3" H 7250 2876 50  0000 C CNN
F 1 "DIN-5_180degree" H 7250 2785 50  0000 C CNN
F 2 "Connectors:DIN5MIDI-OOTDTY" H 7250 3150 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 7250 3150 50  0001 C CNN
	1    7250 3150
	1    0    0    -1  
$EndComp
$Comp
L Connector:AudioJack3 J4
U 1 1 5DB64365
P 3450 2950
F 0 "J4" H 3430 3275 50  0000 C CNN
F 1 "AudioJack3" H 3430 3184 50  0000 C CNN
F 2 "Connectors:phone-jack-6.3" H 3450 2950 50  0001 C CNN
F 3 "~" H 3450 2950 50  0001 C CNN
	1    3450 2950
	1    0    0    1   
$EndComp
Text GLabel 4000 1850 2    50   Input ~ 0
POW1
Text GLabel 4000 2050 2    50   Input ~ 0
POW2
Text GLabel 3950 2850 2    50   Input ~ 0
IN_T
Text GLabel 4250 4550 3    50   Input ~ 0
OUT_T
Text GLabel 7750 2000 2    50   Input ~ 0
MIN_5
Text GLabel 7750 3050 2    50   Input ~ 0
MOUT_5
Text GLabel 6800 2000 0    50   Input ~ 0
MIN_4
Text GLabel 6800 3050 0    50   Input ~ 0
MOUT_4
Text GLabel 7750 2800 2    50   Input ~ 0
MOUT_2
Wire Wire Line
	3750 1850 4000 1850
Wire Wire Line
	3750 2050 4000 2050
Wire Wire Line
	3650 2850 3950 2850
Wire Wire Line
	3650 3050 3950 3050
Wire Wire Line
	3650 4500 3900 4500
Wire Wire Line
	6950 2000 6800 2000
Wire Wire Line
	7550 2000 7750 2000
Wire Wire Line
	6800 3050 6950 3050
Wire Wire Line
	7550 3050 7750 3050
Wire Wire Line
	7750 2800 7250 2800
Wire Wire Line
	7250 2800 7250 2850
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 5DB64A49
P 1950 1750
F 0 "J6" H 2056 1928 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2056 1837 50  0000 C CNN
F 2 "Connector_JST:JST_EH_B02B-EH-A_1x02_P2.50mm_Vertical" H 1950 1750 50  0001 C CNN
F 3 "~" H 1950 1750 50  0001 C CNN
	1    1950 1750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J8
U 1 1 5DB64BED
P 8850 2600
F 0 "J8" H 8823 2623 50  0000 R CNN
F 1 "Conn_01x05_Male" H 8823 2532 50  0000 R CNN
F 2 "Connector_JST:JST_EH_B05B-EH-A_1x05_P2.50mm_Vertical" H 8850 2600 50  0001 C CNN
F 3 "~" H 8850 2600 50  0001 C CNN
	1    8850 2600
	-1   0    0    -1  
$EndComp
Text GLabel 2150 1750 2    50   Input ~ 0
POW1
Text GLabel 2150 1850 2    50   Input ~ 0
POW2
Text GLabel 2100 3100 2    50   Input ~ 0
IN_T
Text GLabel 2100 2900 2    50   Input ~ 0
OUT_T
Text GLabel 8650 2800 0    50   Input ~ 0
MIN_5
Text GLabel 8650 2700 0    50   Input ~ 0
MIN_4
Text GLabel 8650 2500 0    50   Input ~ 0
MOUT_2
Text GLabel 8650 2400 0    50   Input ~ 0
MOUT_4
Text GLabel 8650 2600 0    50   Input ~ 0
MOUT_5
$Comp
L relay_omron_g6k-2:G6K-2 K1
U 1 1 5DC3141B
P 5300 4050
F 0 "K1" V 4533 4050 50  0000 C CNN
F 1 "G6K-2" V 4624 4050 50  0000 C CNN
F 2 "Relay_SMD:Relay_DPDT_Omron_G6K-2F-Y" H 5950 4000 50  0001 L CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g6k.pdf" H 5100 4050 50  0001 C CNN
	1    5300 4050
	0    1    1    0   
$EndComp
$Comp
L Jumper:Jumper_3_Bridged12 JP1
U 1 1 5DC31772
P 4250 4300
F 0 "JP1" V 4204 4367 50  0000 L CNN
F 1 "Jumper_3_Bridged12" V 4295 4367 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4250 4300 50  0001 C CNN
F 3 "~" H 4250 4300 50  0001 C CNN
	1    4250 4300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5DC31AE2
P 3900 4500
F 0 "#PWR0101" H 3900 4250 50  0001 C CNN
F 1 "GND" H 3905 4327 50  0000 C CNN
F 2 "" H 3900 4500 50  0001 C CNN
F 3 "" H 3900 4500 50  0001 C CNN
	1    3900 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5DC3202F
P 3950 3050
F 0 "#PWR0102" H 3950 2800 50  0001 C CNN
F 1 "GND" H 3955 2877 50  0000 C CNN
F 2 "" H 3950 3050 50  0001 C CNN
F 3 "" H 3950 3050 50  0001 C CNN
	1    3950 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 4300 4100 4300
Text GLabel 5600 3950 2    50   Input ~ 0
IN_T
Text GLabel 5600 4150 2    50   Input ~ 0
OUT_T
Wire Wire Line
	4250 4050 5000 4050
$Comp
L power:GND #PWR0103
U 1 1 5DC32A91
P 2550 3050
F 0 "#PWR0103" H 2550 2800 50  0001 C CNN
F 1 "GND" H 2555 2877 50  0000 C CNN
F 2 "" H 2550 3050 50  0001 C CNN
F 3 "" H 2550 3050 50  0001 C CNN
	1    2550 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J9
U 1 1 5DC33310
P 2000 4200
F 0 "J9" H 2106 4378 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2106 4287 50  0000 C CNN
F 2 "Connector_JST:JST_EH_B02B-EH-A_1x02_P2.50mm_Vertical" H 2000 4200 50  0001 C CNN
F 3 "~" H 2000 4200 50  0001 C CNN
	1    2000 4200
	1    0    0    -1  
$EndComp
Text GLabel 5600 3650 2    50   Input ~ 0
REL+
Text GLabel 5000 3650 0    50   Input ~ 0
REL-
Text GLabel 2200 4200 2    50   Input ~ 0
REL+
Text GLabel 2200 4300 2    50   Input ~ 0
REL-
$Comp
L Connector:Conn_01x03_Male J7
U 1 1 5DCC416F
P 1900 3000
F 0 "J7" H 2006 3278 50  0000 C CNN
F 1 "Conn_01x03_Male" H 2006 3187 50  0000 C CNN
F 2 "Connector_JST:JST_EH_B03B-EH-A_1x03_P2.50mm_Vertical" H 1900 3000 50  0001 C CNN
F 3 "~" H 1900 3000 50  0001 C CNN
	1    1900 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 3000 2550 3000
Wire Wire Line
	2550 3000 2550 3050
$EndSCHEMATC
