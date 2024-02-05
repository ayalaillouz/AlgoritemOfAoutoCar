#include "IMUSensor.h"
#include "DrivingScenarios.h"

void IMUSensor::calculateSpeed(DrivingScenarios& carpoint)
{
    while (isRunning) {
        // Simulated data from IMU sensor
         accelerometerX = 1.2; // m/s^2 (change these values according to your data)
         accelerometerY = 3.5; // m/s^2
         accelerometerZ = 9.8; // m/s^2
         gyroscopeX = 0.1;    // rad/s
         gyroscopeY = 0.3;    // rad/s
         gyroscopeZ = 0.2;    // rad/s

        // Calculate speed based on sensor data (assuming constant acceleration)
         acceleration = sqrt(accelerometerX * accelerometerX + accelerometerY * accelerometerY + accelerometerZ * accelerometerZ);
         currentSpeed = acceleration * time;
         carpoint.SetcurrentSpeed(currentSpeed);
        // Sleep for a certain duration (simulating real-time data acquisition)
         std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

void IMUSensor::startIMUSensor()
{
    isRunning = true;
    imuThread = std::thread(&IMUSensor::calculateSpeed, this);
}

void IMUSensor::stopIMUSensor()
{
    isRunning = false;
    imuThread.join();
}

double IMUSensor::getCurrentSpeed()
{
    return currentSpeed;
}

void IMUSensor::Settime(int second)
{
    time = second;
}
