cmake_minimum_required(VERSION 2.8.3)
project(6DOF_Cartesian)

 ## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs)

## Declare a catkin package
catkin_package()

install(DIRECTORY launch urdf stl rviz
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

include_directories(include ${catkin_INCLUDE_DIRS})