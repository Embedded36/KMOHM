/*
 * ADC_prog.c
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\Util.h"
#include "ADC_Private.h"
#include "ADC_Config.h"
#include "ADC_Interface.h"

/*Comment!: ADC Initialization */
extern void ADC_voidInit(void) {
	ADC_u8ADMUX = ADC_u8ADMUX_VALUE;
	ADC_u8ADCSRA = ADC_u8ADCSRA_VALUE;
	return;
}

/*Comment!: ADC Enable */
extern void ADC_voidEnable(void) {
	SET_BIT(ADC_u8ADCSRA,ADEN);
	return;
}

/*Comment!: ADC Disable */
extern void ADC_voidDisable(void) {
	CLR_BIT(ADC_u8ADCSRA,ADEN);
	return;
}

/*Comment!: Read ADC on a specific channel, just one shot */
extern u8 ADC_u8ReadChannel(u8 Copy_u8ChannelNum, u16* Copy_u16ADCValue) {
	u8 Local_u8Status = u8OK;
	if (!GET_BIT(ADC_u8ADCSRA,ADEN) || (Copy_u8ChannelNum > ADC_u8CH7)) { // ADC is Disable
		Local_u8Status = u8ERROR;
	} else {
	ADC_u8ADMUX = ((ADC_u8ADMUX & 0xE0) | Copy_u8ChannelNum); // clears the bottom 3 bits before ORing
	SET_BIT(ADC_u8ADCSRA,ADSC);	// Start the ADC conversion
    while(GET_BIT(ADC_u8ADCSRA,ADSC));      // waits for the ADC to finish 
//    *Copy_u16ADCValue = ADC_u8ADCL;
//    *Copy_u16ADCValue = (ADC_u8ADCH << 8) + *Copy_u16ADCValue;    // ADCH is read so ADC can be updated again
    *Copy_u16ADCValue = ADC_u8ADC;
	}
	return Local_u8Status;
}

/*Comment!: Read ADC on a specific channel, Filtered Reading */
extern u8 ADC_u8ReadChannelFiltered (u8 Copy_u8ChannelNum, u16* Copy_u16ADCValue) {
	u8 Local_u8Status = u8OK;
	if (!GET_BIT(ADC_u8ADCSRA,ADEN) || (Copy_u8ChannelNum > ADC_u8CH7)) { // ADC is Disable
		Local_u8Status = u8ERROR;
	} else {
	u8 Local_u8LoopIndex;
	u16 Local_u16TempADCValue;
	*Copy_u16ADCValue=ADC_u8Num0;
	ADC_u8ADMUX = ((ADC_u8ADMUX & 0xE0) | Copy_u8ChannelNum); // clears the bottom 3 bits before ORing
	for(Local_u8LoopIndex=ADC_u8Num0;Local_u8LoopIndex<ADC_u8FilteredItertion;Local_u8LoopIndex++){
	SET_BIT(ADC_u8ADCSRA,ADSC);	// Start the ADC conversion
    while(GET_BIT(ADC_u8ADCSRA,ADSC));      // waits for the ADC to finish 
    Local_u16TempADCValue = ADC_u8ADCL;
    Local_u16TempADCValue = (ADC_u8ADCH << 8) + Local_u16TempADCValue;    // ADCH is read so ADC can be updated again
	*Copy_u16ADCValue += Local_u16TempADCValue;
	}
		*Copy_u16ADCValue /=ADC_u8FilteredItertion;
	}
	return Local_u8Status;
}
