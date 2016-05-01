/*
 * RTOS_interface.h
 *
 *  Created on: Apr 20, 2016
 *      Author: Kareem Galal
 */

#ifndef RTOS_INTERFACE_H_
#define RTOS_INTERFACE_H_


/*******************************************************/
/***************** Public Definitions ******************/
/*******************************************************/


/*******************************************************/
/*****************  Public Functions  ******************/
/*******************************************************/

/*Comment!: Set Task*/
extern void RTOS_voidSetTask(u8 Copy_u8TaskCounter,u8 Copy_u8TaskPeriodicity,void (*Task_Function)(void));

/*Comment!: Initialize RTOS*/
extern void RTOS_voidInit(void);


#endif /* RTOS_INTERFACE_H_ */
