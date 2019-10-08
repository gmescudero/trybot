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

const char nodeName[] = "demoComander_node";
int main(int argc, char **argv)
{
  ros::init(argc, argv, nodeName);

  ros::NodeHandle nh;
  ros::Rate       rh(5);
  ros::Publisher  pub = nh.advertise<sensor_msgs::JointState>(TOPIC, 10);
  //ros::Publisher  pub = nh.advertise<std_msgs::Float64>(TOPIC, 10);

  float j = 0.0;
 
  // Define all joints with its values
  Joint joint0 ("cartesian_z",       0.45, -0.45);
  Joint joint1 ("cartesian_x",       0.45, -0.45);
  Joint joint2 ("cartesian_y",       0.45, -0.45);
  Joint joint3 ("orientation_yaw",   PI,   -PI);
  Joint joint4 ("orientation_pitch", PI/2, -PI/2);
  Joint joint5 ("orientation_roll",  PI,   -PI);

  // List all joints
  std::vector <Joint> jointsArray;
  jointsArray.push_back(joint0);
  jointsArray.push_back(joint1);
  jointsArray.push_back(joint2);
  jointsArray.push_back(joint3);
  jointsArray.push_back(joint4);
  jointsArray.push_back(joint5);

  // Create and initialize ROS message
  sensor_msgs::JointState jointsMsg;
  jointsMsg.header.stamp = ros::Time::now();
  jointsMsg.header.frame_id.assign("jointSetPointScheduler");
  jointsMsg.position.clear();
  jointsMsg.position.clear();
  for(int i = 0; i < JOINTS_NUM; i++) 
  {
    jointsMsg.position.push_back(jointsArray[i].min);
    jointsMsg.name.push_back(jointsArray[i].name);
  }

  sleep(2);
  while(ros::ok())
  {
    // Joint values tracing
    std::cout << "Joints: ";
    for (int i = 0; i < jointsMsg.position.size(); i++)
      std::cout << jointsMsg.position[i] << ", ";
    std::cout << std::endl;

    pub.publish(jointsMsg);

    // Reset the message
    jointsMsg.position.clear();
    jointsMsg.header.stamp = ros::Time::now();

    // Sinusoidal movements for all joints
    for(int i = 0; i < JOINTS_NUM; i++)
    {
      jointsMsg.position.push_back((jointsArray[i].max - jointsArray[i].min)*0.5*(sin(j) + 1) + jointsArray[i].min);    
    }


    // Increment the phase seed
    j += 0.1;

    // ROS callbacks and synchronization
    ros::spinOnce();
    rh.sleep();
  }
  return 0;
}