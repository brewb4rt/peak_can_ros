/**
 * @file toCAN.cpp
 * @author Danny Behnecke
 */

#include "toCAN.h"




void toCAN::exampleCallback(const canDongle::example::ConstPtr &msg) {
    //ROS_INFO("motor_Callback: Baem!\r\n");
    canDongle::example ex;

    ex.can_id = msg->can_id;
    ex.length = msg->length;
    unsigned char tempMsg[8] = { msg->value };


    Bus.talk(ex.can_id, ex.length, tempMsg);

}


toCAN::toCAN() {
	printf("Initialize..");

}

template<typename T>
T swap_endian(T u) {
	union {
		T u;
		unsigned char u8[sizeof(T)];
	} source, dest;

	source.u = u;

	for (size_t k = 0; k < sizeof(T); k++)
		dest.u8[k] = source.u8[sizeof(T) - k - 1];

	return dest.u;
}

void toCAN::setDebug(bool b){
	Bus.setDebug(b);
}

toCAN::~toCAN() {
	// TODO Auto-generated destructor stub
}
void toCAN::setMSG(unsigned char data[8], int lng) {
	for (int i = 0; i < lng; i++) {
		this->MSG[i] = data[i];
	}
}
void toCAN::setLNG(int l) {
	this->lng = l;

}

int toCAN::getLNG() {

	return this->lng;
}

unsigned char* toCAN::getMSG() {
	return this->MSG;
}



unsigned char* toCAN::getRecMSG() {
unsigned char *backM = new unsigned char[10];
for (int i = 0; i < 10; i++) {
	backM[i] = this->recMSG[i];
}
return backM;
}



void toCAN::setRecMSG(unsigned char msg[10]) {
for (int i = 0; i < 10; i++) {
	this->recMSG[i] = msg[i];
}
}
