#ifndef config_h
#define config_h

#include "dragino.h"
#include "types.h"
#include "fskconfig.h"
#include <math.h>

// Define General Registers
#define REG_FIFO 0x00
#define REG_OP_MODE 0x01
#define REG_VERSION 0x42
#define REG_FRF_MSB 0x06
#define REG_FRF_MID 0x07
#define REG_FRF_LSB 0x08
#define REG_PA_CONFIG 0x09

// Define General Registers values
#define MODE_SLEEP 0x00
#define MODE_STDBY 0x01
#define MODE_TX 0x03
#define MODE_RX 0x05
#define MOD_LORA 0x80
#define MOD_FSK 0x00
#define MOD_OOK 0x40
#define LNA_GAIN_G1 0x20
#define LNA_GAIN_G2 0x40
#define LNA_GAIN_G3 0x60
#define LNA_GAIN_G4 0x80
#define LNA_GAIN_G5 0xA0
#define LNA_GAIN_G6 0xC0
#define PA_SELECT_ON 0x80
#define PA_SELECT_OFF 0x00



// Define global configuration
typedef struct Config Config;
struct Config {
	byte mod;
	byte mode;
	int cFreq;
	FSKConfig fsk; // FSK Specific configuration
	byte lnaGain;
	byte paSelect;
	short maxPower;
	short outputPower;
	// TODO LORA Specific configuration
};


/**
 * Apply global configuration (module mode is unchanged here)
 */
void applyConfig(Config config);

/**
 * Change SX1276 mode (SLEEP, TX, RX etc...)
 */
void applyMode(Config config);

#endif
