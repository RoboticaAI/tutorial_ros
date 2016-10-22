#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include "kbhit.h"
using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "create_teleoperacao_teclado");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);

  ros::Rate loop_rate(10);

  geometry_msgs::Twist msg;
  
  char tecla;

  while (ros::ok() && tecla != 'q')
  {
    if (kbhit())
        tecla = getchar();

   if (tecla == 'w'){
	msg.linear.x = 0.04;
	msg.angular.z = 0;
	ROS_INFO("Frente");
	}
   if (tecla == 's'){
        msg.linear.x = -0.04;
	msg.angular.z = 0;
	ROS_INFO("Traz");
	}
   if (tecla == 'a'){
        msg.angular.z = 0.4;
        ROS_INFO("Esquerda");
        }
   if (tecla == 'd'){
        msg.angular.z = -0.4;
        ROS_INFO("Direita");
        }
  if (tecla == 'q'){
	msg.linear.x = 0;
        msg.angular.z = 0;
        ROS_INFO("Parado");
        }


    pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();

  }

  return 0;
}
