/*
 * CC1101_SYSTEM.C
 *
 *  Created on: Mar 17, 2012
 *      Author: nikolai_tesla
 */


#include "definitions_global.h"

#include "CC1101_SYSTEM_DEFINITIONS.H"
#include "CC1101_SYSTEM_PRIVATE_VARIABLES.H"

#include "CC1101.H"
#include "CC1101_CONF.H"

#include "CC1101_SPI_INTERFACE_DEFINITIONS.H"
#include "CC1101_SPI_INTERFACE_PUBLIC.H"


#include "LED_SYS_PUBLIC.H"







//10.1  Chip Status Byte
//7  CHIP_RDYn  Stays high until power and crystal have stabilized. Should always be low when using
//the SPI interface.
//
//
//6:4  STATE[2:0]  Indicates the current main state machine mode
//Value  State  Description
//000  IDLE  IDLE state
//(Also reported for some transitional states instead
//of SETTLING or CALIBRATE)
//001  RX  Receive mode
//010  TX  Transmit mode
//011  FSTXON  Fast TX ready
//100  CALIBRATE  Frequency synthesizer calibration is running
//101  SETTLING  PLL is settling
//110  RXFIFO_OVERFLOW  RX FIFO has overflowed. Read out any
//useful data, then flush the FIFO with SFRX
//111  TXFIFO_UNDERFLOW  TX FIFO has underflowed. Acknowledge with
//SFTX
//
//3:0  FIFO_BYTES_AVAILABLE[3:0]  The number of bytes available in the RX FIFO or free bytes in the TX FIFO

//************************************************************************************************


void f_sys_cc1101_command_transmit_and_receive_forever(void);
void f_sys_cc1101_command_send_loopback(void);

extern u8 usbhidtxbuf[];
extern u8 usbhidrxbuf[];


void f_rf_cc1101_transmit_64_byte_array(u8 x[],u8 length)
{
	u8 i;
	for(i=0;i<64;i++)
	{
		if(i<length)
		{
			u8_array_cc1101_tx_buffer[i]=x[i];
		}
		else
		{
			u8_array_cc1101_tx_buffer[i]=0;
		}
	}

	f_sys_cc1101_command_transmit_and_receive_forever();
}

u8 f_rf_cc1101_command_from_usb(void)
{
	u8 i,j;
	//usbhidrxbuf[0] was 'R'
	if( (usbhidrxbuf[1]=='G') && (usbhidrxbuf[2]=='S') ) //get rf status
	{


		usbhidtxbuf[0]='R';
		usbhidtxbuf[1]='G';
		usbhidtxbuf[2]='S';
		usbhidtxbuf[3]=u8_byte_cc1101_MARCSTATE.byte;
		usbhidtxbuf[4]=u8_byte_cc1101_PKTSTATUS.byte;
		usbhidtxbuf[5]=u8_byte_cc1101_RXBYTES.byte;
		usbhidtxbuf[6]=u8_byte_cc1101_TXBYTES.byte;
		usbhidtxbuf[7]=u8_byte_cc1101_FREQEST.byte;
		usbhidtxbuf[9]=u8_byte_cc1101_LQI.byte;
		usbhidtxbuf[10]=u8_byte_cc1101_VCO_VC_DAC.byte;
		usbhidtxbuf[11]=u8_byte_cc1101_RSSI.byte;
		usbhidtxbuf[12]=u8_sys_cc1101_state;
		usbhidtxbuf[13]=u8_sys_cc1101_command;
		usbhidtxbuf[14]=u8_byte_CC1101_SYSTEM_STATUS.byte;
		usbhidtxbuf[15]=u8_byte_CC1101_SYSTEM_CONTROL.byte;
//		usbhidtxbuf[16]=u8_byte_cc1101_TXBYTES.byte;
//		usbhidtxbuf[17]=u8_byte_cc1101_FREQEST.byte;
//		usbhidtxbuf[19]=u8_byte_cc1101_LQI.byte;
//		usbhidtxbuf[20]=u8_byte_cc1101_VCO_VC_DAC.byte;

		return 1;
	}

	else if( (usbhidrxbuf[1]=='G') && (usbhidrxbuf[2]=='R') ) //get receive buffer
	{
		if(usbhidrxbuf[3]=='1')
		{
			j=0;
			usbhidtxbuf[3]='1';
		}
		else
		{
			j=32;
			usbhidtxbuf[3]='2';
		}

		usbhidtxbuf[0]='R';
		usbhidtxbuf[1]='G';
		usbhidtxbuf[2]='R';
		//usbhidtxbuf[3]='1';

		//j=0;


    	for(i=4;i<36;i++)
    	{
    		usbhidtxbuf[i]=u8_array_cc1101_rx_buffer[j];
    		j++;
    	}



		return 1;
	}

	else if( (usbhidrxbuf[1]=='T') && (usbhidrxbuf[2]=='L') ) //transmit loop back
	{
		f_sys_cc1101_command_send_loopback();

		return 0;
	}
	else if( (usbhidrxbuf[1]=='T') && (usbhidrxbuf[2]=='D') ) //transmit direct
	{

		j=3;
    	for(i=0;i<50;i++)
    	{
    		u8_array_cc1101_tx_buffer[i]=usbhidrxbuf[j];
    		j++;
    	}

    	f_sys_cc1101_command_transmit_and_receive_forever();

		return 0;
	}
	else
	{
		return 0;
	}



}


