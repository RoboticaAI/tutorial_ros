#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <iostream>
#include <math.h>

using namespace std;

turtlesim::Pose feedback;

void subCallback(const turtlesim::Pose::ConstPtr& msg)
{
	feedback.x = msg->x;
	feedback.y = msg->y;
	feedback.theta = msg->theta;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "create_controle_posicao");

  ros::NodeHandle n;
  ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
  ros::Subscriber sub = n.subscribe("/pose", 1000, subCallback);

  ros::Rate loop_rate(10);

  if (ros::ok())
  {
    geometry_msgs::Twist msg;
    float posdesejada[2], oridesejada, dist=99, erroorie=99;
    float tolerance_orie = 0.005, tolerance_pos = 0.05;
    float Kpos = 10, Korie = 15;
    float angulo;

    system("rqt_plot /pose/x:y &");

    cout << "Digite a posicao\nX>>";
    cin >> posdesejada[0];

    cout << "Y>>";
    cin >> posdesejada[1];

    ros::spinOnce();


    angulo = atan2(posdesejada[1]-feedback.y,posdesejada[0]-feedback.x); 
    ROS_WARN("angulo>>%f\n",angulo);

    // Controle da orientacao
 	while (abs(erroorie) > tolerance_orie) {

        	erroorie = angulo-feedback.theta;

        	msg.angular.z = Korie*erroorie/(60/10);

       		if (msg.angular.z > 0.5)
                	msg.angular.z = 0.5;
        	if (msg.angular.z < -0.5)
                	msg.angular.z = -0.5;


         	ROS_INFO("theta>>%f,Erro>>%f",feedback.theta,erroorie);

        	pub.publish(msg);

        	ros::spinOnce();

        	loop_rate.sleep();
	}
 	msg.angular.z = 0;
  	pub.publish(msg);
	ros::spinOnce();
	ROS_WARN("...Orientacao alcancada...");


    //Controle de posicao
    	while (dist > tolerance_pos){
	
        	dist =  sqrt(pow(posdesejada[0]-feedback.x,2)+pow(posdesejada[1]-feedback.y,2));

		msg.linear.x = abs(Kpos*(dist) /(60/10));


        	if (msg.linear.x > 0.05)
                	msg.linear.x = 0.05;
       	 	if (msg.linear.x < -0.05)
                	msg.linear.x = -0.05;


  	 	ROS_INFO("Dist>>%f",dist);

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
