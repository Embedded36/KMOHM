/*
   BIST_Interface.h

    Created on: Feb 22, 2016
        Author: Kareem Galal
*/

#ifndef _BIST_INTERFACE_H_
#define _BIST_INTERFACE_H_

/*******************************************************/
/***************** Public Definitions ******************/
/*******************************************************/



/*******************************************************/
/*****************  Public Functions  ******************/
/*******************************************************/

/*Comment!: Begin the BIST (Buit-In Selt Test)*/
extern u8 BIST_u8Begin(void);

/*Comment!: Initialize the Tactile_Switch*/
extern void BIST_voidInit(void);

#endif	/* _BIST_INTERFACE_H_ */
