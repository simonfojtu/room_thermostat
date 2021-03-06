EESchema Schematic File Version 2  date Wed 11 Jan 2012 08:20:01 AM CET
LIBS:power,device,transistors,conn,linear,regul,74xx,cmos4000,adc-dac,memory,xilinx,special,microcontrollers,dsp,microchip,analog_switches,motorola,texas,intel,audio,interface,digital-audio,philips,display,cypress,siliconi,opto,atmel,contrib,valves,./ui_board.cache
EELAYER 24  0
EELAYER END
$Descr A4 11700 8267
Sheet 1 1
Title "UI board"
Date "6 nov 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4200 2750 4200 3000
Wire Wire Line
	1200 1400 1600 1400
Wire Wire Line
	1200 1600 1600 1600
Wire Wire Line
	1400 2700 1400 2750
Wire Wire Line
	2700 1200 2400 1200
Wire Wire Line
	4200 2050 4200 2350
Wire Wire Line
	1700 3450 2100 3450
Wire Wire Line
	1150 3850 1400 3850
Wire Wire Line
	1150 3850 1150 3250
Wire Wire Line
	1150 3250 2100 3250
Wire Wire Line
	1800 2950 2100 2950
Connection ~ 3550 5900
Wire Wire Line
	3550 5700 3550 6000
Wire Wire Line
	3150 4850 3150 5100
Wire Wire Line
	3950 4850 3950 5100
Wire Wire Line
	1950 7400 1950 7200
Wire Wire Line
	2150 6300 2150 6450
Wire Wire Line
	2150 6450 1750 6450
Wire Wire Line
	1750 6450 1750 6300
Wire Wire Line
	1300 4900 1300 5200
Wire Wire Line
	2150 5200 2150 4900
Wire Wire Line
	2150 5600 2150 5800
Wire Wire Line
	1300 5600 1300 5800
Wire Wire Line
	2400 1500 2700 1500
Wire Wire Line
	2400 1300 2700 1300
Wire Wire Line
	2400 1100 2700 1100
Wire Wire Line
	1600 1200 1200 1200
Wire Wire Line
	1600 1300 1200 1300
Wire Wire Line
	1200 1100 1600 1100
Wire Wire Line
	2700 1400 2400 1400
Wire Wire Line
	2700 1600 2400 1600
Wire Wire Line
	1750 5600 1750 5800
Wire Wire Line
	1750 5200 1750 4900
Wire Wire Line
	1750 4900 2150 4900
Wire Wire Line
	1300 6500 1300 6300
Wire Wire Line
	1950 6450 1950 6600
Connection ~ 1950 6450
Wire Wire Line
	3550 5100 3550 4850
Wire Wire Line
	3950 5700 3950 5900
Wire Wire Line
	3950 5900 3150 5900
Wire Wire Line
	3150 5900 3150 5700
Wire Wire Line
	1800 2850 2100 2850
Wire Wire Line
	1400 2750 2100 2750
Wire Wire Line
	1700 3050 2100 3050
Wire Wire Line
	1400 3350 2100 3350
Wire Wire Line
	1800 3150 2100 3150
Wire Wire Line
	1400 3850 1400 3750
Wire Wire Line
	1200 1500 1600 1500
Text Label 1400 2700 0    60   ~ 0
3.3V
Text Label 3550 6000 0    60   ~ 0
GND
Text Label 1950 7400 0    60   ~ 0
GND
Text Label 1300 6500 0    60   ~ 0
GND
Text Label 1900 4900 0    60   ~ 0
5V
Text Label 1200 1600 0    60   ~ 0
GND
Text Label 1200 1500 0    60   ~ 0
GND
Text Label 1200 1400 0    60   ~ 0
5V
Text Label 4200 2050 0    60   ~ 0
5V
Text Label 4200 3000 0    60   ~ 0
3.3V
Text Label 1150 3850 0    60   ~ 0
GND
Text Label 1800 3150 0    60   ~ 0
SS
Text Label 1700 3450 0    60   ~ 0
LCD_RST
Text Label 1700 3050 0    60   ~ 0
LCD_DC
Text Label 1800 2950 0    60   ~ 0
MISO
Text Label 1800 2850 0    60   ~ 0
SCK
$Comp
L CONN_8 P2
U 1 1 4EB6C3DB
P 2450 3100
F 0 "P2" V 2400 3100 60  0000 C CNN
F 1 "CONN_8" V 2500 3100 60  0000 C CNN
	1    2450 3100
	1    0    0    -1  