void f_sys_cc1101_command_send_loopback(void)
{
	u8_array_cc1101_tx_buffer[0]='A';
	u8_array_cc1101_tx_buffer[1]='A';

	u8_array_cc1101_tx_buffer[2]='O';
	u8_array_cc1101_tx_buffer[3]='Z';
	u8_array_cc1101_tx_buffer[4]='G';
	u8_array_cc1101_tx_buffer[5]='U';
	u8_array_cc1101_tx_buffer[6]='R';

	f_sys_cc1101_command_transmit_and_receive_forever();
}

void f_sys_cc1101_command_send_loopback_response(void)
{
	u8_array_cc1101_tx_buffer[0]='A';
	u8_array_cc1101_tx_buffer[1]='B';

	u8_array_cc1101_tx_buffer[2]='B';
	u8_array_cc1101_tx_buffer[3]='A';
	u8_array_cc1101_tx_buffer[4]='S';
	u8_array_cc1101_tx_buffer[5]='.';
	u8_array_cc1101_tx_buffer[6]='.';

	f_sys_cc1101_command_transmit_and_receive_forever();
}

void f_sys_cc1101_command_transmit_and_receive_forever(void)
{
	u1_flag_CC1101_SYSTEM_package_transmitted=0;
	u8_sys_cc1101_command=def_u8_sys_cc1101_command_transmit_and_receive_forever;
}

