#ifndef _KEYPAD_INTERFACE_H_ 
#define _KEYPAD_INTERFACE_H_   
  
  
/*******************************************************/  
/***************** Public Definitions ******************/  
/*******************************************************/  

  
/*******************************************************/  
/*****************  Public Functions  ******************/  
/*******************************************************/  
  
  
/*Comment!: Initialization Function*/
extern void KEYPAD_voidInit(void);
/*Comment!: Initialization Function*/
extern u8 KEYPAD_u8Read(u8* Copy_u8PtrVal);
  
#endif  
