# dream-babbling-arduino-framework

This repository contains a basic class used to interface our babbling modules with our ROS supervisor.
You should install it in your Arduino libraries directory, most likely in 
```
~/Arduino/libraries
``` 
Also, don't forget to edit base_arduino_module.h at line 4 to point to your actual ros folder :
```
#include </home/florian/ros_catkin_ws/src/babbling_modules/include/babbling_modules/modules_defs.h>
```
