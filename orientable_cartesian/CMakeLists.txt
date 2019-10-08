cmake_minimum_required(VERSION 2.8.3)
project(orientable_cartesian)

 ## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs)

## Declare a catkin package
catkin_package()

install(DIRECTORY launch urdf stl rviz
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(comander_node src/demo_Controller.cpp)
target_link_libraries(comander_node ${catkin_LIBRARIES})