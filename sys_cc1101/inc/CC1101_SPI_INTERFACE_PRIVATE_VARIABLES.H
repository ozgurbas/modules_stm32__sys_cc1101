/*
 * CC1101_SPI_INTERFACE_PRIVATE_VARIABLES.H
 *
 *  Created on: Mar 24, 2012
 *      Author: nikolai_tesla
 */

#ifndef CC1101_SPI_INTERFACE_PRIVATE_VARIABLES_H_
#define CC1101_SPI_INTERFACE_PRIVATE_VARIABLES_H_


#define u8_cc1101_spi_buffer_length	70
u8
	u8_array_cc1101_spi_rx_buffer[u8_cc1101_spi_buffer_length],
	u8_array_cc1101_spi_tx_buffer[u8_cc1101_spi_buffer_length],
	u8_array_cc1101_spi_tx_buffer_front[u8_cc1101_spi_buffer_length];

u8 u8_cc1101_spi_rx_counter;
u8 u8_cc1101_spi_tx_counter;
u8 u8_cc1101_spi_tx_limit;


//---------------------------------------------------
u8_byte u8_byte_stm32_cc1101_spi_SYSTEM_STATUS;

#define u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy	 u8_byte_stm32_cc1101_spi_SYSTEM_STATUS.bits.b7




#endif /* CC1101_SPI_INTERFACE_PRIVATE_VARIABLES_H_ */
