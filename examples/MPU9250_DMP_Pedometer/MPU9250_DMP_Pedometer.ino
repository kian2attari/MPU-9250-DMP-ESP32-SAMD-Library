/************************************************************
A library for reading data from the MPU9250 using its on board DMP (Digital
Motion Processor) to offload quaternion calculation, step-counting, and 
orientation-determining off to the IMU.

This code was tested on an Adafruit ESP32 Feather Huzzah but it should work 
for any ESP32 based device out there.

This code was based on the Sparkfun MPU9250 Library by:
Jim Lindblom @ SparkFun Electronics
original creation date: November 23, 2016
https://github.com/sparkfun/SparkFun_MPU9250_DMP_Arduino_Library

The library was designed to work with SAMD boards and so it had
to be modified to work with ESP32 devices. This library works for both
After uploading the code, try shaking the 9DoF up and
down at a "stepping speed."
*************************************************************/
#include <SparkFunMPU9250-DMP.h>

#ifdef defined(SAMD)
 #define SerialPort SerialUSB
#else
  #define SerialPort Serial
#endif

MPU9250_DMP imu;

unsigned long stepCount = 0;
unsigned long stepTime = 0;
unsigned long lastStepCount = 0;

void setup() 
{
  SerialPort.begin(115200);

  // Call imu.begin() to verify communication and initialize
  if (imu.begin() != INV_SUCCESS)
  {
    while (1)
    {
      SerialPort.println("Unable to communicate with MPU-9250");
      SerialPort.println("Check connections, and try again.");
      SerialPort.println();
      delay(5000);
    }
  }
  
  imu.dmpBegin(DMP_FEATURE_PEDOMETER);
  imu.dmpSetPedometerSteps(stepCount);
  imu.dmpSetPedometerTime(stepTime);
}

void loop() 
{
  stepCount = imu.dmpGetPedometerSteps();
  stepTime = imu.dmpGetPedometerTime();
  
  if (stepCount != lastStepCount)
  {
    lastStepCount = stepCount;
    SerialPort.print("Walked " + String(stepCount) + 
                     " steps");
    SerialPort.println(" (" + 
              String((float)stepTime / 1000.0) + " s)");
  }
}

