
/*
/clock
/gazebo/link_states
/gazebo/model_states
/gazebo/parameter_descriptions
/gazebo/parameter_updates
/gazebo/set_link_state
/gazebo/set_model_state
/gazebo_gui/parameter_descriptions
/gazebo_gui/parameter_updates
/rosout
/rosout_agg
/tf
/tf_static
/trybot/joint_1_position_controller/command
/trybot/joint_1_position_controller/pid/parameter_descriptions
/trybot/joint_1_position_controller/pid/parameter_updates
/trybot/joint_1_position_controller/state
/trybot/joint2_position_controller/command
/trybot/joint2_position_controller/pid/parameter_descriptions
/trybot/joint2_position_controller/pid/parameter_updates
/trybot/joint2_position_controller/state
/trybot/joint3_position_controller/command
/trybot/joint3_position_controller/pid/parameter_descriptions
/trybot/joint3_position_controller/pid/parameter_updates
/trybot/joint3_position_controller/state
/trybot/joint_states
*/

#include <stdio.h>
#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"

#define TOPIC "/trybot/joint_1_position_controller/command"

const char nodeName[] = "comander_node";
int main(int argc, char **argv)
{
  ros::init(argc, argv, nodeName);

  ros::NodeHandle nh;
  ros::Rate       rh(10);
  //ros::Publisher  pub = nh.advertise<sensor_msgs::JointState>(TOPIC, 10);
  ros::Publisher  pub = nh.advertise<std_msgs::Float64>(TOPIC, 10);

  std_msgs::Float64 sp;
  sp.data = 0.0;

	sleep(2);
  while(ros::ok())
  {
    sp.data += 0.005;
    if (0.9<sp.data) sp.data = 0.1;
    pub.publish(sp);

    ros::spinOnce();
    rh.sleep();
  }
  return 0;
}