EESchema Schematic File Version 4
EELAYER 30 0
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
L MCU_Microchip_ATmega:ATmega328P-AU U1
U 1 1 5E465EF5
P 4950 3550
F 0 "U1" H 4500 5050 50  0000 C CNN
F 1 "ATmega328P-AU" H 5350 2050 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 4950 3550 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 4950 3550 50  0001 C CNN
	1    4950 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:Rotary_Encoder SW1
U 1 1 601C4FD5
P 7650 4050
F 0 "SW1" V 7900 4000 50  0000 L CNN
F 1 "Rotary_Encoder" V 8000 3750 50  0000 L CNN
F 2 "Rotary_Encoder:RotaryEncoder_Alps_EC12E_Vertical_H20mm" H 7500 4210 50  0001 C CNN
F 3 "~" H 7650 4310 50  0001 C CNN
	1    7650 4050
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x08_Male J1
U 1 1 601C51ED
P 7550 5050
F 0 "J1" H 7523 5023 50  0000 R CNN
F 1 "Conn_01x08_Male" H 7523 4932 50  0000 R CNN
F 2 "Annular_LED_Ring:Annular_LED_Ring" H 7550 5050 50  0001 C CNN
F 3 "~" H 7550 5050 50  0001 C CNN
	1    7550 5050
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J2
U 1 1 601C53BB
P 2950 2450
F 0 "J2" H 2800 2850 50  0000 C CNN
F 1 "Conn_01x06_Male" H 2650 2750 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2950 2450 50  0001 C CNN
F 3 "~" H 2950 2450 50  0001 C CNN
	1    2950 2450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 601C5542
P 8350 2350
F 0 "J3" H 8323 2373 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8323 2282 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8350 2350 50  0001 C CNN
F 3 "~" H 8350 2350 50  0001 C CNN
	1    8350 2350
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 601C55B7
P 8350 2750
F 0 "J4" H 8323 2773 50  0000 R CNN
F 1 "Conn_01x03_Male" H 8323 2682 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8350 2750 50  0001 C CNN
F 3 "~" H 8350 2750 50  0001 C CNN
	1    8350 2750
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 601C5766
P 7200 5150
F 0 "R1" V 7250 5300 50  0000 C CNN
F 1 "220" V 7200 5150 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7130 5150 50  0001 C CNN
F 3 "~" H 7200 5150 50  0001 C CNN
	1    7200 5150
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 601C57EE
P 7200 5250
F 0 "R2" V 7250 5400 50  0000 C CNN
F 1 "220" V 7200 5250 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7130 5250 50  0001 C CNN
F 3 "~" H 7200 5250 50  0001 C CNN
	1    7200 5250
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 601C581D
P 7200 5350
F 0 "R3" V 7250 5500 50  0000 C CNN
F 1 "220" V 7200 5350 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7130 5350 50  0001 C CNN
F 3 "~" H 7200 5350 50  0001 C CNN
	1    7200 5350
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 601C584B
P 7200 5450
F 0 "R4" V 7250 5600 50  0000 C CNN
F 1 "220" V 7200 5450 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7130 5450 50  0001 C CNN
F 3 "~" H 7200 5450 50  0001 C CNN
	1    7200 5450
	0    1    1    0   
$EndComp
$Comp
L Device:R R5
U 1 1 601C61F7
P 7300 3900
F 0 "R5" H 7450 4000 50  0000 R CNN
F 1 "30k" V 7300 3950 39  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7230 3900 50  0001 C CNN
F 3 "~" H 7300 3900 50  0001 C CNN
	1    7300 3900
	-1   0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 601C62AB
P 8000 3900
F 0 "R6" H 7950 4000 50  0000 R CNN
F 1 "30k" V 8000 3950 39  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7930 3900 50  0001 C CNN
F 3 "~" H 8000 3900 50  0001 C CNN
	1    8000 3900
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 601C6317
P 4950 5050
F 0 "#PWR0101" H 4950 4800 50  0001 C CNN
F 1 "GND" H 4955 4877 50  0000 C CNN
F 2 "" H 4950 5050 50  0001 C CNN
F 3 "" H 4950 5050 50  0001 C CNN
	1    4950 5050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 601C6450
P 4950 2050
F 0 "#PWR0102" H 4950 1900 50  0001 C CNN
F 1 "+5V" H 4850 2200 50  0000 C CNN
F 2 "" H 4950 2050 50  0001 C CNN
F 3 "" H 4950 2050 50  0001 C CNN
	1    4950 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 601C65F1
