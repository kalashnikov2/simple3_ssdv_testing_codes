#ifndef fskconfig_h
#define fskconfig_h

#include "dragino.h"
#include "types.h"

// Define FSK Registers
#define REG_PREAMBLE_DETECT 0x1f
#define REG_PREAMBLE_MSB 0x25
#define REG_PREAMBLE_LSB 0x26
#define REG_PACKET_CONFIG_1 0x30
#define REG_PACKET_CONFIG_2 0x31
#define REG_PAYLOAD_LENGTH 0x32
#define REG_FIFO_THRESH 0x35
#define REG_LNA 0x0C
#define REG_FDEV_MSB 0x04
#define REG_FDEV_LSB 0x05
#define REG_BITRATE_MSB 0x02
#define REG_BITRATE_LSB 0x03
#define REG_RSSI_CONFIG 0x0E
#define REG_RSSI_VALUE 0x11

// Define FSK configuration parameters values
#define CRC_ON 0x10
#define CRC_OFF 0x00
#define CRC_AUTOCLEAR_OFF_ON 0x08
#define CRC_AUTOCLEAR_OFF_OFF 0x00
#define FIXED_PAYLOAD_LENGTH_ON 0x80
#define FIXED_PAYLOAD_LENGTH_OFF 0x00
#define PREAMBLE_DETECTION_ON 0x80
#define PREAMBLE_DETECTION_OFF 0x00
#define RSSI_SAMPLE_2 0x00
#define RSSI_SAMPLE_4 0x01
#define RSSI_SAMPLE_8 0x02
#define RSSI_SAMPLE_16 0x03
#define RSSI_SAMPLE_32 0x04
#define RSSI_SAMPLE_64 0x05
#define RSSI_SAMPLE_128 0x06
#define RSSI_SAMPLE_256 0x07


// Define FSK Configuration
typedef struct FSKConfig FSKConfig;
struct FSKConfig {
	byte preambleDetection;
	short preambleSize;
	short fifoThreshold;
	short payloadLength;
	short freqDev;
	short bitrate;
	byte rssiSmoothing;
	byte crcOn;
	byte crcAutoClearOff;
	byte fixedPayloadLength;
};

/**
 * Apply FSK configuration
 */
void applyFSKConfig(FSKConfig fsk);

/**
 * Fetch FSK RSSI
 */
int fetchRSSI();

#endif
