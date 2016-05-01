/*
 * ADC_config.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_

/*******************************************************/
/***************** Public Definitions  *****************/
/*******************************************************/
/* 
		7 bit 	6 bit 	5 bit 	4 bit 	3 bit 	2 bit 	1 bit 	0 bit 
ADMUX	REFS1	REFS0	ADLAR	MUX4	MUX3	MUX2	MUX1	MUX0

if ADLAR is set, the result is left adjusted so read ADCH & ADCL for the other lower 2 bit 

REFS1 REFS0 Voltage Reference Selection
0	 	0	AREF, Internal Vref turned off
0 		1 	AVCC with external capacitor at AREF pin
1 		0 	Reserved
1 		1 	Internal 2.56V Voltage Reference with external capacitor at AREF pin

MUX4..0	Single Ended Input
 00000		ADC0 
 00001		ADC1 
 00010		ADC2 
 00011		ADC3 
 00100		ADC4 
 00101		ADC5 
 00110		ADC6 
 00111		ADC7 
 11110		1.22V 1.22V (VBG)
 11111		0V (GND) 
 */
 

/*Comment!:  Voltage Reference Selection For ADC */
/*Range!  : ADC_u8AREF or ADC_u8AVCC or ADC_u8INTERNAL */
#define ADC_u8REFVOLT			ADC_u8AVCC

/*Comment!: Adjust Result For ADC */
/*Range!  : ADC_u8ADJ_LEFT or ADC_u8ADJ_RIGHT */
#define ADC_u8ADJ_RESULT			ADC_u8ADJ_RIGHT

/* 
		7 bit	6 bit 	5 bit 	4 bit 	3 bit 	2 bit 	1 bit 	0 bit 
ADCSRA	ADEN	ADSC	ADATE	ADIF	ADIE	ADPS2	ADPS1	ADPS0
Bit 7 – ADEN: ADC Enable , 1 Enable, 0 Disable
Bit 6 – ADSC: ADC Start Conversion, In Single Conversion mode, write this bit to one to start each conversion
Bit 5 – ADATE: ADC Auto Trigger Enable
Bit 4 – ADIF: ADC Interrupt Flag
Bit 3 – ADIE: ADC Interrupt Enable
Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
ADPS2 ADPS1 ADPS0 Division Factor
0 		0		0		2
0		0		1		2
0		1		0		4
0		1		1		8
1		0		0		16
1		0		1		32
1		1		0		64
1		1		1		128
By default, the successive approximation circuitry requires an input clock frequency between
50kHz and 200kHz to get maximum resolution. If a lower resolution than 10 bits is needed, the
input clock frequency to the ADC can be higher than 200kHz to get a higher sample rate.
 */
/*Comment!: ADC Prescaler Select */
/*Range!  : ADC_u8DIVISION_FACTOR2, ADC_u8DIVISION_FACTOR4, ADC_u8DIVISION_FACTOR8, ADC_u8DIVISION_FACTOR16, ADC_u8DIVISION_FACTOR32, ADC_u8DIVISION_FACTOR64, ADC_u8DIVISION_FACTOR128*/
#define ADC_u8PRESCALER			ADC_u8DIVISION_FACTOR32

/*Comment!: ADC Filtered Configration, take number of ADC reading from the same channel them return the average*/
/*Range!  : ADC_u8Num1 : ADC_u8Num10*/
#define ADC_u8FILTEREDITERTION			ADC_u8NUM5

#endif /* _ADC_CONFIG_H_ */
