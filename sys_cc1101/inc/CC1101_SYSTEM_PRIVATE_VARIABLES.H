/*
 * CC1101_SYSTEM_PRIVATE_VARIABLES.H
 *
 *  Created on: Mar 24, 2012
 *      Author: nikolai_tesla
 */

#ifndef CC1101_SYSTEM_PRIVATE_VARIABLES_H_
#define CC1101_SYSTEM_PRIVATE_VARIABLES_H_




u8 u8_array_cc1101_rx_buffer[64];

u8 u8_array_cc1101_tx_buffer[64];




u8 u8_sys_cc1101_state=def_u8_sys_cc1101_state_reset;
u16 u16_sys_cc1101_1ms_down_counter=2000;

u8 rf_rx_package_counter=0;


u8_byte u8_byte_cc1101_Chip_Status;

u8_byte u8_byte_cc1101_PARTNUM;
u8_byte u8_byte_cc1101_VERSION;
u8_byte u8_byte_cc1101_FREQEST;
u8_byte u8_byte_cc1101_LQI;
u8_byte u8_byte_cc1101_RSSI;
u8_byte u8_byte_cc1101_MARCSTATE;
u8_byte u8_byte_cc1101_WORTIME1;
u8_byte u8_byte_cc1101_WORTIME0;
u8_byte u8_byte_cc1101_PKTSTATUS;
u8_byte u8_byte_cc1101_VCO_VC_DAC ;
u8_byte u8_byte_cc1101_TXBYTES;
u8_byte u8_byte_cc1101_RXBYTES;
u8_byte u8_byte_cc1101_RCCTRL1_STATUS;
u8_byte u8_byte_cc1101_RCCTRL0_STATUS;

//---------------------------------------------------
u8_byte u8_byte_CC1101_SYSTEM_STATUS;

#define u1_flag_CC1101_SYSTEM_received_package_ready 		u8_byte_CC1101_SYSTEM_STATUS.bits.b7
#define u1_flag_CC1101_SYSTEM_protect_received_package 		u8_byte_CC1101_SYSTEM_STATUS.bits.b6
#define u1_flag_CC1101_SYSTEM_protect_receive_state_error 		u8_byte_CC1101_SYSTEM_STATUS.bits.b5
#define u1_flag_CC1101_SYSTEM_package_transmitted 		u8_byte_CC1101_SYSTEM_STATUS.bits.b4


u8_byte u8_byte_CC1101_SYSTEM_CONTROL;

#define u1_flag_CC1101_SYSTEM_CONTROL_receive_forever 				u8_byte_CC1101_SYSTEM_STATUS.bits.b7
#define u1_flag_CC1101_SYSTEM_CONTROL_receive_after_transmit 		u8_byte_CC1101_SYSTEM_STATUS.bits.b6


u8 u8_sys_cc1101_command=def_u8_sys_cc1101_state_reset;


#endif /* CC1101_SYSTEM_PRIVATE_VARIABLES_H_ */
