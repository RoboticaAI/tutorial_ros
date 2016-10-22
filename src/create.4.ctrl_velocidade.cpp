#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "create_controle_velocidade");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  ros::Rate loop_rate(10);

  if (ros::ok())
  {
    	geometry_msgs::Twist msg;
	int i;

        ros::spinOnce();

	ROS_INFO("Pressione qualquer tecla para iniciar...");

	getchar();

	for(i=0;i<4;i++){
	
		msg.linear.x = 0.05;
		msg.angular.z = 0;
		pub.publish(msg);
    		ros::spin();
		sleep(5);

      		msg.linear.x = 0;
                msg.angular.z = 0.04;
                pub.publish(msg);
                ros::spin();
                sleep(8);
	}

        ROS_WARN("Quadrado finalizado...");
  }

  return 0;
}
