
#include <ros/ros.h>
#include <signal.h>
#include <robot_voice_control/Set_Major_Mic_srv.h>
#include <string.h>
#include <cmath>
#include <iostream>
#include <std_msgs/Int32.h>
#include <std_msgs/Int8.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>



int main(int argc, char** argv)
{

	ros::init(argc, argv, "test");    

	ros::NodeHandle nha;    

	int i =0 ;
	
	ros::ServiceClient Set_Major_Mic_client = nha.serviceClient<robot_voice_control::Set_Major_Mic_srv>("voice_control/set_major_mic_srv");
	
	double rate2 = 0.1;    
	ros::Rate loopRate2(rate2);

	while(ros::ok())
	{
		if(i < 6)
			i++;
		else 
			i = 0;
			
		robot_voice_control::Set_Major_Mic_srv num;
		num.request.mic_id = i;
		Set_Major_Mic_client.call(num);

		ros::spinOnce();
		loopRate2.sleep();    

		//ros::spin();     
	}
	return 0;

}

