#include "frame.h"


void pushFrame(Frame frame){
	writeReg(REG_FIFO, frame.id);
	writeReg(REG_FIFO, frame.stamp);
	int i;
	for(i=0;i<FRAME_DATA_SIZE;i++){
		writeReg(REG_FIFO,frame.data[i]);
	}
}

Frame pullFrame(){
	Frame frame;
	frame.id=readReg(REG_FIFO);
	frame.stamp=readReg(REG_FIFO);
	int i;
	for(i=0;i<FRAME_DATA_SIZE;i++){
		frame.data[i]=readReg(REG_FIFO);
	}
	return(frame);
}
