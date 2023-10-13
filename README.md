# :rocket: Attitude Estimation Algorithms :airplane:
Various different attitude estimation algorithms implemented for the Nicla Sense Me board.

## Overview
This repository contains various attitude estimation algorithms, and a algorithm execution layer that can be used to run a selected algorithm. The algorithms themselves are implemented to be platform agnostic, so they can be used on other embedded system targets. The following attiude estimation algorithms have been implemented:

* Complementary Filter
* Madgwick Filter
* Mahony Filter

The algorithm used for estimation purpose can be selected through changing the enum value found in the ```SensorManager``` object constructor call in the ```AttitudeEstimation.ino``` file.

## Data Output Format 
The algorithm driver layer creates an instance of the selected attitude estimation class, and provides an interface to update the estimated attitude using measurements from an IMU sensor. The IMU provided on the Nicla Sense Me board has an internal MCU that runs an EKF state estimation algorithm in parrallel of whatever is implemented on the main MCU. This EKF result is treated as a "ground truth" for evaluating the algorithms implemented here. At each update step in the algorithm driver class, a JSON message is generated containing the ground truth quaternion and the newly estimated quaternion from the selected algorithm. An example JSON message can be seen below:

```bash
{"ground_truth_quat": {"w": 0.998838, "x": -0.017456, "y": -0.035095, "z": -0.026733},"estimated_quat": {"w": 0.959821,"x": -0.005751,"y": -0.037534,"z": 0.278033}}
```

## Visualization Tool
This data can be consumed and visualized by the visualization tool developed here. This tool will generate a 3D representation of the orientation of the sensor in space for the ground truth data, and the selected orientation algorithm data. To run the tool, run the following command:

```bash
python3 Visualizer.py "/dev/ttyACM0" 115200
```
**NOTE:** please change the *port* and *baud rate* values as needed for your system implementation. 

This should produce a window that looks something like this:

![Visualization](https://github.com/sherrardTr4129/AttitudeEstimation/blob/main/img/vizTool.png?raw=true)