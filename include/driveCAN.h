/**
 * @file driveCAN.h
 * @class driveCAN
 * @brief wrapper for the CAN Bus driver from peak
 * @detail
 * @author Danny Behnecke
 */

#ifndef DRIVE_CAN_H_
#define DRIVE_CAN_H_

/**
 * Definiere True und False für msg uebernahme
 * **/
#ifndef True
#define True 1
#endif
#ifndef False
#define False 0
#endif

#include <string.h>
#include <stdio.h>
#include "ros/ros.h"

#include <unistd.h>
#include <asm/types.h>
#include <pthread.h>
#include <sys/time.h>

#define DWORD  __u32
#define WORD   unsigned short
#define BYTE   unsigned char
#define LPSTR  char*

#include <PCANBasic.h>
//#include <pcan.h>


class driveCAN {
private:
	TPCANMsg SendMessage,RecMessage;
	TPCANStatus INIT,SEND,RECEIVE;
	fd_set Fds;
	bool d;//d for debug

public:
	/**
	 * @brief constructor, initializes driver
	 *
	 * */
	driveCAN();

	///Destruktor
	virtual ~driveCAN();

	/**
	 * sends message to CAN bus
	 * @param unsigned int ID
	 * @param unsigned char Len message length
	 * @param unsigned char* MSG message
	 * **/
	void talk(unsigned int ID, unsigned char Len, unsigned char* MSG);

	/**
	 * listens for message from CAN bus
	 * returns true if the device is still open, otherwise false	
	 * **/
	bool listen();

	TPCANMsg getRecMSG();

	fd_set getFds();
	/**
	 * setter fuer debug bool
	 * **/
	void setDebug(bool d);

};
#endif /* DRIVE_CAN_H_ */