P 7650 3750
F 0 "#PWR0103" H 7650 3600 50  0001 C CNN
F 1 "+5V" H 7665 3923 50  0000 C CNN
F 2 "" H 7650 3750 50  0001 C CNN
F 3 "" H 7650 3750 50  0001 C CNN
	1    7650 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 601C668B
P 7300 4050
F 0 "#PWR0104" H 7300 3800 50  0001 C CNN
F 1 "GND" H 7305 3877 50  0000 C CNN
F 2 "" H 7300 4050 50  0001 C CNN
F 3 "" H 7300 4050 50  0001 C CNN
	1    7300 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 601C66B0
P 8000 4050
F 0 "#PWR0105" H 8000 3800 50  0001 C CNN
F 1 "GND" H 8005 3877 50  0000 C CNN
F 2 "" H 8000 4050 50  0001 C CNN
F 3 "" H 8000 4050 50  0001 C CNN
	1    8000 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3750 7550 3750
Wire Wire Line
	7750 3750 8000 3750
$Comp
L Device:C_Small C2
U 1 1 601C7C77
P 4050 4850
F 0 "C2" H 4142 4896 50  0000 L CNN
F 1 "0.1u" H 4142 4805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4050 4850 50  0001 C CNN
F 3 "~" H 4050 4850 50  0001 C CNN
	1    4050 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 601C7DA3
P 3700 4850
F 0 "C1" H 3792 4896 50  0000 L CNN
F 1 "0.1u" H 3792 4805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3700 4850 50  0001 C CNN
F 3 "~" H 3700 4850 50  0001 C CNN
	1    3700 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 601C7DEE
P 3700 4750
F 0 "#PWR0108" H 3700 4600 50  0001 C CNN
F 1 "+5V" H 3715 4923 50  0000 C CNN
F 2 "" H 3700 4750 50  0001 C CNN
F 3 "" H 3700 4750 50  0001 C CNN
	1    3700 4750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0109
U 1 1 601C7E17
P 4050 4750
F 0 "#PWR0109" H 4050 4600 50  0001 C CNN
F 1 "+5V" H 4050 4900 50  0000 C CNN
F 2 "" H 4050 4750 50  0001 C CNN
F 3 "" H 4050 4750 50  0001 C CNN
	1    4050 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 601C7E40
P 3700 4950
F 0 "#PWR0110" H 3700 4700 50  0001 C CNN
F 1 "GND" H 3705 4777 50  0000 C CNN
F 2 "" H 3700 4950 50  0001 C CNN
F 3 "" H 3700 4950 50  0001 C CNN
	1    3700 4950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 601C7E69
P 4050 4950
F 0 "#PWR0111" H 4050 4700 50  0001 C CNN
F 1 "GND" H 4055 4777 50  0000 C CNN
F 2 "" H 4050 4950 50  0001 C CNN
F 3 "" H 4050 4950 50  0001 C CNN
	1    4050 4950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 601C8787
P 3150 2250
F 0 "#PWR0112" H 3150 2100 50  0001 C CNN
F 1 "+5V" H 3165 2423 50  0000 C CNN
F 2 "" H 3150 2250 50  0001 C CNN
F 3 "" H 3150 2250 50  0001 C CNN
	1    3150 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 601C882A
P 3550 2350
F 0 "#PWR0113" H 3550 2100 50  0001 C CNN
F 1 "GND" H 3555 2177 50  0000 C CNN
F 2 "" H 3550 2350 50  0001 C CNN
F 3 "" H 3550 2350 50  0001 C CNN
	1    3550 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2350 3550 2350
Text GLabel 3150 2450 2    50   Input ~ 0
RST
Text GLabel 5550 3850 2    50   Input ~ 0
RST
Text GLabel 3150 2550 2    50   Input ~ 0
SCK
Text GLabel 5550 2850 2    50   Input ~ 0
SCK
Text GLabel 3150 2650 2    50   Input ~ 0
MOSI
Text GLabel 5550 2650 2    50   Input ~ 0
MOSI
Text GLabel 3150 2750 2    50   Input ~ 0
MISO
Text GLabel 5550 2750 2    50   Input ~ 0
MISO
Text GLabel 3050 3350 2    50   Input ~ 0
SCL
Text GLabel 3050 3250 2    50   Input ~ 0
SDA
Text GLabel 5550 3750 2    50   Input ~ 0
SCL
Text GLabel 5550 3650 2    50   Input ~ 0
SDA
$Comp
L power:+5V #PWR0114
U 1 1 601C904B
P 5050 2050
F 0 "#PWR0114" H 5050 1900 50  0001 C CNN
F 1 "+5V" H 5150 2200 50  0000 C CNN
F 2 "" H 5050 2050 50  0001 C CNN
F 3 "" H 5050 2050 50  0001 C CNN
	1    5050 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C3
