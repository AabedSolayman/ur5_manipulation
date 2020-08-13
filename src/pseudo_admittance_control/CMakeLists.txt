cmake_minimum_required(VERSION 2.8.3)
project(pseudo_admittance_control)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages

find_package(catkin REQUIRED
  COMPONENTS
    moveit_core
    moveit_ros_planning
    moveit_ros_planning_interface
    pluginlib
    geometric_shapes
    rosbag
    tf2_ros
    tf2_eigen
    tf2_geometry_msgs
)


find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED system filesystem date_time thread)



###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
##  INCLUDE_DIRS include	
  LIBRARIES 
  CATKIN_DEPENDS
    moveit_core
    moveit_ros_planning_interface
    tf2_geometry_msgs
    roscpp
  DEPENDS
    EIGEN3
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIRS})


## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
 add_executable(${PROJECT_NAME}_endEffectorMover src/endEffectorMover.cpp)
 add_executable(${PROJECT_NAME}_jointAnglesProvider src/jointAnglesProvider.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(${PROJECT_NAME}_endEffectorMover ${catkin_LIBRARIES} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME}_jointAnglesProvider ${catkin_LIBRARIES} ${Boost_LIBRARIES})
#############
## Install ##
#############


## Mark executables for installation
## See http://docs.ros.org/melodic/api/catkin/html/howto/format1/building_executables.html
 install(TARGETS ${PROJECT_NAME}_endEffectorMover DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
## Mark cpp header files for installation
 install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

