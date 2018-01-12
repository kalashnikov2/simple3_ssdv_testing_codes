#ifndef gps_h
#define gps_h

/**
 * Define NMEA frame types
 */
typedef enum NMEA_TYPE NMEA_TYPE;
enum NMEA_TYPE { GGA=125,NONE }; // TODO : other frame type

/**
 * Define compass N,S,E,W
 */
typedef enum COMPASS COMPASS;
enum COMPASS { NORTH=78, SOUTH=83, EAST=69, WEST=87};

/**
 * Define GPS state
 */
typedef enum GPS_STATE GPS_STATE;
enum GPS_STATE { FIXED_GPS=1, FIXED_DGPS=2, UNFIXED=0};

/**
 * Define NMEA GGA FRAME
 */
struct NMEA_GGA {
	short hour;
	short min;
	short sec;
	short ms;

	short latDeg;
	short latMin;
	float latSec;
	COMPASS latDir;

	short lonDeg;
	short lonMin;
	float lonSec;
	COMPASS lonDir;

	short sats;
	GPS_STATE state;

	// TODO : Finish Frame

};

/**
 * Fetch the last NMEA_GGA frame
 */
struct NMEA_GGA getNMEA_GGAFrame();

#endif
