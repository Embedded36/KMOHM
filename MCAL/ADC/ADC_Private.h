/*
   ADC_private.h

    Created on: Jan 27, 2016
        Author: Kareem Galal
*/

#ifndef _ADC_PRIVATE_H_
#define _ADC_PRIVATE_H_

/*******************************************************/
/***************** Private Definitions  ****************/
/*******************************************************/

/*Comment!: ATMEGA32 ADC Registers */
#define ADC_u8ADMUX		(*(volatile u8*)(0x27))
#define ADC_u8ADCSRA	(*(volatile u8*)(0x26))
#define ADC_u8ADCH		(*(volatile u8*)(0x25))
#define ADC_u8ADCL		(*(volatile u8*)(0x24))
#define ADC_u16ADC		(*(volatile u16*)(0x24))
/*Comment!: ADC Filtered Configuration options*/
#define ADC_u8NUM0			0	
#define ADC_u8NUM1			1	
#define ADC_u8NUM2			2	
#define ADC_u8NUM3			3	
#define ADC_u8NUM4			4	
#define ADC_u8NUM5			5	
#define ADC_u8NUM6			6	
#define ADC_u8NUM7			7	
#define ADC_u8NUM8			8	
#define ADC_u8NUM9			9	
#define ADC_u8NUM10			10

/*Comment!: ADC Enable Bit Number */
#define ADEN		7
/*Comment!: ADC Start Conversion */
#define ADSC		6

/*Comment!: Adjust Result For ADC */
#define ADC_u8ADJ_LEFT			1
#define ADC_u8ADJ_RIGHT			0

/*Comment!:  Voltage Reference Selection For ADC */
/*Range!  : ADC_u8AREF or ADC_u8AVCC or ADC_u8INTERNAL */
#define ADC_u8AREF			00
#define ADC_u8AVCC			01
#define ADC_u8INTERNAL		11

/*Range!  : ADC_u8DIVISION_FACTOR2, ADC_u8DIVISION_FACTOR4, ADC_u8DIVISION_FACTOR8, ADC_u8DIVISION_FACTOR16, ADC_u8DIVISION_FACTOR32, ADC_u8DIVISION_FACTOR64, ADC_u8DIVISION_FACTOR128*/
#define ADC_u8DIVISION_FACTOR2			000 //or 001
#define ADC_u8DIVISION_FACTOR4			010
#define ADC_u8DIVISION_FACTOR8			011
#define ADC_u8DIVISION_FACTOR16			100
#define ADC_u8DIVISION_FACTOR32			101
#define ADC_u8DIVISION_FACTOR64			110
#define ADC_u8DIVISION_FACTOR128		111

/*******************************************************/
/***************** Private Functions *******************/
/*******************************************************/

/*Comment!: Concatenate Function for ADMUX*/
#define CONC_ADMUX_HELPER(BIT76,BIT5,BIT43210) 0b##BIT76##BIT5##BIT43210
#define CONC_ADMUX(BIT76,BIT5,BIT43210)    CONC_ADMUX_HELPER(BIT76,BIT5,BIT43210)

/*Comment!: Concatenate Function for ADCSRA*/
#define CONC_ADCSRA_HELPER(BIT7, BIT6, BIT5, BIT4, BIT3, BIT210) 0b##BIT7##BIT6##BIT5##BIT4##BIT3##BIT210
#define CONC_ADCSRA(BIT7, BIT6, BIT5, BIT4, BIT3, BIT210)    CONC_ADCSRA_HELPER(BIT7, BIT6, BIT5, BIT4, BIT3, BIT210)

/*Comment!: ADMUX Initial Value */
#define ADC_u8ADMUX_VALUE CONC_ADMUX(ADC_u8REFVOLT, ADC_u8ADJ_RESULT, 00000)
/*Comment!: ADMUX Initial Value */
#define ADC_u8ADCSRA_VALUE CONC_ADCSRA(0,0,0,0,0,ADC_u8PRESCALER)


#endif /* _ADC_PRIVATE_H_ */
