/*
 * CC1101_SYSTEM_DEFINITIONS.H
 *
 *  Created on: Mar 24, 2012
 *      Author: nikolai_tesla
 */

#ifndef CC1101_SYSTEM_DEFINITIONS_H_
#define CC1101_SYSTEM_DEFINITIONS_H_


#define def_u16_rf_rx_status_pull_interval	200
#define def_u16_rf_transmit_init_front_wait 20

//enum u8_sys_cc1101_state            /* Defines an enumeration type    */
//{
//    def_u8_sys_cc1101_state_reset,
//    def_u8_sys_cc1101_state_init0,
//    def_u8_sys_cc1101_state_init1,
//    def_u8_sys_cc1101_state_init2,
//    def_u8_sys_cc1101_state_init3,
//    def_u8_sys_cc1101_state_init4,
//    def_u8_sys_cc1101_state_configurate,
//    def_u8_sys_cc1101_state_configuration_wait,
//    def_u8_sys_cc1101_state_get_status,
//    def_u8_sys_cc1101_state_get_status_wait,
//
//    def_u8_sys_cc1101_state_idle,
//    def_u8_sys_cc1101_state_receive_init,
//    def_u8_sys_cc1101_state_receive_init_wait,
//    def_u8_sys_cc1101_state_receive_get_status,
//    def_u8_sys_cc1101_state_receive_get_status_wait,
//    def_u8_sys_cc1101_state_receive_check_status,
//    def_u8_sys_cc1101_state_receive_get_buffer,
//    def_u8_sys_cc1101_state_receive_get_buffer_wait,
//    def_u8_sys_cc1101_state_receive_return_idle,
//    def_u8_sys_cc1101_state_receive_return_idle_wait,
//    def_u8_sys_cc1101_state_receive_pull_wait_state,
//    def_u8_sys_cc1101_state_receive_error,
//
//
//
//    def_u8_sys_cc1101_state_undefined
//};

#define     def_u8_sys_cc1101_state_reset			0
#define     def_u8_sys_cc1101_state_init0			1
#define     def_u8_sys_cc1101_state_init1 2
#define     def_u8_sys_cc1101_state_init2 3
#define     def_u8_sys_cc1101_state_init3 4
#define     def_u8_sys_cc1101_state_init4 5
#define     def_u8_sys_cc1101_state_configurate 6
#define     def_u8_sys_cc1101_state_configuration_wait 7
#define     def_u8_sys_cc1101_state_get_status 8
#define     def_u8_sys_cc1101_state_get_status_wait 9

#define     def_u8_sys_cc1101_state_idle 10
#define     def_u8_sys_cc1101_state_receive_init 11
#define     def_u8_sys_cc1101_state_receive_init_wait 12
#define     def_u8_sys_cc1101_state_receive_get_status 13
#define     def_u8_sys_cc1101_state_receive_get_status_wait 14
#define     def_u8_sys_cc1101_state_receive_check_status 15
#define     def_u8_sys_cc1101_state_receive_get_buffer 16
#define     def_u8_sys_cc1101_state_receive_get_buffer_wait 17
#define     def_u8_sys_cc1101_state_receive_return_idle 18
#define     def_u8_sys_cc1101_state_receive_return_idle_wait 19
#define     def_u8_sys_cc1101_state_receive_pull_wait_state 20
#define     def_u8_sys_cc1101_state_receive_error 21


#define     def_u8_sys_cc1101_state_transmit_init 22
#define     def_u8_sys_cc1101_state_transmit_init_wait 23
#define     def_u8_sys_cc1101_state_transmit_fill_buffer 24
#define     def_u8_sys_cc1101_state_transmit_fill_buffer_wait 25
#define     def_u8_sys_cc1101_state_transmit_start 26
#define     def_u8_sys_cc1101_state_transmit_start_wait 27
#define     def_u8_sys_cc1101_state_transmit_init_front_wait 28




//command set
#define     def_u8_sys_cc1101_command_nop								0
#define     def_u8_sys_cc1101_command_receive							1
#define     def_u8_sys_cc1101_command_receive_forever					2
#define     def_u8_sys_cc1101_command_cancel_receive					3
#define     def_u8_sys_cc1101_command_transmit							4
#define     def_u8_sys_cc1101_command_transmit_forever					5
#define     def_u8_sys_cc1101_command_cancel_transmit					6

#define     def_u8_sys_cc1101_command_transmit_and_receive				7
#define     def_u8_sys_cc1101_command_transmit_and_receive_forever		8

#define     def_u8_sys_cc1101_command_test								100


#endif /* CC1101_SYSTEM_DEFINITIONS_H_ */
