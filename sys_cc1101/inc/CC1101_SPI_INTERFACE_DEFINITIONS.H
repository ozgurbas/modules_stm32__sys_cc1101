/*
 * CC1101_SPI_INTERFACE.H
 *
 *  Created on: Mar 17, 2012
 *      Author: nikolai_tesla
 */

#ifndef CC1101_SPI_INTERFACE_H_
#define CC1101_SPI_INTERFACE_H_


			//used hw on stm32f103r8t6: SPI2;
			// mosi 	PB15
			// miso 	PB14
			// sck		PB13
			// nss		PB12
#define 		SET_SPI_CC1101_NSS		GPIO_SetBits(GPIOB, GPIO_Pin_12);
#define 		RESET_SPI_CC1101_NSS	GPIO_ResetBits(GPIOB, GPIO_Pin_12);

#define 		SET_SPI_CC1101_SCK		GPIO_SetBits(GPIOB, GPIO_Pin_13);
#define 		RESET_SPI_CC1101_SCK	GPIO_ResetBits(GPIOB, GPIO_Pin_13);


#define   		GET_SPI_CC1101_MISO     GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)

#define 		SET_SPI_CC1101_MOSI		GPIO_SetBits(GPIOB, GPIO_Pin_15);
#define 		RESET_SPI_CC1101_MOSI	GPIO_ResetBits(GPIOB, GPIO_Pin_15);





#define GPIO_SPI_2_CS                  GPIOB
#define RCC_APB2Periph_GPIO_SPI_2_CS   RCC_APB2Periph_GPIOB
#define GPIO_SPI_2_Pin_CS              GPIO_Pin_12

//___________________________________________________
#define GPIO_SPI_2_NSS             GPIOB
#define GPIO_Pin_SPI_2_NSS         GPIO_Pin_12

#define GPIO_SPI_2_SCK             GPIOB
#define GPIO_Pin_SPI_2_SCK         GPIO_Pin_13

#define GPIO_SPI_2_MISO            GPIOB
#define GPIO_Pin_SPI_2_MISO        GPIO_Pin_14

#define GPIO_SPI_2_MOSI            GPIOB
#define GPIO_Pin_SPI_2_MOSI        GPIO_Pin_15










#define macro_trigger_cc1101_spi_transection SPI_I2S_ITConfig(SPI2, SPI_I2S_IT_TXE, ENABLE);

#endif /* CC1101_SPI_INTERFACE_H_ */
