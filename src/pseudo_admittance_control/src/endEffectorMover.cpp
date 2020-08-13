
#include <moveit/move_group_interface/move_group_interface.h>
#include <ros/ros.h>
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"


class endEffectorTask {

private:
  ros::NodeHandle node_handle;
  ros::Subscriber subForce;
  geometry_msgs::Pose homePose_;


public:
  endEffectorTask(){

    //Creating a MoveGroup Interface with the planning group "manipulator"
    homePose_.orientation.x = 0.50794;
    homePose_.orientation.y = 0.49886;
    homePose_.orientation.z = 0.49201;
    homePose_.orientation.w = 0.50106;
    homePose_.position.x = 0.81076;
    homePose_.position.y = 0;
    homePose_.position.z = 0.3235;

    gotoPose(homePose_);

    subForce = node_handle.subscribe("force_applier", 1000, &endEffectorTask::forceCallback, this);

  }

  //forceCallback is responsible the moition of the robot
  void forceCallback(const geometry_msgs::Twist::ConstPtr& appliedForce)
  {
    moveit::planning_interface::MoveGroupInterface move_group("manipulator");
    // Get target pose
    geometry_msgs::Pose targetPose = getNewPose(move_group.getCurrentPose().pose,*appliedForce);

    // Go to new Pose
    gotoPose(targetPose);

  }
  
  //getNewPose gets the current pose and the applied force to it
  //getNewPose returns the calculated Pose
  geometry_msgs::Pose getNewPose(geometry_msgs::Pose current_pose, geometry_msgs::Twist force){

    current_pose.position.x += 0.05*force.linear.x;
    current_pose.position.y += 0.05*force.linear.y;
    current_pose.position.z += 0.05*force.linear.z;
    return current_pose;
  }

  void gotoPose(geometry_msgs::Pose target_pose){
    moveit::planning_interface::MoveGroupInterface move_group("manipulator");
    move_group.setPoseTarget(target_pose);
    move_group.move(); 
  }


};


int main(int argc, char** argv){

  ros::init(argc, argv, "endEffectorMover");

  ros::AsyncSpinner async_spinner(2);
  async_spinner.start();

  endEffectorTask letsPlay;

  ros::waitForShutdown();

  return 0;
}
