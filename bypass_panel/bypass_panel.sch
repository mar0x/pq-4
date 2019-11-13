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
L Switch:SW_MEC_5G_LED SW1
U 1 1 5DC33EA7
P 5950 3600
F 0 "SW1" H 5950 3985 50  0000 C CNN
F 1 "SW_MEC_5G_LED" H 5950 3894 50  0000 C CNN
F 2 "LED_Button_Switch_THT:SW_PUSH_6mm" H 5950 3900 50  0001 C CNN
F 3 "http://www.apem.com/int/index.php?controller=attachment&id_attachment=488" H 5950 3900 50  0001 C CNN
	1    5950 3600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J1
U 1 1 5DC44193
P 4750 3500
F 0 "J1" H 4856 3778 50  0000 C CNN
F 1 "Conn_01x04_Male" H 4856 3687 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 4750 3500 50  0001 C CNN
F 3 "~" H 4750 3500 50  0001 C CNN
	1    4750 3500
	1    0    0    -1  
$EndComp
Text GLabel 4950 3400 2    50   Input ~ 0
B1
Text GLabel 4950 3500 2    50   Input ~ 0
B2
Text GLabel 4950 3600 2    50   Input ~ 0
L+
Text GLabel 4950 3700 2    50   Input ~ 0
L-
$Comp
L Connector:Conn_01x04_Male J2
U 1 1 5DC442A4
P 4750 4250
F 0 "J2" H 4856 4528 50  0000 C CNN
F 1 "Conn_01x04_Male" H 4856 4437 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 4750 4250 50  0001 C CNN
F 3 "~" H 4750 4250 50  0001 C CNN
	1    4750 4250
	1    0    0    -1  
$EndComp
Text GLabel 4950 4150 2    50   Input ~ 0
B1
Text GLabel 4950 4250 2    50   Input ~ 0
B2
Text GLabel 4950 4350 2    50   Input ~ 0
L+
Text GLabel 4950 4450 2    50   Input ~ 0
L-
Text GLabel 5750 3500 0    50   Input ~ 0
B1
Text GLabel 6150 3500 2    50   Input ~ 0
B2
Text GLabel 5750 3600 0    50   Input ~ 0
L-
Text GLabel 6150 3600 2    50   Input ~ 0
L+
$EndSCHEMATC
