/*
 * CC1101_SPI_INTERFACE_PUBLIC.H
 *
 *  Created on: Mar 24, 2012
 *      Author: nikolai_tesla
 */

#ifndef CC1101_SPI_INTERFACE_PUBLIC_H_
#define CC1101_SPI_INTERFACE_PUBLIC_H_

#define u8_cc1101_spi_buffer_length	70
extern u8
	u8_array_cc1101_spi_rx_buffer[],
	u8_array_cc1101_spi_tx_buffer[],
	u8_array_cc1101_spi_tx_buffer_front[];
extern u8 u8_cc1101_spi_rx_counter;
extern u8 u8_cc1101_spi_tx_counter;
extern u8 u8_cc1101_spi_tx_limit;



void f_stm32_cc1101_spi_hw_init(void);
void spi_2_send_and_receive_array(u8* send_array,u8 length);
void f_clear_spi_buffers_and_pointers(void);
u8 f_u8_exchange_byte_spi2(u8 x);
void wait_spi(void);

u8 f_stm32_cc1101_spi_start_transmit_buffer(u8 length, u8 *buffer);
void f_stm32_cc1101_spi_reset(void);





//---------------------------------------------------
extern u8_byte u8_byte_stm32_cc1101_spi_SYSTEM_STATUS;

#define u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy	 u8_byte_stm32_cc1101_spi_SYSTEM_STATUS.bits.b7



#endif /* CC1101_SPI_INTERFACE_PUBLIC_H_ */
