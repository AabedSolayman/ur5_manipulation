# ur5_manipulation

ur5_manipulation is an interview task. The task requiers background in ROS, gazebo and robotics in general.

## The Task
Simulate and UR5 robot on ROS -Gazebo
1) Write a controller which provides joint angles as function of sine/ sine waves  and visualize it using Gazebo. 
2) Write a node which publish a linear force topic in X,Y,Z periodically. (choose 1 axis you like)
3) Write a controller (Pseudo-Admittance Control), which subscribes to the force topic which u published and move the end effector of the UR5 in your gazebo.
 
Hints: U can add Cartesian increments based on the Force you are publishing, so add the increments to your current Cartesian pose and do an inverse kinematics using KDL to get new joint angles and feed it to the gazebo. 

## Requirements
1) Gazebo
2) MoveIt

## Launch
Task 1
```
 roslaunch demo_moveit_config demo_planning_execution.launch
 roslaunch pseudo_admittance_control joint_manipulation.launch 
```

Task 2
```
 roslaunch demo_moveit_config demo_planning_execution.launch
 roslaunch pseudo_admittance_control motion.launch
```
