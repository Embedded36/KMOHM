#ifndef _PotentioMeter_INTERFACE_H_ 
#define _PotentioMeter_INTERFACE_H_   

/*******************************************************/
/***************** Public Definitions ******************/
/*******************************************************/

/*Comment!: PotentioMeter Numbers*/
#define	POTENTIOMETER_u8NUM1	0
#define POTENTIOMETER_u8NUM2	1
#define POTENTIOMETER_u8NUM3	2
#define POTENTIOMETER_u8NUM4	3
#define POTENTIOMETER_u8NUM5	4
#define POTENTIOMETER_u8NUM6	5
#define POTENTIOMETER_u8NUM7	6
#define POTENTIOMETER_u8NUM8	7  

/*******************************************************/
/*****************  Public Functions  ******************/
/*******************************************************/

/*Comment!: Function to get the voltage value of the PotentioMeter, it reads a specific ADC channel then map its vaule*/
extern u8 PotentioMeter_u8GetVoltageVal(u8 Copy_u8PotentioIdx, f32* Copy_f32PotentioVal);

/*Comment!: */
//extern void PotentioMeter_voidInit(void); 
#endif  
