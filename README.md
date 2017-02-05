videoDelayLine
==============

Simple Video Delay Line using openFrameworks library and boost circular buffer. 

Requires boost/circular_buffer. Repository includes Visual Studio 2012 project files and XCode 8.2.1 project files

OSX
---

* Check out https://github.com/danoli3/ofxOSXBoost to your openFrameworks addon directory.
* Change the following line in your CoreOF.xconfig file:

`//HEADER_BOOST = "$(OF_PATH)/libs/boost/include"`

`HEADER_BOOST = "$(OF_PATH)/addons/ofxOSXBoost/libs/boost/include"`
