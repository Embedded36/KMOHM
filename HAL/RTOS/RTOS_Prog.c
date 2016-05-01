/*
 * RTOS_prog.c
 *
 *  Created on: Apr 20, 2016
 *      Author: Kareem Galal
 */

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\SystemClock.h"
#include "..\..\Utilities\Interrupt.h"
#include "RTOS_Config.h"
#include "RTOS_Private.h"
#include "RTOS_Interface.h"
#include "..\..\MCAL\TIMER_RTOS\TIMER_Interface.h"

#define Timer0_Prescale					(1UL)
#define OverFlowCount_MatchedTickTime	(((clockCyclesPerMillisecond)*(RTOS_u16TickTime))/(Timer0_Prescale)/255UL) //7843.13

struct TCB // Task control Block
{
	void (*ptr)(void); // pointer to function
	u8 Counter; 		// counter at first = first time + 1
	u8 Periodicity; 	//each time we call the function
};

/*Comment!:TCB array*/
static struct TCB RTOS_Task_List[RTOS_u8MAX_TASK_NUM];

/*Comment!: Initialize number of tasks */
static u8 RTOS_u8TaskNum;

/*Comment!: Set Task*/
extern void RTOS_voidSetTask(u8 Copy_u8TaskCounter, u8 Copy_u8TaskPeriodicity,void (*Task_Function)(void)) {
	RTOS_Task_List[RTOS_u8TaskNum].Counter = Copy_u8TaskCounter;
	RTOS_Task_List[RTOS_u8TaskNum].Periodicity = Copy_u8TaskPeriodicity;
	RTOS_Task_List[RTOS_u8TaskNum].ptr = Task_Function;
	RTOS_u8TaskNum++;
}

/*Comment!: RTOS Scheduler*/
static void RTOS_voidScheduler(void) {
	for (u8 Local_u8Counter = 0; Local_u8Counter < RTOS_u8MAX_TASK_NUM;
			Local_u8Counter++) {
		if (RTOS_Task_List[Local_u8Counter].Counter == 1) {
			RTOS_Task_List[Local_u8Counter].ptr();
		}
	}
}

/*Comment!: ISR run every tick time*/
static void RTOS_ISR(void) {
	static u32 Local_u32TickTime = OverFlowCount_MatchedTickTime;
	u8 Local_u8Counter;
	Local_u32TickTime--;
	if (!Local_u32TickTime) {
		Local_u32TickTime = OverFlowCount_MatchedTickTime;
		for (Local_u8Counter = 0; Local_u8Counter < RTOS_u8MAX_TASK_NUM;
				Local_u8Counter++) {
			RTOS_Task_List[Local_u8Counter].Counter--;
			if (RTOS_Task_List[Local_u8Counter].Counter == 0) {
				RTOS_Task_List[Local_u8Counter].Counter =
						RTOS_Task_List[Local_u8Counter].Periodicity;
			}
		}
		RTOS_voidScheduler();
	}
}

/*Comment!: Initialize RTOS*/
extern void RTOS_voidInit(void) {

	RTOS_voidScheduler();

	/*Comment!: set call back function for timer0 interrupt*/
	TIMER_u8AttachInt(TIMER0_OVF, RTOS_ISR);

	/*Comment!: Initialize timer0 */
	TIMER0_voidInit();

	return;
}
