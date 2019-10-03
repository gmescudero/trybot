#!/bin/bash

sudo killall rosmaster
sudo killall gzserver
sudo killall gzclient
#roslaunch trybot_gazebo trybot_world.launch
roslaunch trybot_gazebo trybot_gzcontrol.launch