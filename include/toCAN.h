/**
 * @file toCAN.h
 * @class toCAN
 * @brief wrapper for the CAN Bus driver from peak
 * @detail Send from system to CAN
 * @author Danny Behnecke
 */

#include "driveCAN.h"
#include <canDongle/example.h>

#ifndef TO_CAN_H_
#define TO_CAN_H_

class toCAN {
private:
	///message to send
	unsigned char MSG[8];
	/// length of the message
	int lng;
	///received message
	unsigned char recMSG[10];


public:

	///Bus interface object
	driveCAN Bus;
	/**
	 * initialize driver
	 * **/
	toCAN();
	/**
	 * destructor
	 * **/
	virtual ~toCAN();

	void exampleCallback(const canDongle::example::ConstPtr& msg) ;

	/**
	 * set the message to send
	 * @param unsigned char data[8]
	 * @param int length of the message
	 * **/
	void setMSG(unsigned char data[8], int lng);

	/**
	 * get message to send
	 * @return char[8] Msg
	 * **/
	unsigned char* getMSG();
	/**
	 * set message length
	 * @param int message length
	 *
	 * **/
	void setLNG(int l);
	/**
	 * get get message length
	 * @return int message length
	 * **/
	int getLNG();
	/**
	 * get received message
	 *
	 * @return unsigned char[10] received message
	 * **/
	unsigned char* getRecMSG();
	/**
	 * set received msg
	 * @param unsigned char[10] received msg
	 *
	 * **/
	void setRecMSG(unsigned char msg[10]);

	/****/
	template <typename T>
	T swap_endian(T u);
	/**
	 * setter fuer debug bool
	 * **/
	void setDebug(bool b);
};

#endif /* TO_CAN_H_*/
