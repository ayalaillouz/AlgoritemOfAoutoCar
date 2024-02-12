#include "IMUSensor.h"
#include "DrivingScenarios.h"
#include <thread>
#include <corecrt_math.h>
#include <locale>
#include <xlocale>

#include <corecrt_math.h>

IMUSensor::IMUSensor()
{
 timeSensor = 0.0;
 g = 9.81;  // Acceleration due to gravity (approx. 9.81 m/s^2)
 dt = 0.0;
 currentSpeed = 0.0;
 isRunning = false;
 dv = 0.0;
}

void IMUSensor::calculateSpeed(DrivingScenarios& carpoint)
{   
    while (isRunning)
    {
        // Simulated data from IMU sensor
         accelerometerX = 1.2; // m/s^2 (change these values according to your data)
         accelerometerY = 3.5; // m/s^2
         accelerometerZ = 9.8; // m/s^2
         g = 9.81;  // Acceleration due to gravity (approx. 9.81 m/s^2)
        // Calculate speed based on sensor data (assuming constant acceleration)
         Dataprocessing = sqrt(accelerometerX * accelerometerX + accelerometerY * accelerometerY + accelerometerZ * accelerometerZ);
         // Calculate change in velocity using gyroscope data (assuming constant angular velocity)
        // Sleep for a certain duration (simulating real-time data acquisition)
         std::this_thread::sleep_for(std::chrono::milliseconds(500));
         dt = timeSensor /dt;
         // Estimate the current speed by integrating acceleration and change in velocity
         currentSpeed = (Dataprocessing - g) * dt;
         dv = currentSpeed / dv;
         acceleration = dv / dt;
         carpoint.SetaccelerationSpeed(acceleration);
         carpoint.SetcurrentSpeed(currentSpeed);
    }
}

void IMUSensor::startIMUSensor(DrivingScenarios& carpoint)
{
    this->isRunning = true;
    imuThread = std::thread(&IMUSensor::calculateSpeed, carpoint);
}

void IMUSensor::stopIMUSensor()
{
    this->isRunning = false;
    imuThread.join();
}

double IMUSensor::getCurrentSpeed()
{
    return this->currentSpeed;
}

double IMUSensor::getdt()
{
    return this->dt;
}

double IMUSensor::getdv()
{
    return this->dv;
}

double IMUSensor::getacceleration()
{
    return acceleration;
}

double IMUSensor::GettimeSensor()
{
    return this->timeSensor;
}

void IMUSensor::SettimeSensor(double second)
{
    this->timeSensor = second;
}
