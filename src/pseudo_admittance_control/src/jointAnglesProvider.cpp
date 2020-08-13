
#include <moveit/move_group_interface/move_group_interface.h>
#include <ros/ros.h>
#include "geometry_msgs/Pose.h"
#include "math.h"



std::vector<double> getJointValuesParameters(std::vector<double> joint_values, double increment){

  for(int jointCounter=0;jointCounter<joint_values.size();jointCounter++)
    
    joint_values[jointCounter] = 2.45*sin(increment);

  std::cout<<"Joints " << " have the value " << joint_values[0]<<std::endl;

  return joint_values;
}


int main(int argc, char** argv){

  ros::init(argc, argv, "jointManipulator");
  ros::NodeHandle node_handle;

  std::vector<double> joints_values;
  std::vector<double> target_joints_values;
  double increment =0;

  ros::AsyncSpinner async_spinner(2);
  async_spinner.start();

  static const std::string PLANNING_GROUP = "manipulator";
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);

  const robot_state::JointModelGroup* joint_model_group =
  move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  moveit::core::RobotStatePtr current_state = move_group.getCurrentState();
  current_state->copyJointGroupPositions(joint_model_group, joints_values);

  while(ros::ok()){

    target_joints_values = getJointValuesParameters(joints_values,increment);

    move_group.setJointValueTarget(target_joints_values);

    move_group.move();

    increment+=0.01; 

  }
  
  ros::waitForShutdown();
  return 0;
}


