#pragma once

#include "../Quaternion/Quaternion.hpp"
#include "../Matrix/Matrix.hpp"
#include "Nicla_System.h"

// define a few macros to do unit conversion
#define EARTH_G_MSS 9.81
#define ACCEL_SENSITIVITY 4096 // LSB/g
#define GYRO_SENSITIVITY 16.4  // LSB/deg/sec
#define MAG_SENSITIVITY 16     // LSB/uT
#define DEG_SEC_TO_RAD_SEC(x) (x * 0.017453292519943) // convert from deg/sec to rad/sec
#define ACC_TO_MSS(x)                                                          \
  (x * (EARTH_G_MSS / ACCEL_SENSITIVITY)) // convert from ADC reading to m/sec^s
#define GYRO_TO_DEG_SEC(x)                                                     \
  (x * (1.0 / GYRO_SENSITIVITY)) // convert from ADC reading to deg/sec
#define MAG_TO_uT(x)                                                           \
  (x * (1.0 / MAG_SENSITIVITY)) // convert from ADC reading to uT

namespace filters {
class SensorDriver {
    virtual structures::Quaternion<double> update(structures::Matrix<double, 3, 1> acc_mat,
                                                  structures::Matrix<double, 3, 1> gyro_mat,
                                                  structures::Matrix<double, 3, 1> mat_mat) = 0;
}; // end SensorDriver class

class SensorManager {
public:
    SensorManager(SensorXYZ *accelerometer, SensorXYZ *gyro, 
                  SensorXYZ *magnetometer, SensorQuaternion *quaternion);
private:
    SensorDriver *_sensor_driver;

};
} // end filters namespace

