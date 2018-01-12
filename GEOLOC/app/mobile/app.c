#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "app.h"
#include "../frame.h"
#include <string.h>
#include <unistd.h>

void runApp(Config config){
	
	// Hello msg
	printf("\n|Starting mobile application|\n\n");

	// Ensure we are in standby mode and apply configuration
	config.mode=MODE_STDBY;
	applyMode(config);
	applyConfig(config);

	// Write frame on sx1276
	Frame frame;
	frame.id=001;
	frame.stamp=00;
	frame.data[0]=232;
	frame.data[1]=424;
	frame.data[2]=484;
	frame.data[3]=323;
	frame.data[4]=424;
	frame.data[5]=444;
	pushFrame(frame);
	
	config.mode=MODE_TX;
	applyMode(config); // Send frame
	
	// Wait for frame to be sending
	while(1){
		if(digitalRead(0x7)==1){
			printf("Packet send !!!\n\n");
			config.mode=MODE_STDBY;
			applyMode(config);
			//saveGPSPosition();
			delay(2000);
			// Write frame on sx1276
			pushFrame(frame);
			//writeReg(REG_FIFO, 'hablalo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!');
			config.mode=MODE_TX;
			applyMode(config); // Send frame
		}
	}
}
