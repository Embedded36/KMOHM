#include "..\..\Utilities\Types.h"
#include "..\..\MCAL\ADC\ADC_Interface.h"
#include "PotentioMeter_Config.h"
#include "PotentioMeter_Interface.h"
#include "PotentioMeter_Private.h"

static const u8 PotentioMeter_u8ChNumArr[POTENTIOMETER_u8TOTALNUM] = {POTENTIOMETER_u8NUM1CH, POTENTIOMETER_u8NUM2CH, POTENTIOMETER_u8NUM3CH, POTENTIOMETER_u8NUM4CH, POTENTIOMETER_u8NUM5CH, POTENTIOMETER_u8NUM6CH, POTENTIOMETER_u8NUM7CH, POTENTIOMETER_u8NUM8CH};

//ADC_u8ReadChannelFiltered (u8 Copy_u8ChannelNum, u16* Copy_u16ADCFilteredValue);

/*Comment!: Function to get the voltage value of the PotentioMeter, it reads a specific ADC channel then map its vaule*/  
extern u8 PotentioMeter_u8GetVoltageVal(u8 Copy_u8PotentioIdx, f32* Copy_f32PotentioVal){
	u8 Local_u8RetrunStatus = u8OK;
	if(Copy_u8PotentioIdx>POTENTIOMETER_u8NUM8){
		Local_u8RetrunStatus = u8ERROR;
	}
	else{
		u16 Local_u16ADCValue;
		ADC_u8ReadChannel(PotentioMeter_u8ChNumArr[Copy_u8PotentioIdx], &Local_u16ADCValue);
		*Copy_f32PotentioVal = 0;
		*Copy_f32PotentioVal = (Local_u16ADCValue * ADC_u8VREF) / ADC_u16RESULOTION;
	}
	return Local_u8RetrunStatus;
}

