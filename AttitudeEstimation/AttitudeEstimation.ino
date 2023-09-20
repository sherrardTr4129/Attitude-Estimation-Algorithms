#include "Arduino_BHY2.h"
#include "Matrix/Matrix.hpp"
#include "Nicla_System.h"
#include "Quaternion/Quaternion.hpp"

// define a few macros to do unit conversion
#define EARTH_G_MSS 9.81
#define ACCEL_SENSITIVITY 4096 // LSB/g
#define GYRO_SENSITIVITY 16.4  // LSB/deg/sec
#define MAG_SENSITIVITY 16     // LSB/uT
#define ACC_TO_MSS(x)                                                          \
  (x * (EARTH_G_MSS / ACCEL_SENSITIVITY)) // convert from ADC reading to m/sec^s
#define GYRO_TO_DEG_SEC(x)                                                     \
  (x * (1.0 / GYRO_SENSITIVITY)) // convert from ADC reading to deg/sec
#define MAG_TO_uT(x)                                                           \
  (x * (1.0 / MAG_SENSITIVITY)) // convert from ADC reading to uT

// setup 9DOF sensor objects
SensorXYZ accelerometer(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);
SensorXYZ magnetometer(SENSOR_ID_MAG);

void setup() {
  BHY2.begin();
  Serial.begin(115200);

  // start sensor communication
  accelerometer.begin();
  gyro.begin();
  magnetometer.begin();
}

void loop() {
  // get new sensor readings
  BHY2.update();

  // pack sensor readings into arrays
  float accelerometer_readings[3][1] = {{ACC_TO_MSS(accelerometer.x())},
                                        {ACC_TO_MSS(accelerometer.y())},
                                        {ACC_TO_MSS(accelerometer.z())}};
  float gyro_readings[3][1] = {{GYRO_TO_DEG_SEC(gyro.x())},
                               {GYRO_TO_DEG_SEC(gyro.y())},
                               {GYRO_TO_DEG_SEC(gyro.z())}};
  float magnetometer_readings[3][1] = {{MAG_TO_uT(magnetometer.x())},
                                       {MAG_TO_uT(magnetometer.y())},
                                       {MAG_TO_uT(magnetometer.z())}};

  // construct matrix objects
  Matrix<float, 3, 1> acc_mat(accelerometer_readings);
  Matrix<float, 3, 1> gyro_mat(gyro_readings);
  Matrix<float, 3, 1> mag_mat(magnetometer_readings);
}
