#include "lib/dragino.h"
#include "lib/config.h"
#include "app/frame.h"
#include "app/mobile/app.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main(){

	// Init dragino pins
	initPins();

	// Init sx1276
	reset();

	// Init configuration
	Config config;
	config.mod=MOD_FSK; // Choose modulation
	config.mode=MODE_SLEEP; // Standby mode at startup
	config.cFreq=915000000; // Choose carrier frequency
	config.fsk.preambleSize=1; // Choose preamble size
	config.fsk.crcOn=CRC_OFF; // ON/OFF CRC check
	config.fsk.freqDev=5002; // Choose frequency deviation
	config.fsk.preambleDetection=PREAMBLE_DETECTION_ON; // ON/OFF preamble detection
	config.lnaGain=LNA_GAIN_G1; // Choose LNA GAIN
	config.fsk.crcAutoClearOff=CRC_AUTOCLEAR_OFF_OFF; // ON/OFF CRC autoclean
	config.fsk.bitrate=4800; // Choose bitrate
	config.fsk.fixedPayloadLength=FIXED_PAYLOAD_LENGTH_OFF; // ON/OFF Fixed payload length
	config.fsk.payloadLength=FRAME_SIZE; // Choose payload length
	config.fsk.fifoThreshold=FRAME_SIZE-1; // Choose fifo threshold
	config.paSelect=PA_SELECT_ON; // Toggle PA BOOST
	config.maxPower=12; // Define max power
	config.outputPower=12; // Set the output power
	config.fsk.rssiSmoothing=RSSI_SAMPLE_256; // Set rssi sample
	
	runApp(config); 

	return(0);
}
