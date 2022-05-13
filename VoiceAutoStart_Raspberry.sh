#! /bin/bash

### BEGIN INIT
sleep 10

gnome-terminal -- bash -c "source /opt/ros/melodic/setup.bash;source /home/work/catkin_ws/devel/setup.bash;roslaunch robot_voice_control base.launch"

sleep 15

gnome-terminal -- bash -c "source /opt/ros/melodic/setup.bash;source /home/work/catkin_ws/devel/setup.bash;roslaunch robot_voice_control mic_init.launch"

wait
exit 0
