EESchema Schematic File Version 4
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
L Device:Rotary_Encoder_Switch RE1
U 1 1 5D8A6DDB
P 5800 3800
F 0 "RE1" H 5800 4167 50  0000 C CNN
F 1 "Rotary_Encoder_Switch" H 5800 4076 50  0000 C CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC12E-Switch_Vertical_H20mm" H 5650 3960 50  0001 C CNN
F 3 "~" H 5800 4060 50  0001 C CNN
	1    5800 3800
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5D8A6F76
P 7250 3850
F 0 "SW2" H 7250 4135 50  0000 C CNN
F 1 "SW_Push" H 7250 4044 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H5mm" H 7250 4050 50  0001 C CNN
F 3 "" H 7250 4050 50  0001 C CNN
	1    7250 3850
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5D8A6FFA
P 4450 3800
F 0 "SW1" H 4450 4085 50  0000 C CNN
F 1 "SW_Push" H 4450 3994 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm_H5mm" H 4450 4000 50  0001 C CNN
F 3 "" H 4450 4000 50  0001 C CNN
	1    4450 3800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0115
U 1 1 5D8C5C29
P 4700 3700
F 0 "#PWR0115" H 4700 3550 50  0001 C CNN
F 1 "+5V" H 4715 3873 50  0000 C CNN
F 2 "" H 4700 3700 50  0001 C CNN
F 3 "" H 4700 3700 50  0001 C CNN
	1    4700 3700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0116
U 1 1 5D8C5C52
P 7500 3750
F 0 "#PWR0116" H 7500 3600 50  0001 C CNN
F 1 "+5V" H 7515 3923 50  0000 C CNN
F 2 "" H 7500 3750 50  0001 C CNN
F 3 "" H 7500 3750 50  0001 C CNN
	1    7500 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5D8C5C9A
P 4250 3950
F 0 "R1" H 4320 3996 50  0000 L CNN
F 1 "10k" V 4250 3950 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4180 3950 50  0001 C CNN
F 3 "~" H 4250 3950 50  0001 C CNN
	1    4250 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5D8C5CF7
P 7050 4000
F 0 "R2" H 7120 4046 50  0000 L CNN
F 1 "10k" V 7050 4000 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6980 4000 50  0001 C CNN
F 3 "~" H 7050 4000 50  0001 C CNN
	1    7050 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 5D8C5D3A
P 4250 4100
F 0 "#PWR0117" H 4250 3850 50  0001 C CNN
F 1 "GND" H 4100 4000 50  0000 C CNN
F 2 "" H 4250 4100 50  0001 C CNN
F 3 "" H 4250 4100 50  0001 C CNN
	1    4250 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 5D8C5D67
P 7050 4150
F 0 "#PWR0118" H 7050 3900 50  0001 C CNN
F 1 "GND" H 6900 4050 50  0000 C CNN
F 2 "" H 7050 4150 50  0001 C CNN
F 3 "" H 7050 4150 50  0001 C CNN
	1    7050 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 3800 4700 3800
Wire Wire Line
	4700 3800 4700 3700
Wire Wire Line
	7450 3850 7500 3850
Wire Wire Line
	7500 3850 7500 3750
$Comp
L power:+5V #PWR0119
U 1 1 5D8C5E49
P 5800 3400
F 0 "#PWR0119" H 5800 3250 50  0001 C CNN
F 1 "+5V" H 5815 3573 50  0000 C CNN
F 2 "" H 5800 3400 50  0001 C CNN
F 3 "" H 5800 3400 50  0001 C CNN
	1    5800 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R3
U 1 1 5D8C5E76
P 5400 3750
F 0 "R3" H 5470 3796 50  0000 L CNN
F 1 "10k" V 5400 3750 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5330 3750 50  0001 C CNN
F 3 "~" H 5400 3750 50  0001 C CNN
	1    5400 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5D8C5EC1
P 6300 3750
F 0 "R5" H 6370 3796 50  0000 L CNN
F 1 "10k" V 6300 3750 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6230 3750 50  0001 C CNN
F 3 "~" H 6300 3750 50  0001 C CNN
	1    6300 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0120
U 1 1 5D8C5FC2
P 6150 4150
F 0 "#PWR0120" H 6150 4000 50  0001 C CNN
F 1 "+5V" H 6165 4323 50  0000 C CNN
F 2 "" H 6150 4150 50  0001 C CNN
F 3 "" H 6150 4150 50  0001 C CNN
	1    6150 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5D8C5FF3
P 5700 4350
F 0 "R4" H 5770 4396 50  0000 L CNN
F 1 "10k" V 5700 4350 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5630 4350 50  0001 C CNN
F 3 "~" H 5700 4350 50  0001 C CNN
	1    5700 4350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 5D8C603C
P 5700 4500
F 0 "#PWR0121" H 5700 4250 50  0001 C CNN
F 1 "GND" H 5500 4400 50  0000 C CNN
F 2 "" H 5700 4500 50  0001 C CNN
F 3 "" H 5700 4500 50  0001 C CNN
	1    5700 4500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 5D8C606F
