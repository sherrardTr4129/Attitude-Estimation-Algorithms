#include "Arduino_BHY2.h"
#include "Matrix/Matrix.hpp"
#include "Nicla_System.h"
#include "Quaternion/Quaternion.hpp"
#include "Euler/Euler.hpp"
#include "SensorDriver/SensorDriver.hpp"
#include "EstimationAlgs/ComplementaryFilter/ComplementaryFilter.hpp"
#include "SensorDriver/SensorDriver.hpp"

// setup 9DOF sensor objects
SensorXYZ accelerometer(SENSOR_ID_ACC);
SensorXYZ gyro(SENSOR_ID_GYRO);
SensorXYZ magnetometer(SENSOR_ID_MAG);
SensorQuaternion quaternion(SENSOR_ID_RV);

// setup sensor manager object with selected filter
filters::SensorManager sensor_man(&accelerometer, &gyro, &magnetometer, &quaternion, filters::COMPLEMENTARY);

void setup() {
  BHY2.begin();
  Serial.begin(115200);

  // start sensor communication
  accelerometer.begin();
  gyro.begin();
  magnetometer.begin();
  quaternion.begin();
}

void loop() {
  sensor_man.run();
}
