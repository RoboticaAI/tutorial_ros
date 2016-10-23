#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include "../kbhit.h"
using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "create_teleoperacao_teclado");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  ros::Rate loop_rate(10);

  geometry_msgs::Twist msg;
  
  char tecla;

 if(ros::ok()) 
 {
	
   for (int y=0;y<4;y++){

	ROS_INFO("Frente");
	for (int i=0;i<50;i++){
	  msg.linear.x = 0.05;
          msg.angular.z = 0;
	  pub.publish(msg);
    	  ros::spinOnce();
    	  loop_rate.sleep();
	}

        ROS_INFO("Girar");
        for (int i=0;i<33;i++){
          msg.linear.x = 0;
          msg.angular.z = 0.5;
          pub.publish(msg);
          ros::spinOnce();
          loop_rate.sleep();
        }

  }
  ROS_INFO("Parar");
  msg.linear.x = 0.00;
  msg.angular.z = 0;
  pub.publish(msg);
  ros::spinOnce();

  }

  return 0;
}
