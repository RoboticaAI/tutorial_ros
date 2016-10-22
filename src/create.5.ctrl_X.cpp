#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
using namespace std;

turtlesim::Pose feedback;

void subCallback(const turtlesim::Pose::ConstPtr& msg)
{
	feedback.x = msg->x;
	feedback.y = msg->y;
	feedback.theta = msg->theta;
	feedback.linear_velocity = msg->linear_velocity;
	feedback.angular_velocity = msg->angular_velocity; 
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "create_controle_X");

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::Subscriber sub = n.subscribe("/pose", 1000, subCallback);

  ros::Rate loop_rate(10);

  system("rqt_plot /pose/x &");

  if (ros::ok())
  {
    geometry_msgs::Twist msg;
    float desejado, erro=99;
    float tolerance = 0.01;
    float Kpos = 10;

    cout << "Digite a posicao\nX>>";
    cin >> desejado;

    ros::spinOnce();

    while (abs(erro) > tolerance) {
	
	erro = desejado-feedback.x;

	msg.linear.x = Kpos*erro/(60/10);

	if (msg.linear.x > 0.05)
		msg.linear.x = 0.05;
	if (msg.linear.x < -0.05)
		msg.linear.x = -0.05;


  	 ROS_INFO("X>>%f,Erro>>%f",feedback.x,erro);

    	pub.publish(msg);

    	ros::spinOnce();

    	loop_rate.sleep();

	}
        ROS_WARN("...Posicao alcancada...");
  }

	sleep(1);
	system("killall rqt_plot");

  return 0;
}
