#ifndef dragino_h
#define dragino_h

#include "types.h"
#include <wiringPi.h>
#include <wiringPiSPI.h>

// Define WiringPi Parameters
#define CHANNEL 0
#define BIT_RATE 500000

// Define dragino shield pin for use SPI protocol (see http://wiki.dragino.com/index.php?title=Lora/GPS_HAT)
#define NSS_PIN 6
#define RESET_PIN 0
#define DIO0_PIN 7
#define TX_PIN 15

/**
 * Configure WiringPi for SPI
 */
void initPins();

/**
 * Used to init and reset SX1276
 */
void reset();

/**
 * Read in SX1276 register
 */
byte readReg(byte address);

/**
 * Write in SX1276 register
 */
void writeReg(byte address, byte value);

#endif
