/*
 * CC1101_SPI_INTERFACE.C
 *
 *  Created on: Mar 17, 2012
 *      Author: nikolai_tesla
 */

#include "definitions_global.h"


#include "CC1101_SPI_INTERFACE_DEFINITIONS.H"
#include "CC1101_SPI_INTERFACE_PRIVATE_VARIABLES.H"


//	NOTES FROM CC1101 DATA SHEET
//	All
//	transfers  on the SPI interface  are  done most
//	significant bit first.
//
//	All transactions on the SPI interface start with
//	a header byte    containing a  R/W ¯   bit, a burst
//	access bit (B), and a 6-bit address (A5 – A0).
//
//	When CSn  is pulled  low, the MCU must wait
//	until CC1101 SO pin goes low before starting to
//	transfer the header byte. This indicates that
//	the crystal is running. Unless the chip was in
//	the SLEEP or XOFF states, the SO pin will
//	always go low immediately after taking CSn
//	low.


//MAX SCLK frequency, burst access  6.5 MHz
//
//When the header byte, data byte, or command
//strobe  is sent on the SPI interface, the chip
//status byte is sent by the CC1101 on the SO pin.

//************************************************************************************************






//For register addresses in the range 0x30-
//0x3D, the burst  bit is used to select between
//status registers  when  burst bit  is one,  and
//between   command  strobes when  burst bit  is
//zero.

//Because of this, burst access is not available
//for status registers and they must be accessed
//one at a time. The status registers can only be
//read.

//used hw on stm32f103r8t6: SPI2;
// mosi 	PB15
// miso 	PB14
// sck		PB13
// nss		PB12



void f_stm32_cc1101_spi_clear_buffers_pointers(void);


#ifdef def_enable_rf_sys


void SPI2_IRQHandler(void)
{
	  //RECEIVED!!!
	  if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) != RESET)
	  {
		  if(u8_cc1101_spi_rx_counter<(u8_cc1101_spi_buffer_length))
		  {
			  u8_array_cc1101_spi_rx_buffer[u8_cc1101_spi_rx_counter]=SPI_I2S_ReceiveData(SPI2);
			  u8_cc1101_spi_rx_counter++;
		  }
		  else
		  {
			  SPI_I2S_ReceiveData(SPI2);
		  }
	  }

	//TRANSMITTED!!!
	  else if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_TXE) != RESET)
	  {

		  SPI_I2S_SendData(SPI2, u8_array_cc1101_spi_tx_buffer[u8_cc1101_spi_tx_counter]);
		  u8_cc1101_spi_tx_counter++;

		  if(u8_cc1101_spi_tx_counter >= u8_cc1101_spi_tx_limit)
		  {
			  SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, DISABLE);
			  u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy=0;
		  }

	  }


}


#endif

void f_stm32_cc1101_spi_reset(void)
{
	u8_byte_stm32_cc1101_spi_SYSTEM_STATUS.byte=0;
	f_stm32_cc1101_spi_clear_buffers_pointers();
}


u8 f_stm32_cc1101_spi_start_transmit_buffer(u8 length, u8 *buffer)
{
	u8 i;

	if(u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy==1)
	{
		return def_u8_fail;
	}
	else
	{

		f_stm32_cc1101_spi_clear_buffers_pointers();

		for(i=0;i<length;i++)
		{
			u8_array_cc1101_spi_tx_buffer[i]=(u8) *buffer;
			buffer++;

		}



    	u8_cc1101_spi_tx_limit=length;

    	u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy=1;

    	macro_trigger_cc1101_spi_transection

		return def_u8_success;
	}


}




void f_stm32_cc1101_spi_clear_buffers_pointers(void)
{
	u8 i;

	//flush!!!
	/////////////////////

	for(i=0;i<u8_cc1101_spi_buffer_length;i++)
	{
		  u8_array_cc1101_spi_rx_buffer[i]=0;
		  u8_array_cc1101_spi_tx_buffer[i]=0;
	}

	u8_cc1101_spi_tx_counter=0;
	u8_cc1101_spi_rx_counter=0;
	u8_cc1101_spi_tx_limit=0;
}


void f_stm32_cc1101_spi_hw_init(void)
{
	u8 i;
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, DISABLE);


	  /* Enable SPI_MASTER Periph clock */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

	  SPI_I2S_DeInit(SPI2);


	  /* Configure SPI_MASTER pins: SCK, MISO and MOSI */
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);

	  //nss
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_Init(GPIOB, &GPIO_InitStructure);



	  SET_SPI_CC1101_NSS //SELECT CHIP!!! VITAL??? WHY??? TX INTERRUPT CRASHES IF THIS LINE DOES NOT EXIST!!!


	  /* SPI_MASTER configuration ------------------------------------------------*/
	  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
	  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;// _256;
	  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	  SPI_InitStructure.SPI_CRCPolynomial = 7; //????
	  SPI_Init(SPI2, &SPI_InitStructure);



	  /* SPI_SLAVE configuration -------------------------------------------------*/
//	  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Rx;
//	  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
//	  SPI_Init(SPI_SLAVE, &SPI_InitStructure);

	  /* Enable SPI_MASTER TXE interrupt */
	  //SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, ENABLE); ///!!WILL BE ENABLED WHILE TRANSMITTING


	  /* Enable SPI_SLAVE RXNE interrupt */
	  SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_RXNE, ENABLE);

	  /* Enable SPI_SLAVE */
	  SPI_Cmd(SPI2, ENABLE);

	  /* Enable SPI_MASTER */
	 // SPI_Cmd(SPI_MASTER, ENABLE);

	  SPI_SSOutputCmd(SPI2, ENABLE);    //??? here or above???




}


u8 dummy_wait=0;
u8 dummy_wait_2=0;
void wait_spi(void)
{
	u8 i=0;
	for(i=0;i<16;i++)
	{
		dummy_wait++;
	}

	dummy_wait_2=dummy_wait;

}

u8 f_u8_exchange_byte_cc1101_spi(u8 x)
{
	u8 y=0;
	u8 i;

	RESET_SPI_CC1101_SCK
	RESET_SPI_CC1101_MOSI
	wait_spi();

	for(i=0;i<8;i++)
	{
		RESET_SPI_CC1101_SCK

		//output
		if( (x  & 0x80) == 0x80 )
		{
			SET_SPI_CC1101_MOSI
		}
		else
		{
			RESET_SPI_CC1101_MOSI
		}

		x=x<<1;

		wait_spi();

		SET_SPI_CC1101_SCK

		//input
		if( GET_SPI_CC1101_MISO== 1)
		{
			y++;
		}

		if(i!=7)
		{
			y=y<<1;
		}

		wait_spi();



	}

	RESET_SPI_CC1101_SCK
	RESET_SPI_CC1101_MOSI


	return y;
}

