/*
 * CC1101.H
 *
 *  Created on: Mar 15, 2012
 *      Author: nikolai_tesla
 */

#ifndef CC1101_H_
#define CC1101_H_

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Table 42: Command Strobes
//		Strobe 		Address 	Description
//		Name

#define SRES	0x30    //Reset chip.
#define SFSTXON	0x31    //Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1). If in RX (with CCA):
						//Go to a wait state where only the synthesizer is running (for quick RX / TX turnaround).
#define SXOFF  	0x32  	//Turn off crystal oscillator.
#define SCAL	0x33    //Calibrate frequency synthesizer and turn it off. SCAL can be strobed from IDLE mode without
						//setting manual calibration mode (MCSM0.FS_AUTOCAL=0)
#define SRX		0x34    //Enable RX. Perform calibration first if coming from IDLE and MCSM0.FS_AUTOCAL=1.
#define STX		0x35    //In IDLE state: Enable TX. Perform calibration first if MCSM0.FS_AUTOCAL=1.
						//If in RX state and CCA is enabled: Only go to TX if channel is clear.
#define SIDLE	0x36    //Exit RX / TX, turn off frequency synthesizer and exit Wake-On-Radio mode if applicable.
#define SWOR	0x38    //Start automatic RX polling sequence (Wake-on-Radio) as described in Section 19.5 if
						//WORCTRL.RC_PD=0.
#define SPWD 	0x39   	//Enter power down mode when CSn goes high.
#define SFRX	0x3A    //Flush the RX FIFO buffer. Only issue SFRX in IDLE or RXFIFO_OVERFLOW states.
#define SFTX 	0x3B   	//Flush the TX FIFO buffer. Only issue SFTX in IDLE or TXFIFO_UNDERFLOW states.
#define SWORRST	0x3C    //Reset real time clock to Event1 value.
#define SNOP	0x3D    //No operation. May be used to get access to the chip status byte.


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Table 43: Configuration Registers Overview

#define IOCFG2		0x00    //GDO2 output pin configuration
#define IOCFG1		0x01    //GDO1 output pin configuration
#define IOCFG0		0x02    //GDO0 output pin configuration
#define FIFOTHR		0x03    //RX FIFO and TX FIFO thresholds
#define SYNC1		0x04    //Sync word, high byte
#define SYNC0		0x05    //Sync word, low byte
#define PKTLEN		0x06    //Packet length
#define PKTCTRL1	0x07    //Packet automation control
#define PKTCTRL0	0x08    //Packet automation control
#define ADDR		0x09    //Device address
#define CHANNR		0x0A    //Channel number
#define FSCTRL1		0x0B    //Frequency synthesizer control
#define FSCTRL0		0x0C    //Frequency synthesizer control
#define FREQ2		0x0D    //Frequency control word, high byte
#define FREQ1		0x0E    //Frequency control word, middle byte
#define FREQ0		0x0F    //Frequency control word, low byte
#define MDMCFG4		0x10    //Modem configuration
#define MDMCFG3		0x11    //Modem configuration
#define MDMCFG2		0x12    //Modem configuration
#define MDMCFG1		0x13    //Modem configuration
#define MDMCFG0		0x14    //Modem configuration
#define DEVIATN		0x15    //Modem deviation setting
#define MCSM2		0x16    //Main Radio Control State Machine configuratio
#define MCSM1		0x17    //Main Radio Control State Machine configuratio
#define MCSM0		0x18    //Main Radio Control State Machine configuratio
#define FOCCFG		0x19    //Frequency Offset Compensation configuration
#define BSCFG		0x1A    //Bit Synchronization configuration
#define AGCCTRL2		0x1B    //AGC control
#define AGCCTRL1		0x1C    //AGC control
#define AGCCTRL0		0x1D    //AGC control
#define WOREVT1		0x1E    //High byte Event 0 timeout
#define WOREVT0		0x1F    //Low byte Event 0 timeout
#define WORCTRL		0x20    //Wake On Radio control
#define FREND1		0x21    //Front end RX configuration
#define FREND0		0x22    //Front end TX configuration
#define FSCAL3		0x23    //Frequency synthesizer calibration
#define FSCAL2		0x24    //Frequency synthesizer calibration
#define FSCAL1		0x25    //Frequency synthesizer calibration
#define FSCAL0		0x26    //Frequency synthesizer calibration
#define RCCTRL1		0x27    //RC oscillator configuration
#define RCCTRL0		0x28    //RC oscillator configuration
#define FSTEST		0x29    //Frequency synthesizer calibration control
#define PTEST		0x2A    //Production test
#define AGCTEST		0x2B    //AGC test
#define TEST2		0x2C    //Various test settings
#define TEST1		0x2D    //Various test settings
#define TEST0		0x2E    //Various test settings


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Table 44: Status Registers Overview
//read da catallanıyor; +0xC0 icin
//burst not supported!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define PARTNUM				0xF0//0x30 	//(#define 0xF0)    Part number for CC1101
#define VERSION				0xF1//0x31 	//(#define 0xF1)    Current version number
#define FREQEST				0xF2//0x32 	//(#define 0xF2)    Frequency Offset Estimate
#define LQI					0xF3//0x33 	//(#define 0xF3)    Demodulator estimate for Link Quality
#define RSSI				0xF4//0x34 	//(#define 0xF4)    Received signal strength indication
#define MARCSTATE			0xF5//0x35 	//(#define 0xF5)    Control state machine state
#define WORTIME1			0xF6//0x36 	//(#define 0xF6)    High byte of WOR timer
#define WORTIME0			0xF7//0x37 	//(#define 0xF7)    Low byte of WOR timer
#define PKTSTATUS			0xF8//0x38 	//(#define 0xF8)    Current GDOx status and packet status
#define VCO_VC_DAC			0xF9//0x39 	//(#define 0xF9)   	Current setting from PLL calibration module
#define TXBYTES				0xFA//0x3A 	//(#define 0xFA)   	Underflow and number of bytes in the TX FIFO
#define RXBYTES				0xFB//0x3B 	//(#define 0xFB)   	Overflow and number of bytes in the RX FIFO
#define RCCTRL1_STATUS		0xFC//0x3C 	//(#define 0xFC)    Last RC oscillator calibration result
#define RCCTRL0_STATUS		0xFD//0x3D 	//(#define 0xFD)    Last RC oscillator calibration result


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++




