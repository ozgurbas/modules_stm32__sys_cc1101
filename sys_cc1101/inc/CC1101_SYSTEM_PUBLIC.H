/*
 * CC1101_SYSTEM_PUBLIC.H
 *
 *  Created on: Mar 17, 2012
 *      Author: nikolai_tesla
 */

#ifndef CC1101_SYSTEM_H_
#define CC1101_SYSTEM_H_



extern u8 u8_array_cc1101_rx_buffer[];

extern u8 u8_array_cc1101_tx_buffer[];


extern u8_byte u8_byte_CC1101_SYSTEM_STATUS;


#define u1_flag_CC1101_SYSTEM_received_package_ready 		u8_byte_CC1101_SYSTEM_STATUS.bits.b7
#define u1_flag_CC1101_SYSTEM_protect_received_package 		u8_byte_CC1101_SYSTEM_STATUS.bits.b6

extern void f_sys_cc1101_command_transmit_and_receive_forever(void);
extern void f_sys_cc1101_command_send_loopback(void);
void f_sys_cc1101_command_send_loopback_response(void);

void f_rf_cc1101_transmit_64_byte_array(u8 x[],u8 length);


#endif /* CC1101_SYSTEM_H_ */
