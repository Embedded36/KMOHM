/*
 * EXTINT_Prog.c
 *
 *  Created on: Feb 2, 2016
 *      Author: KiMo
 */

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\Util.h"
#include "EXTINT_Private.h"
#include "EXTINT_Config.h"
#include "EXTINT_Interface.h"

/*******************************************************/
/***************** Global Variables ********************/
/*******************************************************/

typedef void (*voidFuncPtr)(void);
volatile static voidFuncPtr EXTINT_IntFunc[EXTINT_NUM_INTERRUPTS];

/*******************************************************/
/***************** Public Functions ********************/
/*******************************************************/

/*Comment!: Initialization Function for EXTINTs*/
extern void EXTINT_voidInit(void) {
	//__asm__("SEI");
//External Interrupt 0
#if (EXTINT0_INITSTATE == EXTINT_ENABLE)
	SET_BIT(EXTINT_u8GICR, INT0);
#if(EXTINT0_SENSE_CON_MODE == EXTINT_LEVEL_LOW || EXTINT0_SENSE_CON_MODE == EXTINT_EDGE_ANY || EXTINT0_SENSE_CON_MODE == EXTINT_EDGE_FALLING || EXTINT0_SENSE_CON_MODE == EXTINT_EDGE_RISING)
	EXTINT_u8MCUCR = ((EXTINT_u8MCUCR & 0xFC) | EXTINT0_SENSE_CON_MODE);
#else
#warning "You put a wrong SENSE_CON_MODE for ExtInt0 so the default state is LEVEL_LOW"
#endif
#elif (EXTINT0_INITSTATE == EXTINT_DISABLE)

#else
#warning "You put a wrong state for ExtInt0 so the default state is OFF"
#endif

//External Interrupt 1
#if (EXTINT1_INITSTATE == EXTINT_ENABLE)
	SET_BIT(EXTINT_u8GICR,INT1);
#if(EXTINT1_SENSE_CON_MODE == EXTINT_LEVEL_LOW || EXTINT1_SENSE_CON_MODE == EXTINT_EDGE_ANY || EXTINT1_SENSE_CON_MODE == EXTINT_EDGE_FALLING || EXTINT1_SENSE_CON_MODE == EXTINT_EDGE_RISING)
	EXTINT_u8MCUCR = ((EXTINT_u8MCUCR & 0xF3) | (EXTINT1_SENSE_CON_MODE<<ISC10));
#else
#warning "You put a wrong SENSE_CON_MODE for ExtInt1 so the default state is LEVEL_LOW"
#endif
#elif (EXTINT1_INITSTATE == EXTINT_DISABLE)
#else
#warning "You put a wrong state for ExtInt1 so the default state is OFF"
#endif

//External Interrupt 2
#if (EXTINT2_INITSTATE == EXTINT_ENABLE)
	SET_BIT(EXTINT_u8GICR,INT2);
#if(EXTINT2_SENSE_CON_MODE == EXTINT_EDGE_RISING)
	SET_BIT(EXTINT_u8MCUCSR,ISC2);
#elif(EXTINT2_SENSE_CON_MODE == EXTINT_EDGE_FALLING)
	//CLR_BIT(EXTINT_u8MCUCSR,ISC2);
#else
#warning "You put a wrong SENSE_CON_MODE for ExtInt2 so the default state is EDGE_FALLING"
#endif
#elif (EXTINT2_INITSTATE == EXTINT_DISABLE)
#else
#warning "You put wrong state for ExtInt2 so the default state is OFF"
#endif
	return;
}
/*Comment!: EXTINT0 Enable */
extern u8 EXTINT_voidEnable(u8 Copy_ExtInterrupt) {
	u8 Local_u8Status = u8OK;
	switch (Copy_ExtInterrupt) {
	case EXTINT0:
		SET_BIT(EXTINT_u8GICR, INT0);
		break;
	case EXTINT1:
		SET_BIT(EXTINT_u8GICR, INT1);
		break;
	case EXTINT2:
		SET_BIT(EXTINT_u8GICR, INT2);
		break;
	default: // make sure the interrupt number is within bounds
		Local_u8Status = u8ERROR;
		break;
	}
	return Local_u8Status;
}
/*Comment!: SPI Disable */
extern u8 EXTINT_voidDisable(u8 Copy_ExtInterrupt) {
	u8 Local_u8Status = u8OK;
	switch (Copy_ExtInterrupt) {
	case EXTINT0:
		CLR_BIT(EXTINT_u8GICR, INT0);
		break;
	case EXTINT1:
		CLR_BIT(EXTINT_u8GICR, INT1);
		break;
	case EXTINT2:
		CLR_BIT(EXTINT_u8GICR, INT2);
		break;
	default: // make sure the interrupt number is within bounds
		Local_u8Status = u8ERROR;
		break;
	}
	return Local_u8Status;
}

// EXTINT_u8AttachInt and EXTINT_u8DetachInt commands
//              These functions allow the attachment (or detachment) of any user
//              function to an external interrupt.  "Attaching" one of your own
//              functions to an interrupt means that it will be called whenever
//              that interrupt is triggered.  Example usage:
//
//              EXTINT_u8AttachInt(EXTINT0, myInterruptHandler);
//              EXTINT_u8DetachInt(EXTINT0);
//
//              extintAttach causes the myInterruptHandler() to be attached, and therefore
//              execute, whenever the corresponding interrupt occurs.  extintDetach removes
//              the association and executes no user function when the interrupt occurs.
//              myInterruptFunction must be defined with no return value and no arguments:
//
//              void myInterruptHandler(void) { ... }
/*Comment!: "Attaching" one of your own functions to an interrupt means that it will be called whenever that interrupt is triggered*/
u8 EXTINT_u8AttachInt(u8 Copy_ExtInterrupt, void (*UserFunc)(void)) {
	u8 Local_u8Status = u8OK;
	// make sure the interrupt number is within bounds
	if (Copy_ExtInterrupt < EXTINT_NUM_INTERRUPTS) {
		// set the interrupt function to run
		// the supplied user's function
		EXTINT_IntFunc[Copy_ExtInterrupt] = UserFunc;
	} else {
		Local_u8Status = u8ERROR;
	}
	return Local_u8Status;
}
/*Comment!: Remove the association and executes no user function when the interrupt occurs*/
u8 EXTINT_u8DetachInt(u8 Copy_ExtInterrupt) {
	u8 Local_u8Status = u8OK;
	// make sure the interrupt number is within bounds
	if (Copy_ExtInterrupt < EXTINT_NUM_INTERRUPTS) {
		// set the interrupt function to run
		// the supplied user's function
		EXTINT_IntFunc[Copy_ExtInterrupt] = 0;
	} else {
		Local_u8Status = u8ERROR;
	}
	return Local_u8Status;
}
/*Comment!: ISR for EXTINT0_vect*/
ISR(INT0_vect) {
	// if a user function is defined, execute it
	if (EXTINT_IntFunc[EXTINT0]) {
		EXTINT_IntFunc[EXTINT0]();
	}
}
/*Comment!: ISR for EXTINT1_vect*/
ISR(INT1_vect) {
	// if a user function is defined, execute it
	if (EXTINT_IntFunc[EXTINT1]) {
		EXTINT_IntFunc[EXTINT1]();
	}
}
/*Comment!: ISR for EXTINT2_vect*/
ISR(INT2_vect) {
	// if a user function is defined, execute it
	if (EXTINT_IntFunc[EXTINT2]) {
		EXTINT_IntFunc[EXTINT2]();
	}
}