$EndComp
$Comp
L CP1 C1
U 1 1 4EB6C37F
P 1400 3550
F 0 "C1" H 1450 3650 50  0000 L CNN
F 1 "10uF" H 1450 3450 50  0000 L CNN
	1    1400 3550
	1    0    0    -1  
$EndComp
Text Label 3950 4850 0    60   ~ 0
B2
Text Label 3550 4850 0    60   ~ 0
B1
Text Label 3150 4850 0    60   ~ 0
B0
$Comp
L SW_PUSH SW4
U 1 1 4EB6C33D
P 3950 5400
F 0 "SW4" H 4100 5510 50  0000 C CNN
F 1 "PUSH_2" H 3950 5320 50  0000 C CNN
	1    3950 5400
	0    1    1    0   
$EndComp
$Comp
L SW_PUSH SW3
U 1 1 4EB6C33B
P 3550 5400
F 0 "SW3" H 3700 5510 50  0000 C CNN
F 1 "PUSH_1" H 3550 5320 50  0000 C CNN
	1    3550 5400
	0    1    1    0   
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 4EB6C336
P 3150 5400
F 0 "SW2" H 3300 5510 50  0000 C CNN
F 1 "PUSH_0" H 3150 5320 50  0000 C CNN
	1    3150 5400
	0    1    1    0   
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 4EB6C2E8
P 1950 6900
F 0 "SW1" H 2100 7010 50  0000 C CNN
F 1 "PUSH_BL" H 1950 6820 50  0000 C CNN
	1    1950 6900
	0    1    1    0   
$EndComp
Text Label 1300 4900 0    60   ~ 0
CTRL
$Comp
L R R4
U 1 1 4EB6BBEA
P 2150 6050
F 0 "R4" V 2230 6050 50  0000 C CNN
F 1 "R" V 2150 6050 50  0000 C CNN
	1    2150 6050
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4EB6BBE6
P 1750 6050
F 0 "R3" V 1830 6050 50  0000 C CNN
F 1 "R" V 1750 6050 50  0000 C CNN
	1    1750 6050
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4EB6BBE2
P 1300 6050
F 0 "R2" V 1380 6050 50  0000 C CNN
F 1 "R" V 1300 6050 50  0000 C CNN
	1    1300 6050
	1    0    0    -1  
$EndComp
$Comp
L LED D4
U 1 1 4EB6BBB6
P 2150 5400
F 0 "D4" H 2150 5500 50  0000 C CNN
F 1 "BACKLIGHT2" H 2150 5300 50  0000 C CNN
	1    2150 5400
	0    1    1    0   
$EndComp
$Comp
L LED D3
U 1 1 4EB6BB7F
P 1750 5400
F 0 "D3" H 1750 5500 50  0000 C CNN
F 1 "BACKLIGHT1" H 1750 5300 50  0000 C CNN
	1    1750 5400
	0    1    1    0   
$EndComp
$Comp
L LED D2
U 1 1 4EB6BB7C
P 1300 5400
F 0 "D2" H 1300 5500 50  0000 C CNN
F 1 "ON" H 1300 5300 50  0000 C CNN
	1    1300 5400
	0    1    1    0   
$EndComp
$Comp
L LED D1
U 1 1 4EB6BB6F
P 4200 2550
F 0 "D1" H 4200 2650 50  0000 C CNN
F 1 "POWER" H 4200 2450 50  0000 C CNN
	1    4200 2550
	0    1    1    0   
$EndComp
Text Label 2700 1600 0    60   ~ 0
SCK
Text Label 2700 1500 0    60   ~ 0
MISO
Text Label 2700 1400 0    60   ~ 0
LCD_DC
Text Label 2700 1300 0    60   ~ 0
SS
Text Label 1200 1300 0    60   ~ 0
CTRL
Text Label 2700 1200 0    60   ~ 0
B2
Text Label 1200 1200 0    60   ~ 0
LCD_RST
Text Label 2700 1100 0    60   ~ 0
B1
Text Label 1200 1100 0    60   ~ 0
B0
$Comp
L CONN_6X2 P1
U 1 1 4EB6BA39
P 2000 1350
F 0 "P1" H 2000 1700 60  0000 C CNN
F 1 "CONN_6X2" V 2000 1350 60  0000 C CNN
	1    2000 1350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