//The following header bytes access the FIFOs:
#define Single_byte_access_to_TX_FIFO           0x3F  //: Single byte access to TX FIFO
#define Burst_access_to_TX_FIFO                 0x7F  //: Burst access to TX FIFO
#define Single_byte_access_to_RX_FIFO           0xBF  //: Single byte access to RX FIFO
#define Burst_access_to_RX_FIFO                 0xFF  //: Burst access to RX FIFO


//// Status registers
//#define PARTNUM          0x30        // Part number
//#define VERSION          0x31        // Current version number
//#define FREQEST          0x32        // Frequency offset estimate
//#define LQI              0x33        // Demodulator estimate for link quality
//#define RSSI             0x34        // Received signal strength indication
//#define MARCSTATE        0x35        // Control state machine state
//#define WORTIME1         0x36        // High byte of WOR timer
//#define WORTIME0         0x37        // Low byte of WOR timer
//#define PKTSTATUS        0x38        // Current GDOx status and packet status
//#define VCO_VC_DAC       0x39        // Current setting from PLL cal module
//#define TXBYTES          0x3A        // Underflow and # of bytes in TXFIFO
//#define RXBYTES          0x3B        // Overflow and # of bytes in RXFIFO


// Multi byte memory locations
#define PATABLE          0x3E
#define TXFIFO           0x3F
#define RXFIFO           0x3F

// Definitions for burst/single access to registers
#define WRITE_SINGLE      0x00
#define WRITE_BURST      0x40
#define READ_SINGLE      0x80
#define READ_BURST       0xC0

//----------------------------------------------------------------------------------
// Chip Status Byte
//----------------------------------------------------------------------------------

// Bit fields in the chip status byte
#define STATUS_CHIP_RDYn_BM             0x80
#define STATUS_STATE_BM                 0x70
#define STATUS_FIFO_BYTES_AVAILABLE_BM  0x0F

// Chip states
#define STATE_IDLE                      0x00
#define STATE_RX                        0x10
#define STATE_TX                        0x20
#define STATE_FSTXON                    0x30
#define STATE_CALIBRATE                 0x40
#define STATE_SETTLING                  0x50
#define STATE_RX_OVERFLOW               0x60
#define STATE_TX_UNDERFLOW              0x70


//----------------------------------------------------------------------------------
// Other register bit fields
//----------------------------------------------------------------------------------
#define LQI_CRC_OK_BM                   0x80
#define LQI_EST_BM                      0x7F



#endif /* CC1101_H_ */
