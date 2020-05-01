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

This example sketch demonstrates how to use the MPU-9250's
digital motion processor (DMP) to calibrate the gyroscope.
After eight seconds of no motion, the DMP will compute
gyro biases and subtract them.

*************************************************************/
#include <SparkFunMPU9250-DMP.h>

#ifdef defined(SAMD)
 #define SerialPort SerialUSB
#else
  #define SerialPort Serial
#endif

MPU9250_DMP imu;

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

  imu.setSensors(INV_XYZ_GYRO); // Enable gyroscope only
  imu.setGyroFSR(2000); // Set gyro to 2000 dps

  imu.dmpBegin(DMP_FEATURE_GYRO_CAL |   // Enable gyro cal
              DMP_FEATURE_SEND_CAL_GYRO,// Send cal'd gyro values
              10);                   // Set DMP rate to 10 Hz
}

void loop() 
{
  // Check for new data in the FIFO
  if ( imu.fifoAvailable() )
  {
    // Use dmpUpdateFifo to update the ax, gx, mx, etc. values
    if ( imu.dmpUpdateFifo() == INV_SUCCESS)
    {
      printIMUData();
    }
  }
}

void printIMUData(void)
{  
  // After calling dmpUpdateFifo() the ax, gx, mx, etc. values
  // are all updated.
  float gyroX = imu.calcGyro(imu.gx);
  float gyroY = imu.calcGyro(imu.gy);
  float gyroZ = imu.calcGyro(imu.gz);
  
  SerialPort.println("Gyro: " + String(gyroX) + ", " +
              String(gyroY) + ", " + String(gyroZ) + " dps");
  SerialPort.println("Time: " + String(imu.time) + " ms");
  SerialPort.println();
}

