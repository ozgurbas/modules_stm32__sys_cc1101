/*
 * RF_PROTOCOL_SYSTEM.C
 *
 *  Created on: Mar 25, 2012
 *      Author: nikolai_tesla
 */
#include "definitions_global.h"

#include "CC1101_SYSTEM_PUBLIC.H"

#include "IO_CONTROL.H"

//void f_tasking_1_ms_base_sys_rf_protocol(void)
//{
//	u8 i,j;
//
//	if(u1_flag_CC1101_SYSTEM_protect_received_package==1)
//	{
////old protocol
////		if(u8_array_cc1101_rx_buffer[0]=='A')		//*** direct data, no id , no enc.
////		{
////			//[[[[[[[[[[[[[[[[[[[[[[[[[[[[
////			if(u8_array_cc1101_rx_buffer[1]=='A') 	//'A' loopback	query
////			{
////				u8_array_cc1101_tx_buffer[0]='B';
////				for(i=1;i<64;i++)
////				{
////					u8_array_cc1101_tx_buffer[i]=u8_array_cc1101_rx_buffer[i];
////				}
////
////				//trigger tx
////				f_sys_cc1101_command_send_loopback_response();
////
////			}
////			else if(u8_array_cc1101_rx_buffer[1]=='B') 	//'B' loopback response
////			{
////
////			}
////
////			else if(u8_array_cc1101_rx_buffer[1]=='C') 	//'C' DIRECT COMMAND
////			{
////			#ifdef def_enable_direct_open_rf_command
////				//example: ACCIAHI ACWIA2S
////				if(u8_array_cc1101_rx_buffer[2]=='W') 	//'W' io command
////				{
////					if(u8_array_cc1101_rx_buffer[3]=='I') //'I' > io
////					{
////						f_write_port_bit_value(u8_array_cc1101_rx_buffer[4],u8_array_cc1101_rx_buffer[5],u8_array_cc1101_rx_buffer[6]);
////					}
////				}
////				else if(u8_array_cc1101_rx_buffer[2]=='C') //'C' > configurate
////				{
////
////					//PORT CONFIGURATION COMMANDS
////					if(u8_array_cc1101_rx_buffer[3]=='I')
////					{
////						//f_PORT_CONFIGURATION_COMMANDS();
////						f_conf_port_directions(u8_array_cc1101_rx_buffer[4],u8_array_cc1101_rx_buffer[5],u8_array_cc1101_rx_buffer[6]);
////					}
////
////
////				}
////			#endif
////
////			}
////
////			//]]]]]]]]]]]]]]]]]]]]]]]]]]]]
////		}
////
////		else if(u8_array_cc1101_rx_buffer[0]=='B')		//*** direct data, no id , no enc.
////		{
////			//[[[[[[[[[[[[[[[[[[[[[[[[[[[[
////
////			//]]]]]]]]]]]]]]]]]]]]]]]]]]]]
////		}
//
//
//
//
//
//
//
//
//		u1_flag_CC1101_SYSTEM_received_package_ready=0;
//		u1_flag_CC1101_SYSTEM_protect_received_package=0;
//
//	}
//
//
//
//}


