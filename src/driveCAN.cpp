/**
 * @file driveCAN.cpp
 * @author Danny Behnecke
 */
#include "driveCAN.h"




driveCAN::driveCAN() {
	INIT = CAN_Initialize(PCAN_USBBUS1, PCAN_BAUD_500K, 0, 0, 0);
	printf("Initialize CAN: %i\n", (int) INIT);
}

driveCAN::~driveCAN() {
}

void driveCAN::talk(unsigned int ID, unsigned char Len, unsigned char* MSG) {

	SendMessage.ID = ID;
	SendMessage.LEN = Len;
	SendMessage.MSGTYPE = PCAN_MESSAGE_STANDARD;
	//memcpy(SendMessage.DATA, MSG, Len);
	for (int i = 0; i < Len; i++) {
		SendMessage.DATA[i] = MSG[i];
	}
	//d for debug
	if (d) {
		printf("Msg ID LEN DATA: %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",(int)SendMessage.ID, (int)SendMessage.LEN,(int)SendMessage.DATA[0],(int)SendMessage.DATA[1],(int)SendMessage.DATA[2],(int)SendMessage.DATA[3],(int)SendMessage.DATA[4],(int)SendMessage.DATA[5],(int)SendMessage.DATA[6],(int)SendMessage.DATA[7]);
	}
	if ((SEND = CAN_Write(PCAN_USBBUS1, &SendMessage)) != PCAN_ERROR_OK) {
		ROS_INFO("CAN_Write Failure!");
	}

}

bool driveCAN::listen() {

	int fd;
	CAN_GetValue(PCAN_USBBUS1, PCAN_RECEIVE_EVENT, &fd, sizeof(int));
	fd_set tempFds = getFds();
	/* Watch stdin (fd 0) to see when it has input. */
	FD_ZERO(&tempFds);
	FD_SET(fd, &tempFds);

	while (select(fd + 1, &tempFds, NULL, NULL, NULL) > 0) {

		RECEIVE = CAN_Read(PCAN_USBBUS1, &RecMessage,
				NULL) == PCAN_ERROR_QRCVEMPTY;

		if (RECEIVE != PCAN_ERROR_OK) {
			//ROS_INFO("READ Error 0x%x\n",(int)RECEIVE);
		}
		return (bool) RECEIVE;
	}
}

TPCANMsg driveCAN::getRecMSG() {
	return RecMessage;
}
fd_set driveCAN::getFds() {
	return Fds;
}
void driveCAN::setDebug(bool d){
	this->d=d;
}
