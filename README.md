videoDelayLine
==============

Simple Video Delay Line using openFrameworks library and boost circular buffer. 

Requires openFrameworks AND boost/circular_buffer. Repository includes Visual Studio 2017 project files and XCode 8.2.1 project files

OSX
---

* Check out https://github.com/danoli3/ofxOSXBoost to your openFrameworks addon directory.
* Change the following line in your CoreOF.xconfig file:

`//HEADER_BOOST = "$(OF_PATH)/libs/boost/include"`

`HEADER_BOOST = "$(OF_PATH)/addons/ofxOSXBoost/libs/boost/include"`


WINDOWS
-------

* Download boost 
* Build it following instructions (I just had to do ./bootstrap.bat and ./b2) (it will take a LOT of time to build)
* substitute OF_ROOT/libs/boost/include and OF_ROOT/libs/boost/lib with the full version of boost that you downloaded and compiled. 
