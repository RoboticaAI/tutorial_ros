#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include "kbhit.h"
using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "turtle_sim_teleop");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1000);

  ros::Rate loop_rate(10);

  geometry_msgs::Twist msg;
  
  char tecla;

  while (ros::ok() && tecla != 'q')
  {
    if (kbhit())
    	//cin >> tecla;
        tecla = getchar();

   if (tecla == 'w'){
	msg.linear.x = 0.5;
	msg.angular.z = 0;
	ROS_INFO("Frente\n");
	}
   if (tecla == 's'){
        msg.linear.x = -0.5;
	msg.angular.z = 0;
	ROS_INFO("Traz\n");
	}
   if (tecla == 'a'){
        msg.angular.z = 0.5;
        ROS_INFO("Esquerda\n");
        }
   if (tecla == 'd'){
        msg.angular.z = -0.5;
        ROS_INFO("Direita\n");
        }
  if (tecla == 'q'){
	msg.linear.x = 0;
        msg.angular.z = 0;
        ROS_INFO("Parado\n");
        }


    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();

  }

  return 0;
}
