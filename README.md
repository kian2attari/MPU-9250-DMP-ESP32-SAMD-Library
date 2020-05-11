MPU-9250 Digital Motion Processor (DMP) Arduino Library for ESP32 and SAMD boards
========================================

This library is based heavily on [Sparkfun's MPU9250 DMP Library](https://github.com/sparkfun/SparkFun_MPU-9250-DMP_Arduino_Library)

Advanced Arduino library for the Invensense MPU-9250 inertial measurement unit (IMU), which enables the sensor's digital motion processing (DMP) features. Along with configuring and reading from the accelerometer, gyroscope, and magnetometer, this library also supports the chip's DMP features like:

* Quaternion calculation
* Pedometer
* Gyroscope calibration
* Tap detection
* Orientation dtection



This library is intended to use the onboard DMP to offload the above calculations. 
If you're looking to bypass the DMP or are looking for something more straightforward, check out the [MPU-9250 Breakout Library by Sparkfun](https://github.com/sparkfun/SparkFun_MPU-9250_Breakout_Arduino_Library), which provides access to all standard MPU-9250 sensor-readings.
Keep in mind, those are designed to work with SAMD boards and will not work with an ESP32 board.

The following library was tested on a Adafruit Feather ESP32 Huzzah but it should work wonderfully with any ESP32 or SAMD based board.

## Note 

 Both the accelerometer and magnetometer could be calibrated for improved accuracy. You can follow [this tutorial]( https://thecavepearlproject.org/2015/05/22/calibrating-any-compass-or-accelerometer-for-arduino/) to complete the calibration!

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
	* **/src/util** - Source and headers for the MPU-9250 driver and dmp configuration. These are available and adapted from [Invensene's downloads page](https://www.invensense.com/developers/software-downloads/#sla_content_45).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 
* **/Processing** - An example processing sketch you can use to test the IMU!
