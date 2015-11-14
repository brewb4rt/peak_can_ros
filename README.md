# peak_can_ros

This is a wrap for the PCAN API which can be found at http://www.peak-system.com/PCAN-Basic.239.0.html?&L=1&amp%3BL=1 .

Add your subscribers in toCAN.cpp (to get the Info from your system) and adjust the switch block in fromCAN to your Identifiers. My best practise is to create your CAN message as ROS message to loop through the information into the system.
