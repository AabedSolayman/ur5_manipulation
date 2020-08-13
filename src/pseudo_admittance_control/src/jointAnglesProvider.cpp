
#include <moveit/move_group_interface/move_group_interface.h>
#include <ros/ros.h>
#include "geometry_msgs/Pose.h"
#include "math.h"



// get the parameteres from the parametere server and assign them to the new joint values
std::vector<double> getJointValuesParameters(std::vector<double> joint_values){

  for(int jointCounter=0;jointCounter<joint_values.size();jointCounter++){

    if((joint_values[jointCounter]>=0 && joint_values[jointCounter]<M_PI)||joint_values[jointCounter]<0)
    joint_values[jointCounter]+=0.1;

    else if((joint_values[jointCounter]<0 && joint_values[jointCounter]>-M_PI)||joint_values[jointCounter]>M_PI)
    joint_values[jointCounter]-=0.1;

    std::cout<<"Joint" << jointCounter <<"has the value " << joint_values[jointCounter]<<std::endl;

  }

  return joint_values;
}


int main(int argc, char** argv){

  ros::init(argc, argv, "jointManipulator");
  ros::NodeHandle node_handle;
  ros::Rate loop_rate(0.1);
  std::vector<double> joints_values;
  std::vector<double> target_joints_values;

  ros::AsyncSpinner async_spinner(2);
  async_spinner.start();

  static const std::string PLANNING_GROUP = "manipulator";
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP);
  geometry_msgs::Pose homePose_;
      //Creating a MoveGroup Interface with the planning group "manipulator"
    homePose_.orientation.x = 0.50794;
    homePose_.orientation.y = 0.49886;
    homePose_.orientation.z = 0.49201;
    homePose_.orientation.w = 0.50106;
    homePose_.position.x = 0.81076;
    homePose_.position.y = 0;
    homePose_.position.z = 0.3235;
    //moveit::planning_interface::MoveGroupInterface move_group("manipulator");
    move_group.setPoseTarget(homePose_);
    move_group.move();
  const robot_state::JointModelGroup* joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  while(ros::ok()){
    moveit::core::RobotStatePtr current_state = move_group.getCurrentState();
    current_state->copyJointGroupPositions(joint_model_group, joints_values);

    target_joints_values = getJointValuesParameters(joints_values);


    move_group.setJointValueTarget(target_joints_values);
    move_group.move(); 
    loop_rate.sleep();

  }
  ros::waitForShutdown();
  return 0;
}


