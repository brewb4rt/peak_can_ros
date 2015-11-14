/**
 * @file driveCAN.cpp
 * @author Danny Behnecke
 */

#include "fromCAN.h"

int main(int argc, char **argv) {
	ros::init(argc, argv, "Can_Comm");
	toCAN toCanHandle;
	ros::NodeHandle n;
    canDongle::example ex;


    ros::Publisher examplePUb = n.advertise<canDongle::example>("exTopic",100);





	while (ros::ok()) {

		bool can_open = toCanHandle.Bus.listen();
		if (can_open == false) {
			//ROS_INFO("can_open==false");
		}

		int msgID = (int) toCanHandle.Bus.getRecMSG().ID;
		int msgLn = (int) toCanHandle.Bus.getRecMSG().LEN;


		if (msgLn) {


			switch (msgID) {

			case 0x100:

                    ex.info = toCanHandle.Bus.getRecMSG().DATA[0];
                    ex.value = toCanHandle.Bus.getRecMSG().DATA[0]+ toCanHandle.Bus.getRecMSG().DATA[1]>>8;


			default:

				break;

			}
		}

		ros::spinOnce();
	}
	return 0;
}
