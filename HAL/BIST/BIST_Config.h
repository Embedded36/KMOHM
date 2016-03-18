/*
   BIST_Config.h

    Created on: Feb 22, 2016
        Author: Kareem Galal
*/


#ifndef _BIST_CONFIG_H_
#define _BIST_CONFIG_H_

/*******************************************************/
/**************** Public Definitions *******************/
/*******************************************************/

/*Comment!: Built In Self Test */
/*Range!  : 0x00 : 0xFF */
#define	BIST_u8PATTERN1		0x55 //0b00 01 0101
#define	BIST_u8PATTERN2		0xAA //0b00 10 1010
#define	BIST_u8PATTERN3		0xF0 //0b00 11 0000
#define	BIST_u8PATTERN4		0x0F //0b00 00 1111

/*Comment!: Control Pins*/
/*Comment!: 00 >> Pattern1, 01 >> Pattern2, 10 >> Pattern3 ,11 >> Pattern4*/
/*Range!  : DIO_u8PIN0 : DIO_u8PIN31*/
#define	BIST_u8INPUT_PIN1	DIO_u8PIN0
#define	BIST_u8INPUT_PIN2	DIO_u8PIN1


#endif	/* _BIST_CONFIG_H_ */
