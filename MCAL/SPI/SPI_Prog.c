/*
 * SPI_prog.c
 *
 *  Created on: Jan 27, 2016
 *      Author: Kareem Galal
 */

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\Util.h"
#include "SPI_Config.h"
#include "SPI_Private.h"
#include "SPI_Interface.h"

/*Comment!: ISR for Serial Transfer Complete*/
ISR(SPI_STC) {

}

/*Comment!: SPI Initialization */
extern void SPI_voidInit(void) {
#if (SPI_INITSTATE==SPI_ENABLE)
	SPI_u8SPCR = SPI_u8SPCR_VALUE;
#if(SPI_SPI2X)
	SET_BIT(SPI_u8SPSR,SPI2X);
#endif
#if (SPI_MASTER_SLAVE_MODE==SPI_SLAVE)
	/* Set MISO output, all others input */
	SET_BIT(SPI_u8DDR,DD_MISO);
	CLR_BIT(SPI_u8DDR,SPI_MOSI);
	CLR_BIT(SPI_u8DDR,SPI_SCK);
#elif (SPI_MASTER_SLAVE_MODE==SPI_MASTER)
	/* Set MOSI and SCK output, all others input for master*/
	SET_BIT(SPI_u8DDR, SPI_MOSI);
	SET_BIT(SPI_u8DDR, SPI_SCK);
	CLR_BIT(SPI_u8DDR, SPI_MISO);
#else
#warning "The default for the SPI mode is MASTER"
	/* Set MOSI and SCK output, all others input for master*/
	SET_BIT(SPI_u8DDR,SPI_MOSI);
	SET_BIT(SPI_u8DDR,SPI_SCK);
	CLR_BIT(SPI_u8DDR,SPI_MISO);
#endif
#endif
	return;
}

/*Comment!: SPI Enable */
extern void SPI_voidEnable(void) {
	/* Enable SPI */
	SET_BIT(SPI_u8SPCR, SPE);
	return;
}

/*Comment!: SPI Disable */
extern void SPI_voidDisable(void) {
	/* Enable SPI */
	CLR_BIT(SPI_u8SPCR, SPE);
	return;
}

/*Comment!: Transmit & Receive One Byte to/From the SPI*/
extern u8 SPI_u8Transfer(u8 Copy_u8TxData, u8 *Copy_u8RxData) {
	u8 Local_u8Status = u8OK;
	/* Start transmission */
	SPI_u8SPDR = Copy_u8TxData;
	/* Wait for transmission complete */
	while (!(GET_BIT(SPI_u8SPSR, SPIF)));
	*Copy_u8RxData = SPI_u8SPDR;
	return Local_u8Status;
}

/*Comment!:  Transmit & Receive a String to/From the SPI*/
extern u8 SPI_u8TransferString(u8 *Copy_u8TxString, u8 *Copy_u8RxString) {
	u8 Local_u8Status = u8OK;
	while (*(Copy_u8TxString)) {
		SPI_u8Transfer(*Copy_u8TxString++,Copy_u8RxString++);
	}
	return Local_u8Status;
}
