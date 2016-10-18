#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle_controle_velocidade");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

  ros::Rate loop_rate(10);

  if (ros::ok())
  {
    	geometry_msgs::Twist msg;
	int i;

        ros::spinOnce();

	ROS_INFO("Pressione qualquer tecla para iniciar...");
	system("rosservice call reset");

	getchar();

	for(i=0;i<4;i++){
	
		msg.linear.x = 2;
		msg.angular.z = 0;
		pub.publish(msg);
    		ros::spinOnce();
		sleep(1);

      		msg.linear.x = 0;
                msg.angular.z = M_PI/2;
                pub.publish(msg);
                ros::spinOnce();
                sleep(1);
	}

        ROS_WARN("Quadrado finalizado...");
  }

  return 0;
}
