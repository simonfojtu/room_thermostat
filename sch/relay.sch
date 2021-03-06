EESchema Schematic File Version 2  date Tue 08 May 2012 10:01:43 PM CEST
LIBS:power,./mine,device,transistors,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,opto,atmel,contrib,valves,./relay.cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title "noname.sch"
Date "8 may 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	5850 3650 5950 3650
Wire Wire Line
	6450 3550 6250 3550
Wire Wire Line
	6250 3550 6250 3600
Wire Wire Line
	6250 3600 5950 3600
Wire Wire Line
	5950 3600 5950 3650
Wire Wire Line
	6050 3750 6050 3800
Wire Wire Line
	6050 3750 6450 3750
Wire Wire Line
	6050 3800 5850 3800
Wire Wire Line
	4300 3750 4600 3750
Wire Wire Line
	4300 3550 4600 3550
Wire Wire Line
	4600 3550 4600 3600
Wire Wire Line
	5850 3500 6050 3500
Wire Wire Line
	6050 3500 6050 3650
Wire Wire Line
	6050 3650 6450 3650
$Comp
L CONN_3 K1
U 1 1 4FA97450
P 6800 3650
F 0 "K1" V 6750 3650 50  0000 C CNN
F 1 "CONN_3" V 6850 3650 40  0000 C CNN
	1    6800 3650
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P1
U 1 1 4FA94FB0
P 3950 3650
F 0 "P1" V 3900 3650 40  0000 C CNN
F 1 "CONN_2" V 4000 3650 40  0000 C CNN
	1    3950 3650
	-1   0    0    1   
$EndComp
$Comp
L RM50 U1
U 1 1 4FA94F9D
P 5200 3650
F 0 "U1" H 5200 3650 60  0000 C CNN
F 1 "RM50" H 5200 3750 60  0000 C CNN
F 2 "RM50" H 5140 3590 60  0001 C CNN
	1    5200 3650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