U 1 1 601C9074
P 3950 2450
F 0 "C3" H 4042 2496 50  0000 L CNN
F 1 "0.1u" H 4042 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3950 2450 50  0001 C CNN
F 3 "~" H 3950 2450 50  0001 C CNN
	1    3950 2450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 601C90B8
P 3950 2550
F 0 "#PWR0115" H 3950 2300 50  0001 C CNN
F 1 "GND" H 3955 2377 50  0000 C CNN
F 2 "" H 3950 2550 50  0001 C CNN
F 3 "" H 3950 2550 50  0001 C CNN
	1    3950 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 2350 4350 2350
Text GLabel 8150 3750 2    50   Input ~ 0
RE_A
Text GLabel 5550 2450 2    50   Input ~ 0
RE_A
Text GLabel 5550 2350 2    50   Input ~ 0
RE_B
Text GLabel 7150 3750 0    50   Input ~ 0
RE_B
Wire Wire Line
	7150 3750 7300 3750
Connection ~ 7300 3750
Wire Wire Line
	8150 3750 8000 3750
Connection ~ 8000 3750
$Comp
L Connector:Conn_01x06_Male J5
U 1 1 601C9CF5
P 2850 3450
F 0 "J5" H 2700 3850 50  0000 C CNN
F 1 "Conn_01x06_Male" H 2550 3750 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2850 3450 50  0001 C CNN
F 3 "~" H 2850 3450 50  0001 C CNN
	1    2850 3450
	1    0    0    -1  
$EndComp
Text GLabel 6900 4750 0    50   Input ~ 0
LED1
Text GLabel 6900 4850 0    50   Input ~ 0
LED2
Text GLabel 6900 4950 0    50   Input ~ 0
LED3
Text GLabel 6900 5050 0    50   Input ~ 0
LED4
Text GLabel 6900 5150 0    50   Input ~ 0
LED5
Text GLabel 6900 5250 0    50   Input ~ 0
LED6
Text GLabel 6900 5350 0    50   Input ~ 0
LED7
Text GLabel 6900 5450 0    50   Input ~ 0
LED8
Wire Wire Line
	7350 4750 6900 4750
Wire Wire Line
	6900 4850 7350 4850
Wire Wire Line
	7350 4950 6900 4950
Wire Wire Line
	6900 5050 7350 5050
Wire Wire Line
	6900 5150 7050 5150
Wire Wire Line
	7050 5250 6900 5250
Wire Wire Line
	6900 5350 7050 5350
Wire Wire Line
	7050 5450 6900 5450
Text GLabel 5550 3550 2    50   Input ~ 0
LED1
Text GLabel 5550 3450 2    50   Input ~ 0
LED2
Text GLabel 5550 3350 2    50   Input ~ 0
LED3
Text GLabel 5550 3250 2    50   Input ~ 0
LED4
Text GLabel 5550 2550 2    50   Input ~ 0
LED5
Text GLabel 5550 4750 2    50   Input ~ 0
LED6
Text GLabel 5550 4650 2    50   Input ~ 0
LED7
Text GLabel 5550 4550 2    50   Input ~ 0
LED8
Text GLabel 5550 4150 2    50   Input ~ 0
MCP_CS
Text GLabel 5550 4050 2    50   Input ~ 0
MCP_SHDN
$Comp
L Device:R R7
U 1 1 601CC93B
P 3150 3950
F 0 "R7" H 3150 4100 50  0000 R CNN
F 1 "30k" V 3150 4000 39  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3080 3950 50  0001 C CNN
F 3 "~" H 3150 3950 50  0001 C CNN
	1    3150 3950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R8
U 1 1 601CC99D
P 3350 3950
F 0 "R8" H 3350 4100 50  0000 R CNN
F 1 "30k" V 3350 4000 39  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3280 3950 50  0001 C CNN
F 3 "~" H 3350 3950 50  0001 C CNN
	1    3350 3950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R9
U 1 1 601CC9D9
P 3550 3950
F 0 "R9" H 3550 4100 50  0000 R CNN
F 1 "30k" V 3550 4000 39  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3480 3950 50  0001 C CNN
F 3 "~" H 3550 3950 50  0001 C CNN
	1    3550 3950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R10
