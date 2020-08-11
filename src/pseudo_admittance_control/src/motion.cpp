
#include <moveit/move_group_interface/move_group_interface.h>
#include <ros/ros.h>
#include "geometry_msgs/Pose.h"



void forceCallback(const geometry_msgs::Pose::ConstPtr& target_pose)
{

  	static const std::string PLANNING_GROUP = "manipulator";
  	moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);


	geometry_msgs::Pose newPose = *target_pose;

	move_group.setPoseTarget(newPose);
	ROS_INFO("Pose %f is set", newPose.position.y);	
  	move_group.move(); 


}



int main(int argc, char** argv){

  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;
  ros::AsyncSpinner async_spinner(2);
  async_spinner.start();
  ros::Subscriber subForce = node_handle.subscribe("forceTopic",1000,forceCallback);
  ros::waitForShutdown();

  return 0;
}
