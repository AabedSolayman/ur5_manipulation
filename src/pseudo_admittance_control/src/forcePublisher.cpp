#include <ros/ros.h>
#include "geometry_msgs/Pose.h"

int main(int argc, char **argv)
{

	ros::init(argc, argv, "forcePublisher");

	ros::NodeHandle node_handle;

	ros::Publisher force_pub = node_handle.advertise<geometry_msgs::Pose>("forceTopic", 1000);
	ros::Rate loop_rate(0.05);

	geometry_msgs::Pose newPose;


	newPose.orientation.x = 0.50794;
	newPose.orientation.y = 0.49886;
	newPose.orientation.z = 0.49201;
	newPose.orientation.w = 0.50106;
	newPose.position.x = 0.81076;
	newPose.position.y = -0.3546;
	newPose.position.z = 0.3235;

	while (ros::ok())
	{

	ROS_INFO("I'm forcing the tool to move to %f", newPose.position.y);
	force_pub.publish(newPose);
	newPose.position.y += 0.05 ;

	ros::spinOnce();
    loop_rate.sleep();

	}

}