U 1 1 601CCA15
P 3750 3950
F 0 "R10" H 3700 4100 50  0000 R CNN
F 1 "30k" V 3750 4000 39  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3680 3950 50  0001 C CNN
F 3 "~" H 3750 3950 50  0001 C CNN
	1    3750 3950
	-1   0    0    1   
$EndComp
Text GLabel 3900 3450 2    50   Input ~ 0
A0
Text GLabel 3900 3550 2    50   Input ~ 0
A1
Text GLabel 3900 3650 2    50   Input ~ 0
A2
Text GLabel 3900 3750 2    50   Input ~ 0
CHG
Wire Wire Line
	3050 3750 3750 3750
Wire Wire Line
	3050 3650 3550 3650
Wire Wire Line
	3050 3550 3350 3550
Wire Wire Line
	3050 3450 3150 3450
Wire Wire Line
	3150 3800 3150 3450
Connection ~ 3150 3450
Wire Wire Line
	3150 3450 3900 3450
Wire Wire Line
	3350 3800 3350 3550
Connection ~ 3350 3550
Wire Wire Line
	3350 3550 3900 3550
Wire Wire Line
	3550 3800 3550 3650
Connection ~ 3550 3650
Wire Wire Line
	3550 3650 3900 3650
Wire Wire Line
	3750 3800 3750 3750
Connection ~ 3750 3750
Wire Wire Line
	3750 3750 3900 3750
$Comp
L power:GND #PWR0117
U 1 1 601D022B
P 3150 4100
F 0 "#PWR0117" H 3150 3850 50  0001 C CNN
F 1 "GND" H 3155 3927 50  0000 C CNN
F 2 "" H 3150 4100 50  0001 C CNN
F 3 "" H 3150 4100 50  0001 C CNN
	1    3150 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 601D0262
P 3350 4100
F 0 "#PWR0118" H 3350 3850 50  0001 C CNN
F 1 "GND" H 3355 3927 50  0000 C CNN
F 2 "" H 3350 4100 50  0001 C CNN
F 3 "" H 3350 4100 50  0001 C CNN
	1    3350 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0119
U 1 1 601D0299
P 3550 4100
F 0 "#PWR0119" H 3550 3850 50  0001 C CNN
F 1 "GND" H 3555 3927 50  0000 C CNN
F 2 "" H 3550 4100 50  0001 C CNN
F 3 "" H 3550 4100 50  0001 C CNN
	1    3550 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 601D02D0
P 3750 4100
F 0 "#PWR0120" H 3750 3850 50  0001 C CNN
F 1 "GND" H 3755 3927 50  0000 C CNN
F 2 "" H 3750 4100 50  0001 C CNN
F 3 "" H 3750 4100 50  0001 C CNN
	1    3750 4100
	1    0    0    -1  
$EndComp
Text GLabel 5550 4350 2    50   Input ~ 0
A0
Text GLabel 5550 4450 2    50   Input ~ 0
A1
Text GLabel 5550 2950 2    50   Input ~ 0
A2
Text GLabel 5550 3050 2    50   Input ~ 0
CHG
$Comp
L ad5262:AD5262 U2
U 1 1 5E38ADD2
P 7650 2650
F 0 "U2" H 7300 3250 50  0000 C CNN
F 1 "AD5262" H 8000 2050 50  0000 C CNN
F 2 "Package_SO:TSSOP-16_4.4x5mm_P0.65mm" H 7650 1950 50  0001 C CNN
F 3 "https://www.analog.com/media/en/technical-documentation/data-sheets/AD5280_5282.pdf" H 7750 2550 50  0001 C CNN
	1    7650 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5E39246B
P 7600 3250
F 0 "#PWR0106" H 7600 3000 50  0001 C CNN
F 1 "GND" H 7605 3077 50  0000 C CNN
F 2 "" H 7600 3250 50  0001 C CNN
F 3 "" H 7600 3250 50  0001 C CNN
	1    7600 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3250 7600 3250
Connection ~ 7600 3250
Wire Wire Line
	7600 3250 7650 3250
$Comp
L power:+5V #PWR0107
U 1 1 5E39336E
P 7650 2050
F 0 "#PWR0107" H 7650 1900 50  0001 C CNN
F 1 "+5V" H 7700 2200 50  0000 C CNN
F 2 "" H 7650 2050 50  0001 C CNN
F 3 "" H 7650 2050 50  0001 C CNN
	1    7650 2050
	1    0    0    -1  
