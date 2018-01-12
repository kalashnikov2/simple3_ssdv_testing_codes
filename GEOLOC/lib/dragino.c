#include "dragino.h"


void initPins(){
	// Init WiringPi
	wiringPiSetup();
	pinMode(NSS_PIN, OUTPUT);
	pinMode(DIO0_PIN, INPUT);
	pinMode(RESET_PIN, OUTPUT);
	wiringPiSPISetup(CHANNEL, BIT_RATE);
}

byte readReg(byte address){
	byte buffer[2];
	buffer[0]=address & 0x7F; // Set read flag (SX1276 datasheet page 80)
	buffer[1]=0x00;

	digitalWrite(NSS_PIN, LOW);
	wiringPiSPIDataRW(CHANNEL, buffer, 2);
	digitalWrite(NSS_PIN, HIGH);

	return(buffer[1]);
}
void writeReg(byte address, byte data){
	byte buffer[2];
	buffer[0]=address | 0x80; // Set write flag (SX1276 datasheet page 80)
	buffer[1]=data;

	digitalWrite(NSS_PIN, LOW);
	wiringPiSPIDataRW(CHANNEL, buffer, 2);
	digitalWrite(NSS_PIN, HIGH);
}

void reset(){
	// SX1276 datasheet page 116
	digitalWrite(RESET_PIN, LOW);
	delay(100);
	digitalWrite(RESET_PIN, HIGH);
	delay(100);
}
