#include <stdio.h>
#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"

#define TOPIC "/jointSetpoint"

const char nodeName[] = "comander_node";
int main(int argc, char **argv)
{
  ros::init(argc, argv, nodeName);

  ros::NodeHandle nh;
  ros::Rate       rh(5);
  ros::Publisher  pub = nh.advertise<sensor_msgs::JointState>(TOPIC, 10);
  //ros::Publisher  pub = nh.advertise<std_msgs::Float64>(TOPIC, 10);

  float j = 0.0;

  sensor_msgs::JointState joints;
  joints.header.stamp = ros::Time::now();
  joints.header.frame_id.assign("jointSetPointScheduler");
  joints.position.clear();
  joints.position.push_back(0.0);
  joints.position.push_back(0.0);
  joints.position.push_back(0.0);
  joints.name.clear();
  joints.name.push_back("joint1");
  joints.name.push_back("joint2");
  joints.name.push_back("joint3");

  sleep(2);
  while(ros::ok())
  {
    std::cout << "Joints: " 
      << joints.position[0] << ", "
      << joints.position[1] << ", "
      << joints.position[2] << std::endl;
    pub.publish(joints);

    joints.position.clear();
    joints.header.stamp = ros::Time::now();

    joints.position.push_back(0.45*sin(j));
    joints.position.push_back(0.45*sin(j));
    joints.position.push_back(0.45*sin(j));

    j += 0.1;

    ros::spinOnce();
    rh.sleep();
  }
  return 0;
}