#include "config.h"

void applyConfig(Config config){

	// Apply modulation and mode
	byte reg=readReg(REG_OP_MODE) &0x3F ; // Fetch opmode register and clear modulation and mode bits
	reg=reg | config.mod; // Apply modulation and mode
	writeReg(REG_OP_MODE,reg); // Send register back to module

	// Apply carrier frequency
	int cFreq=config.cFreq/FSTEP;
	reg=cFreq >> 16 ;
	writeReg(REG_FRF_MSB,reg); // Send register to module
	reg=(cFreq&0x00FFFF) >> 8 ;
	writeReg(REG_FRF_MID,reg); /// Send register to module
	reg=(cFreq&0x0000FF);
	writeReg(REG_FRF_LSB,reg); // Send register to module

	// Set LNAGain
	reg=readReg(REG_LNA) & 0x7F;
	writeReg(REG_LNA, reg|config.lnaGain);
	

	// Apply PaBoost, max output power and outputPower
	byte Pmax=round((config.maxPower-10.8)/0.6);
	Pmax=(Pmax & 0x07)<<4;
	byte outputPower;
	if(config.paSelect==PA_SELECT_ON){
		outputPower=config.outputPower-32;
	}
	else{
		outputPower=config.outputPower-Pmax+15;
	}
	outputPower=config.outputPower & 0x0F;
	reg=config.paSelect|outputPower|Pmax;
	writeReg(REG_PA_CONFIG, reg);


	// Apply FSK configuration
	if(config.mod==MOD_FSK){
		applyFSKConfig(config.fsk);
	}
}

void applyMode(Config config){
	// Apply modulation and mode
	byte reg=readReg(REG_OP_MODE) &0xF8 ; // Fetch opmode register and clear mode
	reg=config.mode | reg; // Apply mode
	writeReg(REG_OP_MODE,reg); // Send register back to module

}
