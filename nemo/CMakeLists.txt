cmake_minimum_required(VERSION 2.8.3)
project(nemo)

 ## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp sensor_msgs std_msgs)


## Declare a catkin package
catkin_package()

install(DIRECTORY launch urdf stl rviz
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(nemoComander_node src/demo_nemoController.cpp)
target_link_libraries(nemoComander_node ${catkin_LIBRARIES})
