#include "gps.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define GPS_DEV_FILE "/dev/ttyS0" // Define GPS serial port file
#define BUFFER_SIZE 100 // Define receive buffer size

/**
 * Configure UART channel
 * TODO : Set baud rate to ???? see NMEA datasheet
 */
void configSerialPort(int fd){
	struct termios Termios;
	tcgetattr(fd,&Termios);
	Termios.c_lflag |= ICANON;
	tcsetattr(fd,TCSANOW,&Termios);
	tcflush(fd, TCIFLUSH); // Clear already received frames
}

/**
 * Fetch NMEA Frame type
 * TODO : Other frame types
 */
NMEA_TYPE getNMEA_TYPE(unsigned char *data){
	unsigned char* typeChar=malloc(sizeof(char)*4);
	typeChar[3]='\0';
	memcpy(typeChar, data+3,3);
	if(strcmp(typeChar, "GGA")==0){
		return(GGA);
	}
	free(typeChar);
	return(NONE);
}

/**
 * Build NMEA frame from array of char
 * TODO : Other GGA parameters
 */
struct NMEA_GGA buildNMEA_GGA(unsigned char *data){
//	data="$GPGGA,095003.000,2055.9571,S,05517.4159,E,1,6,1.59,138.8,M,-9.9,M,,*5D"; // To test !!!
	struct NMEA_GGA frame;
	unsigned char *buffer=malloc(sizeof(char)*strlen(data));
	memcpy(buffer,data,strlen(data));

	short i=1;
	char *saveP;
	char *token=strtok_r(buffer,",",&saveP);
	while(token!=NULL){
		if(strlen(token)>0){
			char tmp[6];
			switch(i){
				case 2: // Fetch hour, min, sec and ms
					memcpy(tmp,token,2);tmp[2]='\0';
					frame.hour=atoi(tmp);
					memcpy(tmp,token+2,2);
					frame.min=atoi(tmp);
					memcpy(tmp,token+4,2);
					frame.sec=atoi(tmp);
					memcpy(tmp,token+7,3);tmp[3]='\0';
					frame.ms=atoi(tmp);
					break;
				case 3: // Fetch Latitude
					memcpy(tmp,token,2);tmp[2]='\0';
					frame.latDeg=atoi(tmp);
					memcpy(tmp,token+2,2);
					frame.latMin=atoi(tmp);
					memcpy(tmp,token+5,4);tmp[4]='\0';
					frame.latSec=atoi(tmp);
					frame.latSec=frame.latSec/10000;
					frame.latSec=(3600*frame.latSec)/60; // Convertion degrès min en degrès sec
					break;
				case 4: // Fetch latitude direction
					frame.latDir=token[0];
					break;
				case 5: // Fetch longitude
					memcpy(tmp,token,3);tmp[3]='\0';
					frame.lonDeg=atoi(tmp);
					tmp[2]='\0';
					memcpy(tmp,token+3,2);
					frame.lonMin=atoi(tmp);
					memcpy(tmp,token+6,4);tmp[4]='\0';
					frame.lonSec=atoi(tmp);
					frame.lonSec=frame.lonSec/10000;
					frame.lonSec=(3600*frame.lonSec)/60; // Convertion degrès min en degrès sec
					break;
				case 6: // Fetch longitude direction
					frame.lonDir=token[0];
					break;
				case 7: // Fetch GPS state
					frame.state=atoi(token);
					break;
				case 8: // Fetch number of statellites
					frame.sats=atoi(token);
					break;
			}
		}
		token=strtok_r(NULL,",",&saveP);
		i++;
	}

	free(buffer);
	return(frame);

}

/**
 * Fetch NMEA FRAME
 */
struct NMEA_GGA getNMEA_GGAFrame(){

	int fd; // File descriptor
	const char *device = "/dev/ttyS0";
	fd = open(device, O_RDWR);
	if(fd == -1) {
		printf( "Failed to open gps device.\n" );
	}
	
	// Configure the serial port
	configSerialPort(fd);

	struct NMEA_GGA frame; // Def empty frame
	short i;
	// Try to feth the GGA frame (100 times max)
	for(i=0;i<100;i++){
		char out[BUFFER_SIZE];
		memset(out,0,BUFFER_SIZE);
		read(fd,out,BUFFER_SIZE);
		if(strlen(out)>1){
			if(getNMEA_TYPE(out)==GGA){
				frame=buildNMEA_GGA(out);
				//if(frame.state!=UNFIXED){
				//	printf("%d:%d:%d:%d\nLat : %d deg %d min %f sec %d Dir\n",frame.hour,frame.min,frame.sec,frame.ms,frame.latDeg,frame.latMin,frame.latSec, frame.latDir);
				//	printf("Lon : %d deg %d min %f sec %d Dir\n",frame.lonDeg,frame.lonMin,frame.lonSec, frame.lonDir);
				//	printf("Sats : %d",frame.sats);
				//	printf("%s",out);
				//}
				break; // If the frame is found, exit
			}
		}
	}
	close(fd);
	return(frame);
}
