/*
 * ADC_interface.h
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#ifndef _ADC_INTERFACE_H_
#define _ADC_INTERFACE_H_

/*******************************************************/
/***************** Public Definitions  *****************/
/*******************************************************/

/*Comment!: Input ADC Channel*/
#define ADC_U8CH0		0
#define ADC_U8CH1		1
#define ADC_U8CH2		2
#define ADC_U8CH3		3
#define ADC_U8CH4		4
#define ADC_U8CH5		5
#define ADC_U8CH6		6
#define ADC_U8CH7		7
//#define ADC_u8VBG		30 //or 1E

/*Comment!: Digital I/O Direction*/
#define ADC_u8INPUT		0
#define ADC_u8OUTPUT	1

/*******************************************************/
/***************** Public Functions ********************/
/*******************************************************/

/*Comment!: ADC Initialization */
extern void ADC_voidInit(void);
/*Comment!: ADC Enable */
extern void ADC_voidEnable(void);
/*Comment!: ADC Disable */
extern void ADC_voidDisable(void);
/*Comment!: Read ADC on a specific channel, just one shot */
extern u8 ADC_u8ReadChannel(u8 Copy_u8ChannelNum, u16* Copy_u16ADCValue);
/*Comment!: Read ADC on a specific channel, Filtered Reading */
extern u8 ADC_u8ReadChannelFiltered (u8 Copy_u8ChannelNum, u16* Copy_u16ADCValue);
/*Comment!: Read ADC on a specific channel, just one shot */
//extern u8 ADC_u8ReadGroup(u8 Copy_u8GroupNum, u16* Copy_u16ADCValue);

#endif /* _ADC_INTERFACE_H_ */
