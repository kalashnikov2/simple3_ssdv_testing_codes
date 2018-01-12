#include "fskconfig.h"

void applyFSKConfig(FSKConfig fsk){
	
	// Set preambleDetection
	byte reg=readReg(REG_PREAMBLE_DETECT)&0x7F;		
	writeReg(REG_PREAMBLE_DETECT, fsk.preambleDetection | reg);

	// Set preamble size
	reg=fsk.preambleSize>>8;
	writeReg(REG_PREAMBLE_MSB, reg);
	reg=fsk.preambleSize & 0x00ff;
	writeReg(REG_PREAMBLE_LSB, reg);

	// Set crcOn
	reg=readReg(REG_PACKET_CONFIG_1) & 0xEF;
	writeReg(REG_PACKET_CONFIG_1,reg|fsk.crcOn);

	// Set crc autoclear
	reg=readReg(REG_PACKET_CONFIG_1) & 0xF7;
	writeReg(REG_PACKET_CONFIG_1,reg|fsk.crcAutoClearOff);

	// Set payloadLength 
	reg=readReg(REG_PACKET_CONFIG_2) & 0xF8;
	byte payloadLengthMSB=(fsk.payloadLength >> 8) &0x7;
	byte payloadLengthLSB=fsk.payloadLength &0xFF;
	writeReg(REG_PACKET_CONFIG_2,payloadLengthMSB|reg);
	writeReg(REG_PAYLOAD_LENGTH, payloadLengthLSB);

	// Set fifo threshold
	reg=readReg(REG_FIFO_THRESH) & 0xC0;
	reg=reg| (fsk.fifoThreshold & 0x3F);
	writeReg(REG_FIFO_THRESH,reg);
	
	// Set fixedPayloadLength	
	reg=readReg(REG_PACKET_CONFIG_1) & 0x7F;
	writeReg(REG_PACKET_CONFIG_1,reg | fsk.fixedPayloadLength);

	// Set frequency dev
	short freqDev=fsk.freqDev/FSTEP;
	byte freqDevMSB=freqDev>>8;
	byte freqDevLSB=freqDev&0x00FF;
	writeReg(REG_FDEV_MSB, freqDevMSB);
	writeReg(REG_FDEV_LSB, freqDevLSB);

	// Apply bitrate //
	short bitrate=FXOSC/fsk.bitrate;
	byte bitrateMSB=bitrate>>8;
	byte bitrateLSB=bitrate & 0x00FF;
	writeReg(REG_BITRATE_MSB, bitrateMSB); 
	writeReg(REG_BITRATE_LSB, bitrate & 0x0F);

	// Apply rssi smoothing
	reg=readReg(REG_RSSI_CONFIG) & 0xF8;
	reg=reg|fsk.rssiSmoothing;
	writeReg(REG_RSSI_CONFIG,reg);
	
}


int fetchRSSI(){
	int value=readReg(REG_RSSI_VALUE);
	value=(-value)/2; // See SX1276 datasheet page 86
	return(value);
}

