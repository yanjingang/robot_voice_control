#! /bin/bash

### BEGIN INIT
gnome-terminal -- bash -c "source /opt/ros/melodic/setup.bash;source /home/wheeltec/wheeltec_robot/devel/setup.bash;roslaunch robot_voice_control base.launch"
sleep 10

gnome-terminal -- bash -c "source /opt/ros/melodic/setup.bash;source /home/wheeltec/wheeltec_robot/devel/setup.bash;roslaunch robot_voice_control mic_init.launch"

wait
exit 0
