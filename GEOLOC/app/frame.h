#ifndef frame_h
#define frame_h

#define FRAME_SIZE 256
#define FRAME_DATA_SIZE 256

#include "../lib/types.h"
#include "../lib/dragino.h"
#include "../lib/config.h"

typedef struct Frame Frame;
struct Frame {
	byte id;
	byte stamp;
	byte data[FRAME_DATA_SIZE];
};

void pushFrame(Frame frame);
Frame pullFrame();

#endif
