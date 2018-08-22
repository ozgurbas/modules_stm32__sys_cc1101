/*
 * CC1101_CONF.H
 *
 *  Created on: Mar 18, 2012
 *      Author: nikolai_tesla
 */

#ifndef CC1101_CONF_H_
#define CC1101_CONF_H_

#include "CC1101.H"

//
// Rf settings for CC1101
//

const u8 u8_const_array_cc1101_conf[42]={
IOCFG0,0x06,  //GDO0 Output Pin Configuration
FIFOTHR,0x47, //RX FIFO and TX FIFO Thresholds
PKTCTRL0,0x05,//Packet Automation Control
FSCTRL1,0x06, //Frequency Synthesizer Control
FREQ2,0x21,   //Frequency Control Word, High Byte
//10
FREQ1,0x62,   //Frequency Control Word, Middle Byte
FREQ0,0x76,   //Frequency Control Word, Low Byte
MDMCFG4,0xF5, //Modem Configuration
MDMCFG3,0x83, //Modem Configuration
MDMCFG2,0x13, //Modem Configuration
//20
DEVIATN,0x15, //Modem Deviation Setting
MCSM0,0x18,   //Main Radio Control State Machine Configuration
FOCCFG,0x16,  //Frequency Offset Compensation Configuration
WORCTRL,0xFB, //Wake On Radio Control
FSCAL3,0xE9,  //Frequency Synthesizer Calibration
//30
FSCAL2,0x2A,  //Frequency Synthesizer Calibration
FSCAL1,0x00,  //Frequency Synthesizer Calibration
FSCAL0,0x1F,  //Frequency Synthesizer Calibration
TEST2,0x81,   //Various Test Settings
TEST1,0x35,   //Various Test Settings
//40
TEST0,0x09   //Various Test Settings
//42
};


const u8 u8_const_array_cc1101_conf_433mhz_250kbps[54]={
		IOCFG0,0x06,
		FIFOTHR,0x47, //(0x77) hassaslık azalıyor saturasyon -15 den +3 e çıkıyor.
		FSCTRL1,0x0c,
		FREQ2,0x10,
		FREQ1,0xb1,

		//11
		FREQ0,0x3b,
		MDMCFG4,0x2d,
		MDMCFG3,0x3b,
		MDMCFG2,0x13,
		DEVIATN,0x62,

		//21
		MCSM0,0x18,
		FOCCFG,0x1d,
		BSCFG,0x1c,
		AGCCTRL2,0xC7,
		AGCCTRL1,0x00,

		//31
		AGCCTRL0,0xB0,
		WORCTRL,0xFB,
		FREND1,0xB6,
		FSCAL3,0xEA,
		FSCAL2,0x2A,

		//41
		FSCAL1,0x00,
		FSCAL0,0x1F,
		TEST0,0x09,
		PKTLEN,64,
		PKTCTRL1,8, //crc auto flush enabled

		//51
		PKTCTRL0,4, //crc calc enabled, fixed size package length.
		PATABLE,0x03 //−30 Output Power [dBm]
		//54

};


const u8 u8_const_array_cc1101_conf_868mhz_250kbps_64channel_0dBm_output[54]={
		IOCFG0,0x06,
		FIFOTHR,0x47, //(0x77) hassaslık azalıyor saturasyon -15 den +3 e çıkıyor.
		FSCTRL1,0x0c,
		FREQ2,0x21,
		FREQ1,0x62,

		//11
		FREQ0,0x76,
		MDMCFG4,0x2d,
		MDMCFG3,0x3b,
		MDMCFG2,0x13,
		DEVIATN,0x62,

		//21
		MCSM0,0x18,
		FOCCFG,0x1d,
		BSCFG,0x1c,
		AGCCTRL2,0xC7,
		AGCCTRL1,0x00,

		//31
		AGCCTRL0,0xB0,
		WORCTRL,0xFB,
		FREND1,0xB6,
		FSCAL3,0xEA,
		FSCAL2,0x2A,

		//41
		FSCAL1,0x00,
		FSCAL0,0x1F,
		TEST0,0x09,
		PKTLEN,64,
		PKTCTRL1,8, //crc auto flush enabled

		//51
		PKTCTRL0,4, //crc calc enabled, fixed size package length.
		//PATABLE,0x03 //−30 Output Power [dBm]
		PATABLE,0x50 //0 Output Power [dBm]
		//54

};







#endif /* CC1101_CONF_H_ */