P 5400 3900
F 0 "#PWR0122" H 5400 3650 50  0001 C CNN
F 1 "GND" H 5405 3727 50  0000 C CNN
F 2 "" H 5400 3900 50  0001 C CNN
F 3 "" H 5400 3900 50  0001 C CNN
	1    5400 3900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 5D8C60A2
P 6300 3900
F 0 "#PWR0123" H 6300 3650 50  0001 C CNN
F 1 "GND" H 6305 3727 50  0000 C CNN
F 2 "" H 6300 3900 50  0001 C CNN
F 3 "" H 6300 3900 50  0001 C CNN
	1    6300 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 3600 5400 3500
Wire Wire Line
	5400 3500 5700 3500
Wire Wire Line
	5800 3500 5800 3400
Wire Wire Line
	5900 3500 6300 3500
Wire Wire Line
	6300 3500 6300 3600
Wire Wire Line
	5700 4100 5700 4200
Wire Wire Line
	5900 4100 5900 4250
Wire Wire Line
	5900 4250 6150 4250
Wire Wire Line
	6150 4250 6150 4150
Text GLabel 4150 3800 0    50   Input ~ 0
SW1
Wire Wire Line
	4150 3800 4250 3800
Connection ~ 4250 3800
Text GLabel 6950 3850 0    50   Input ~ 0
SW2
Wire Wire Line
	6950 3850 7050 3850
Connection ~ 7050 3850
Text GLabel 5550 4200 0    50   Input ~ 0
RE1
Wire Wire Line
	5550 4200 5700 4200
Connection ~ 5700 4200
Text GLabel 5300 3500 0    50   Input ~ 0
RE_B
Wire Wire Line
	5300 3500 5400 3500
Connection ~ 5400 3500
Text GLabel 6400 3500 2    50   Input ~ 0
RE_A
Wire Wire Line
	6400 3500 6300 3500
Connection ~ 6300 3500
$Comp
L Device:LED D1
U 1 1 5DA0654F
P 5950 5100
F 0 "D1" H 5942 4845 50  0000 C CNN
F 1 "LED" H 5942 4936 50  0000 C CNN
F 2 "LED_THT:LED_D5.0mm" H 5950 5100 50  0001 C CNN
F 3 "~" H 5950 5100 50  0001 C CNN
	1    5950 5100
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 5DA0659A
P 5650 5100
F 0 "R6" H 5720 5146 50  0000 L CNN
F 1 "330" V 5650 5100 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5580 5100 50  0001 C CNN
F 3 "~" H 5650 5100 50  0001 C CNN
	1    5650 5100
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5DA065FB
P 6250 5200
F 0 "#PWR0101" H 6250 4950 50  0001 C CNN
F 1 "GND" H 6400 5100 50  0000 C CNN
F 2 "" H 6250 5200 50  0001 C CNN
F 3 "" H 6250 5200 50  0001 C CNN
	1    6250 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 5100 6250 5100
Wire Wire Line
	6250 5100 6250 5200
Text GLabel 5500 5100 0    50   Input ~ 0
LED
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 5DA070DE
P 3100 3800
F 0 "J1" H 3206 4078 50  0000 C CNN
F 1 "Conn_01x04_Male" H 3206 3987 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 3100 3800 50  0001 C CNN
F 3 "~" H 3100 3800 50  0001 C CNN
	1    3100 3800
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 5DA0716A
P 8300 3750
F 0 "J2" H 8273 3723 50  0000 R CNN
F 1 "Conn_01x04_Male" H 8273 3632 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8300 3750 50  0001 C CNN
F 3 "~" H 8300 3750 50  0001 C CNN
	1    8300 3750
	-1   0    0    -1  
$EndComp
Text GLabel 3300 3700 2    50   Input ~ 0
SW1
Text GLabel 3300 3800 2    50   Input ~ 0
RE1
Text GLabel 8100 3750 0    50   Input ~ 0
SW2
$Comp
L power:GND #PWR0102
U 1 1 5DA07444
P 3400 4050
F 0 "#PWR0102" H 3400 3800 50  0001 C CNN
F 1 "GND" H 3250 3950 50  0000 C CNN
F 2 "" H 3400 4050 50  0001 C CNN
F 3 "" H 3400 4050 50  0001 C CNN
	1    3400 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 4000 3400 4000
Wire Wire Line
	3400 4000 3400 4050
Text GLabel 3300 3900 2    50   Input ~ 0
RE_A
Text GLabel 8100 3850 0    50   Input ~ 0
RE_B
Text GLabel 8100 3650 0    50   Input ~ 0
LED
$Comp
L power:+5V #PWR0103
U 1 1 5DA076C9
P 7750 3550
F 0 "#PWR0103" H 7750 3400 50  0001 C CNN
F 1 "+5V" H 7765 3723 50  0000 C CNN
F 2 "" H 7750 3550 50  0001 C CNN
F 3 "" H 7750 3550 50  0001 C CNN
	1    7750 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 3550 7750 3950
Wire Wire Line
	7750 3950 8100 3950
$EndSCHEMATC
