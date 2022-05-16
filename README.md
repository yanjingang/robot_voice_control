# robot_voice_control

科大讯飞麦克风阵列+ROS 语音控制

配置和使用方法：https://blog.yanjingang.com/?p=5943


**1.下载离线语音SDK**

注册讯飞开放平台账号：打开讯飞开放平台网页,网址 https://www.xfyun.cn,注册账号。

创建新应用：选择控制台——我的应用——创建新应用——填好对应资料后提交。

下载Linux SDK：进入刚创建的应用,下载离线命令词识别 linux SDK（我这里使用的聚合SDK下载页生成的Linux平台SDK，同时包含了唤醒、识别、合成等库，下载后解压到~/linux_sdk备用）。


**2.配置麦克风阵列库**

//麦克风阵列库

cd ~/catkin_ws/src

git clone git@github.com:yanjingang/robot_voice_control.git

cd robot_voice_control


// 拷贝.so动态库

sudo cp lib/x64/*  /usr/lib/

//sudo cp lib/arm64/* /usr/lib/

// 替换APPID为上一部步自己注册的appid

vim config/appid_params.yaml

// 配置 udev 规则

sudo cp xf_mic.rules /etc/udev/rules.d/

sudo service udev restart

// 更新库里的科大迅飞离线语音SDK *.jet文件(这些文件内部与appid绑定了，必须同步替换)

cd ~/linux_sdk

cp bin/msc/res/asr/common.jet ~/catkin_ws/src/robot_voice_control/config/msc/res/asr/

cp -r bin/msc/res/tts bin/msc/res/ivw bin/msc/res/xtts  ~/catkin_ws/src/robot_voice_control/config/msc/res/


**3.安装声卡和语音播放库**

// 安装声卡驱动和语音库

sudo apt-get install libasound2-dev sox mplayer

// 插上麦克风USB口，检查设备是否正常识别

lsusb|grep 10d6:b003


**4.测试Linux SDK**

// 编译语音识别示例

cd ~/linux_sdk

cd samples/asr_offline_record_sample

sh 64bit_make.sh

// 运行测试

cd ~/linux_sdk/bin

./asr_offline_record_sample


**5.测试ROS库**

// 修改编译平台配置

vim ~/catkin_ws/src/robot_voice_control/CMakeLists.txt

  link_directories(

   lib/x64  

   // lib/arm64   

 )



// 编译

cd ~/catkin_ws

rm -rf build devel

catkin_make

source ~/catkin_ws/devel/setup.bash

// 开启语音控制底层、导航、雷达扫描节点

roslaunch robot_voice_control base.launch

// 开启麦克风阵列初始化节点（启动失败错误码说明：https://shimo.im/sheet/w3yUy39uNKs0J7DT）

roslaunch robot_voice_control mic_init.launch

// 调整声卡音量

alsamixer

// 通过“小猪小猪”唤醒



**6.重启lanuch测试**

通过“小猪去厨房”进行自定义位置点导航测试即可。


// 启动语音处理相关包

roslaunch robot_voice_control base.launch

// 启动麦克风阵列离线SDK主程序

roslaunch robot_voice_control mic_init.launch



// 启动底盘base control 

roslaunch ros_arduino_python arduino.launch

// 启动camera 

roslaunch robot_vslam camera.launch 


// 启动rtab并自动定位 

roslaunch robot_vslam rtabmap_rgbd.launch localization:=true

// 启动movebase（纯前向视觉无法后退） 

roslaunch robot_vslam move_base.launch planner:=dwa move_forward_only:=true



// pc端查看

roslaunch robot_vslam rtabmap_rviz.launch

// 语音控制“小猪去厨房”