$EndComp
Text GLabel 7150 2350 0    50   Input ~ 0
SCK
Text GLabel 7150 2450 0    50   Input ~ 0
MOSI
Text GLabel 7150 2250 0    50   Input ~ 0
MISO
Text GLabel 7150 2550 0    50   Input ~ 0
MCP_CS
Text GLabel 6950 2850 0    50   Input ~ 0
MCP_SHDN
$Comp
L Device:R R11
U 1 1 5E39598F
P 7050 3000
F 0 "R11" H 7000 3100 50  0000 R CNN
F 1 "30k" V 7050 3000 39  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6980 3000 50  0001 C CNN
F 3 "~" H 7050 3000 50  0001 C CNN
	1    7050 3000
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 5E395ED2
P 7050 3250
F 0 "#PWR0116" H 7050 3000 50  0001 C CNN
F 1 "GND" H 7055 3077 50  0000 C CNN
F 2 "" H 7050 3250 50  0001 C CNN
F 3 "" H 7050 3250 50  0001 C CNN
	1    7050 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 3150 7050 3250
Wire Wire Line
	6950 2850 7050 2850
Connection ~ 7050 2850
Wire Wire Line
	7050 2850 7150 2850
NoConn ~ 7150 2750
$Comp
L power:+9V #PWR0121
U 1 1 5E3A4165
P 7550 2050
F 0 "#PWR0121" H 7550 1900 50  0001 C CNN
F 1 "+9V" H 7450 2200 50  0000 C CNN
F 2 "" H 7550 2050 50  0001 C CNN
F 3 "" H 7550 2050 50  0001 C CNN
	1    7550 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+9V #PWR0122
U 1 1 5E3A5490
P 6300 2050
F 0 "#PWR0122" H 6300 1900 50  0001 C CNN
F 1 "+9V" H 6200 2200 50  0000 C CNN
F 2 "" H 6300 2050 50  0001 C CNN
F 3 "" H 6300 2050 50  0001 C CNN
	1    6300 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0123
U 1 1 5E3A5F6A
P 6300 2350
F 0 "#PWR0123" H 6300 2100 50  0001 C CNN
F 1 "GND" H 6305 2177 50  0000 C CNN
F 2 "" H 6300 2350 50  0001 C CNN
F 3 "" H 6300 2350 50  0001 C CNN
	1    6300 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5E3A670C
P 6400 2200
F 0 "C5" H 6492 2246 50  0000 L CNN
F 1 "0.1u" H 6492 2155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6400 2200 50  0001 C CNN
F 3 "~" H 6400 2200 50  0001 C CNN
	1    6400 2200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP_Small C4
U 1 1 5E3A7990
P 6200 2200
F 0 "C4" H 6000 2250 50  0000 L CNN
F 1 "10u" H 5950 2150 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A_Pad1.58x1.35mm_HandSolder" H 6200 2200 50  0001 C CNN
F 3 "~" H 6200 2200 50  0001 C CNN
	1    6200 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2100 6200 2050
Wire Wire Line
	6200 2050 6300 2050
Wire Wire Line
	6300 2050 6400 2050
Wire Wire Line
	6400 2050 6400 2100
Connection ~ 6300 2050
Wire Wire Line
	6200 2300 6200 2350
Wire Wire Line
	6200 2350 6300 2350
Wire Wire Line
	6400 2300 6400 2350
Wire Wire Line
	6400 2350 6300 2350
Connection ~ 6300 2350
$Comp
L Connector:Conn_01x01_Male J6
U 1 1 5E418BDC
P 3050 5550
F 0 "J6" H 3158 5731 50  0000 C CNN
F 1 "Conn_01x01_Male" H 3158 5640 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x01_P2.54mm_Vertical" H 3050 5550 50  0001 C CNN
F 3 "~" H 3050 5550 50  0001 C CNN
	1    3050 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+9V #PWR0124
U 1 1 5E419DC4
P 3600 5500
F 0 "#PWR0124" H 3600 5350 50  0001 C CNN
F 1 "+9V" H 3500 5650 50  0000 C CNN
F 2 "" H 3600 5500 50  0001 C CNN
F 3 "" H 3600 5500 50  0001 C CNN
	1    3600 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 5550 3600 5550
Wire Wire Line
	3600 5550 3600 5500
NoConn ~ 4350 2550
NoConn ~ 4350 2650
NoConn ~ 5550 4250
$EndSCHEMATC
