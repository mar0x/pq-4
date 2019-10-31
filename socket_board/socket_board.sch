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
P 3450 3700
F 0 "J5" H 3430 4025 50  0000 C CNN
F 1 "AudioJack3" H 3430 3934 50  0000 C CNN
F 2 "Connectors:phone-jack-6.3" H 3450 3700 50  0001 C CNN
F 3 "~" H 3450 3700 50  0001 C CNN
	1    3450 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector:DIN-5_180degree J2
U 1 1 5DB63F10
P 5950 2100
F 0 "J2" H 5950 1826 50  0000 C CNN
F 1 "DIN-5_180degree" H 5950 1735 50  0000 C CNN
F 2 "Connectors:DIN5MIDI-OOTDTY" H 5950 2100 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 5950 2100 50  0001 C CNN
	1    5950 2100
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
P 5950 3150
F 0 "J3" H 5950 2876 50  0000 C CNN
F 1 "DIN-5_180degree" H 5950 2785 50  0000 C CNN
F 2 "Connectors:DIN5MIDI-OOTDTY" H 5950 3150 50  0001 C CNN
F 3 "http://www.mouser.com/ds/2/18/40_c091_abd_e-75918.pdf" H 5950 3150 50  0001 C CNN
	1    5950 3150
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
	1    0    0    -1  
$EndComp
Text GLabel 4000 1850 2    50   Input ~ 0
POW1
Text GLabel 4000 2050 2    50   Input ~ 0
POW2
Text GLabel 3950 2850 2    50   Input ~ 0
IN_S
Text GLabel 3950 3050 2    50   Input ~ 0
IN_T
Text GLabel 3900 3600 2    50   Input ~ 0
OUT_S
Text GLabel 3900 3800 2    50   Input ~ 0
OUT_T
Text GLabel 6450 2000 2    50   Input ~ 0
MIN_5
Text GLabel 6450 3050 2    50   Input ~ 0
MOUT_5
Text GLabel 5500 2000 0    50   Input ~ 0
MIN_4
Text GLabel 5500 3050 0    50   Input ~ 0
MOUT_4
Text GLabel 6450 2800 2    50   Input ~ 0
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
	3650 3600 3900 3600
Wire Wire Line
	3650 3800 3900 3800
Wire Wire Line
	5650 2000 5500 2000
Wire Wire Line
	6250 2000 6450 2000
Wire Wire Line
	5500 3050 5650 3050
Wire Wire Line
	6250 3050 6450 3050
Wire Wire Line
	6450 2800 5950 2800
Wire Wire Line
	5950 2800 5950 2850
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
L Connector:Conn_01x04_Male J7
U 1 1 5DB64B97
P 2000 3200
F 0 "J7" H 2106 3478 50  0000 C CNN
F 1 "Conn_01x04_Male" H 2106 3387 50  0000 C CNN
F 2 "Connector_JST:JST_EH_B04B-EH-A_1x04_P2.50mm_Vertical" H 2000 3200 50  0001 C CNN
F 3 "~" H 2000 3200 50  0001 C CNN
	1    2000 3200
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J8
U 1 1 5DB64BED
P 7550 2600
F 0 "J8" H 7523 2623 50  0000 R CNN
F 1 "Conn_01x05_Male" H 7523 2532 50  0000 R CNN
F 2 "Connector_JST:JST_EH_B05B-EH-A_1x05_P2.50mm_Vertical" H 7550 2600 50  0001 C CNN
F 3 "~" H 7550 2600 50  0001 C CNN
	1    7550 2600
	-1   0    0    -1  
$EndComp
Text GLabel 2150 1750 2    50   Input ~ 0
POW1
Text GLabel 2150 1850 2    50   Input ~ 0
POW2
Text GLabel 2200 3100 2    50   Input ~ 0
IN_S
Text GLabel 2200 3200 2    50   Input ~ 0
IN_T
Text GLabel 2200 3300 2    50   Input ~ 0
OUT_S
Text GLabel 2200 3400 2    50   Input ~ 0
OUT_T
Text GLabel 7350 2700 0    50   Input ~ 0
MIN_5
Text GLabel 7350 2800 0    50   Input ~ 0
MIN_4
Text GLabel 7350 2500 0    50   Input ~ 0
MOUT_2
Text GLabel 7350 2600 0    50   Input ~ 0
MOUT_4
Text GLabel 7350 2400 0    50   Input ~ 0
MOUT_5
$EndSCHEMATC