void f_tasking_1_ms_base_sys_cc1101(void)
{
	u8 i,j,k,d;





	if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_idle) //every operation passes here before or after!!!
	{
		//command operating state, no process will be applied, only state change is possible

		//command reception
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if(u8_sys_cc1101_command==def_u8_sys_cc1101_command_nop)
		{

		}
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		else if(u8_sys_cc1101_command==def_u8_sys_cc1101_command_receive_forever)
		{
			if(u1_flag_CC1101_SYSTEM_protect_receive_state_error==1)
			{
				u1_flag_CC1101_SYSTEM_protect_receive_state_error=0;

				u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_init;

			}
			else
			{
				u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_get_status; //continue receive operation
			}
		}
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		else if(u8_sys_cc1101_command==def_u8_sys_cc1101_command_transmit_and_receive_forever)
		{
			if(u1_flag_CC1101_SYSTEM_package_transmitted==1)
			{
				u8_sys_cc1101_command=def_u8_sys_cc1101_command_receive_forever;
				u1_flag_CC1101_SYSTEM_protect_receive_state_error=1;
			}
			else
			{
				u8_sys_cc1101_state=def_u8_sys_cc1101_state_transmit_init_front_wait;
				u16_sys_cc1101_1ms_down_counter=def_u16_rf_transmit_init_front_wait;// 200;
			}

		}

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		else if(u8_sys_cc1101_command==def_u8_sys_cc1101_command_test)
		{

			f_sys_cc1101_command_send_loopback();

		}
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


		//receive forever test
		//u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_init;
		//u1_flag_CC1101_SYSTEM_CONTROL_receive_forever=1;
	}



	//START OF TRANSMIT OPERATION
	//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_transmit_init_front_wait)
	{
		u16_sys_cc1101_1ms_down_counter--;
		if(u16_sys_cc1101_1ms_down_counter==0)
		{
			u8_sys_cc1101_state=def_u8_sys_cc1101_state_transmit_init;
		}
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_transmit_init)
	{
		RESET_SPI_CC1101_NSS

		u8_array_cc1101_spi_tx_buffer_front[0]= SIDLE;
		u8_array_cc1101_spi_tx_buffer_front[1]= SFTX;
		u8_array_cc1101_spi_tx_buffer_front[2]= STX;

		f_stm32_cc1101_spi_start_transmit_buffer(3,u8_array_cc1101_spi_tx_buffer_front);

		u8_sys_cc1101_state=def_u8_sys_cc1101_state_transmit_init_wait;

	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_transmit_init_wait)
	{
		if(u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy==0)
		{
			SET_SPI_CC1101_NSS
			//rx command sent

			u8_sys_cc1101_state=def_u8_sys_cc1101_state_transmit_fill_buffer;
		}
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_transmit_fill_buffer)
	{
		u1_flag_sys_led_blink_rf_tx_transection=1;

		RESET_SPI_CC1101_NSS

		u8_array_cc1101_spi_tx_buffer_front[0]=(WRITE_BURST+TXFIFO);

    	for(i=0;i<64;i++)
    	{
    		u8_array_cc1101_spi_tx_buffer_front[i+1]=u8_array_cc1101_tx_buffer[i];
    	}

		f_stm32_cc1101_spi_start_transmit_buffer(65,u8_array_cc1101_spi_tx_buffer_front);


		u8_sys_cc1101_state=def_u8_sys_cc1101_state_transmit_fill_buffer_wait;

	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_transmit_fill_buffer_wait)
	{
		if(u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy==0)
		{
			SET_SPI_CC1101_NSS
			//tx buffer filled

			u8_sys_cc1101_state=def_u8_sys_cc1101_state_idle;
			//end of tx not controlled
			u1_flag_CC1101_SYSTEM_package_transmitted=1;
		}
	}

	//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
	//END OF TRANSMIT OPERATION












	//START OF RECEIVE OPERATION
	//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{
	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_init)
	{
		RESET_SPI_CC1101_NSS

		u8_array_cc1101_spi_tx_buffer_front[0]= SRX;

		f_stm32_cc1101_spi_start_transmit_buffer(1,u8_array_cc1101_spi_tx_buffer_front);

		u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_init_wait;


//		//test:fauult
//		for(i=0;i<64;i++)
//		{
//			u8_array_cc1101_rx_buffer[i]=0;
//		}

	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_init_wait)
	{
		if(u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy==0)
		{
			SET_SPI_CC1101_NSS
			//rx command sent

			u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_get_status;
		}
	}


	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_get_status)
	{
		//get status
    	RESET_SPI_CC1101_NSS

    	u8_array_cc1101_spi_tx_buffer_front[0]=MARCSTATE;
    	u8_array_cc1101_spi_tx_buffer_front[1]=0;
    	u8_array_cc1101_spi_tx_buffer_front[2]=PKTSTATUS;
    	u8_array_cc1101_spi_tx_buffer_front[3]=0;
    	u8_array_cc1101_spi_tx_buffer_front[4]=RXBYTES;
    	u8_array_cc1101_spi_tx_buffer_front[5]=0;



    	f_stm32_cc1101_spi_start_transmit_buffer(6,u8_array_cc1101_spi_tx_buffer_front);

    	u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_get_status_wait;



	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_get_status_wait)
	{
		if(u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy==0)
		{
			SET_SPI_CC1101_NSS
			//status ready
			u8_byte_cc1101_MARCSTATE.byte=u8_array_cc1101_spi_rx_buffer[1];
			u8_byte_cc1101_PKTSTATUS.byte=u8_array_cc1101_spi_rx_buffer[3];
			u8_byte_cc1101_RXBYTES.byte=u8_array_cc1101_spi_rx_buffer[5];

			u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_check_status;
		}
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_check_status)
	{
		//if(u8_byte_cc1101_RXBYTES.byte==64)
		if(u8_byte_cc1101_RXBYTES.byte!=0) //test
		{
			u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_get_buffer;
			u1_flag_sys_led_blink_rf_rx_transection=1;
		}
		else if(u8_byte_cc1101_MARCSTATE.byte!=0x0d)
		{
			//error
			u8_sys_cc1101_state=def_u8_sys_cc1101_state_idle;
			u1_flag_CC1101_SYSTEM_protect_receive_state_error=1;
		}
		//etc

		//if there is no unexpected status, goto wait and pull status again.
		else
		{
			u16_sys_cc1101_1ms_down_counter=def_u16_rf_rx_status_pull_interval; //2000;
			u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_pull_wait_state;
		}
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_get_buffer)
	{
		RESET_SPI_CC1101_NSS

			u8_array_cc1101_spi_tx_buffer_front[0]=(READ_BURST+RXFIFO);

	    	for(i=1;i<65;i++)
	    	{
	    		u8_array_cc1101_spi_tx_buffer_front[i]=0;
	    	}

	    	f_stm32_cc1101_spi_start_transmit_buffer(65,u8_array_cc1101_spi_tx_buffer_front);

	    	u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_get_buffer_wait;

	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_get_buffer_wait)
	{
		if(u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy==0)
		{
			SET_SPI_CC1101_NSS

			if(u1_flag_CC1101_SYSTEM_protect_received_package==0)
			{
				u1_flag_CC1101_SYSTEM_received_package_ready=1; //RX_PACKAGE_READY!!!
				u1_flag_CC1101_SYSTEM_protect_received_package=1;

				//hw faulta atan kod???? ram şişmiş!!!
//				j=0;
//				for(i=0;i<64;i++)
//				{
//
//					u8_array_cc1101_rx_buffer[i]=u8_array_cc1101_spi_rx_buffer[j];
//					j++;
//				}

							for(i=0;i<64;i++)
							{
								u8_array_cc1101_rx_buffer[i]=u8_array_cc1101_spi_rx_buffer[i+1];
							}
			}







			u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_return_idle;


		}

	}


	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_return_idle)
	{

		RESET_SPI_CC1101_NSS

		u8_array_cc1101_spi_tx_buffer_front[0]= SIDLE;

		f_stm32_cc1101_spi_start_transmit_buffer(1,u8_array_cc1101_spi_tx_buffer_front);

		u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_return_idle_wait;

	}


	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_return_idle_wait)
	{
		if(u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy==0)
		{
			SET_SPI_CC1101_NSS
			//rx command sent

			u8_sys_cc1101_state=def_u8_sys_cc1101_state_idle; //receive operation finished succesfully!!!
		}
	}




	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_pull_wait_state)
	{
		//receive statuus pull wait state
		u16_sys_cc1101_1ms_down_counter--;
		if(u16_sys_cc1101_1ms_down_counter==0)
		{
			//u8_sys_cc1101_state=def_u8_sys_cc1101_state_receive_get_status; //loop is forbiden bypassing idle!!!
			u8_sys_cc1101_state=def_u8_sys_cc1101_state_idle;
		}
	}


	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_receive_error)
	{

	}
	//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}
	//END OF RECEIVE OPERATION










	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_get_status)
	{
		//get status
    	RESET_SPI_CC1101_NSS

    	u8_array_cc1101_spi_tx_buffer_front[0]=MARCSTATE;
    	u8_array_cc1101_spi_tx_buffer_front[1]=0;
    	u8_array_cc1101_spi_tx_buffer_front[2]=PKTSTATUS;
    	u8_array_cc1101_spi_tx_buffer_front[3]=0;
    	u8_array_cc1101_spi_tx_buffer_front[4]=RXBYTES;
    	u8_array_cc1101_spi_tx_buffer_front[5]=0;
    	u8_array_cc1101_spi_tx_buffer_front[6]=TXBYTES;
    	u8_array_cc1101_spi_tx_buffer_front[7]=0;


    	f_stm32_cc1101_spi_start_transmit_buffer(8,u8_array_cc1101_spi_tx_buffer_front);

    	u8_sys_cc1101_state=def_u8_sys_cc1101_state_get_status_wait;



	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_get_status_wait)
	{
		if(u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy==0)
		{
			SET_SPI_CC1101_NSS
			//status ready
			u8_byte_cc1101_RXBYTES.byte=u8_array_cc1101_spi_rx_buffer[5];

			u8_sys_cc1101_state=def_u8_sys_cc1101_state_idle;
		}
	}

	//start of init process
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_reset)
	{
		u16_sys_cc1101_1ms_down_counter--;
		if(u16_sys_cc1101_1ms_down_counter==0)
		{
			//initial state

			u8_byte_CC1101_SYSTEM_STATUS.byte=0;

			//***18.1.2  Manual Reset

			//used hw on stm32f103r8t6: SPI2;
			// mosi 	PB15
			// miso 	PB14
			// sck		PB13
			// nss		PB12


			  //***Set SCLK = 1 and SI = 0.

			GPIO_InitTypeDef GPIO_InitStructure;


			  //nss
			  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
			  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			  GPIO_Init(GPIOB, &GPIO_InitStructure);

			  SET_SPI_CC1101_NSS


			  //SCK, MOSI
			  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_13;
			  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			  GPIO_Init(GPIOB, &GPIO_InitStructure);

			  SET_SPI_CC1101_SCK
			  RESET_SPI_CC1101_MOSI


			  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
			  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			  GPIO_Init(GPIOB, &GPIO_InitStructure);



			u8_sys_cc1101_state=def_u8_sys_cc1101_state_init0;
		}
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_init0)
	{
		  //***Strobe CSn low / high.
		RESET_SPI_CC1101_NSS
		u8_sys_cc1101_state=def_u8_sys_cc1101_state_init1;
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_init1)
	{
		SET_SPI_CC1101_NSS
		u8_sys_cc1101_state=def_u8_sys_cc1101_state_init2;
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_init2)
	{
		//***Hold  CSn  low and then  high  for at  least
		//***40 µs relative to pulling CSn low

		RESET_SPI_CC1101_NSS
		u8_sys_cc1101_state=def_u8_sys_cc1101_state_init3;
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_init3)
	{
		//***Pull  CSn  low and wait for  SO  to go low
		//***(CHIP_RDYn).

	    if(GET_SPI_CC1101_MISO==0)
	    {
	    	u8_sys_cc1101_state=def_u8_sys_cc1101_state_init4;
	    }

	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_init4)
	{
		//***Issue the SRES strobe on the SI line.
		u8_byte_cc1101_Chip_Status.byte=f_u8_exchange_byte_cc1101_spi(SRES);

		u8_sys_cc1101_state=def_u8_sys_cc1101_state_configurate;
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_configurate)
	{

		//***When  SO  goes low again, reset is
		//***complete and the chip is in the IDLE state.
	    if(GET_SPI_CC1101_MISO==0)
	    {
	    	SET_SPI_CC1101_NSS
	    	u8_sys_cc1101_state=def_u8_sys_cc1101_state_configuration_wait;

	    	//***the chip is in the IDLE state.

	    	//configurate!!!
	    	//***********************************************************************************************************

	    	wait_spi();
	    	f_stm32_cc1101_spi_hw_init();

	    	f_stm32_cc1101_spi_reset();

	    	wait_spi();

	    	//trigger conf transmit
	    	RESET_SPI_CC1101_NSS

	    	for(i=0;i<54;i++)
	    	{
	    		//u8_array_cc1101_spi_tx_buffer_front[i]=u8_const_array_cc1101_conf_433mhz_250kbps[i];
	    		u8_array_cc1101_spi_tx_buffer_front[i]=u8_const_array_cc1101_conf_868mhz_250kbps_64channel_0dBm_output[i];
	    	}


	    	f_stm32_cc1101_spi_start_transmit_buffer(54,u8_array_cc1101_spi_tx_buffer_front);



	    }
	}

	else if(u8_sys_cc1101_state==def_u8_sys_cc1101_state_configuration_wait)
	{
		if(u1_flag_stm32_cc1101_spi_SYSTEM_STATUS_tx_busy==0)
		{
			SET_SPI_CC1101_NSS
			//CONF OK!!!

			//start up state after configuration
			u8_sys_cc1101_state=def_u8_sys_cc1101_state_idle;
			//u8_sys_cc1101_command=def_u8_sys_cc1101_command_receive_forever;
			f_sys_cc1101_command_send_loopback();
			u1_flag_CC1101_SYSTEM_protect_receive_state_error=1;
		}
	}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//end of init process











}













