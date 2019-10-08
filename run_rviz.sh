#!/bin/sh

helpFunction()
{
    echo "This script automatically launches rviz visualizer for a given robot"
    echo "Usage: $0 [<robot>]"
    echo "Available robots:"
    echo "\t-t trybot: 3DOF cartesian rviz simulation"
    echo "\t-n nemo: launches the braccio rviz simulation"
    echo "\t-c 6DOFCartesian: 6DOF cartesian rviz simulation (WIP)"
    echo "\t-h help: print this info"
    exit 1
}


if [ $# = 0 ]; then helpFunction; fi

while getopts "tnch" opt; do
    case $opt in
        t) # Trybot
            echo "Launching trybot simulation"
            roslaunch trybot_description trybot_rviz.launch
            ;;
        n) # Nemo
            echo "Launching nemo simulation"
            roslaunch nemo nemo_rviz.launch
            ;;
        c) # Cartesian
            echo "Launching cartesian simulation (WIP)"
            roslaunch orientable_cartesian orientable_cartesian_rviz.launch
            ;;
        h) helpFunction ;; #Print help
        ?) helpFunction ;; #Print help
    esac
done
