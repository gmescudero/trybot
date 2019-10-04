#include <stdio.h>
#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Float64.h"

#define TOPIC "/joints_set"
#define JOINTS_NUM 6
#define PI 3.141592

class Joint
{
public:
  std::string name;
  float max;
  float min;

  Joint(std::string na, float x,float n = 0.0):name(na),max(x),min(n){};
  ~Joint(){};
};

const char nodeName[] = "nemoComander_node";
int main(int argc, char **argv)
{
  ros::init(argc, argv, nodeName);

  ros::NodeHandle nh;
  ros::Rate       rh(5);
  ros::Publisher  pub = nh.advertise<sensor_msgs::JointState>(TOPIC, 10);
  //ros::Publisher  pub = nh.advertise<std_msgs::Float64>(TOPIC, 10);

  float j = 0.0;
 
  // Define all joints with its values
  Joint base_joint        ("base_joint",        PI,   0.0);
  Joint shoulder_joint    ("shoulder_joint",    2.88, 0.26);
  Joint elbow_joint       ("elbow_joint",       PI,   0.0);
  Joint wrist_pitch_joint ("wrist_pitch_joint", PI,   0.0);
  Joint wrist_roll_joint  ("wrist_roll_joint",  PI,   0.0);
  Joint gripper_joint     ("gripper_joint",     1.27, 0.17);

  // List all joints
  std::vector <Joint> nemoJoints;
  nemoJoints.push_back(base_joint);
  nemoJoints.push_back(shoulder_joint);
  nemoJoints.push_back(elbow_joint);
  nemoJoints.push_back(wrist_pitch_joint);
  nemoJoints.push_back(wrist_roll_joint);
  nemoJoints.push_back(gripper_joint);

  // Create and initialize ROS message
  sensor_msgs::JointState jointsMsg;
  jointsMsg.header.stamp = ros::Time::now();
  jointsMsg.header.frame_id.assign("jointSetPointScheduler");
  jointsMsg.position.clear();
  jointsMsg.position.clear();
  for(int i = 0; i < JOINTS_NUM; i++) 
  {
    jointsMsg.position.push_back(nemoJoints[i].min);
    jointsMsg.name.push_back(nemoJoints[i].name);
  }

  sleep(2);
  while(ros::ok())
  {
    // Joint values tracing
    std::cout << "Joints: " 
      << jointsMsg.position[0] << ", "
      << jointsMsg.position[1] << ", "
      << jointsMsg.position[2] << ", "
      << jointsMsg.position[3] << ", "
      << jointsMsg.position[4] << ", "
      << jointsMsg.position[5] << std::endl;
    pub.publish(jointsMsg);

    // Reset the message
    jointsMsg.position.clear();
    jointsMsg.header.stamp = ros::Time::now();

    // Sinusoidal movements for all joints
    for(int i = 0; i < JOINTS_NUM; i++)
    {
      jointsMsg.position.push_back((nemoJoints[i].max - nemoJoints[i].min)*0.5*(sin(j) + 1) + nemoJoints[i].min);    
    }


    // Increment the phase seed
    j += 0.1;

    // ROS callbacks and synchronization
    ros::spinOnce();
    rh.sleep();
  }
  return 0;
}