#include "IMUSensor.h"
#include "DrivingScenarios.h"
#include <thread>
#include <corecrt_math.h>
#include <locale>
#include <xlocale>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>

IMUSensor::IMUSensor()
{
 timeSensor = 0.0;
 distance = 0.0;
 currentSpeed = 0.0;
 isRunning = false;
 dt = 1.0;
}

void IMUSensor::calculateSpeed(DrivingScenarios& carpoint)
{   
    while (isRunning)
    {
        //// Simulated data from IMU sensor
        // accelerometerX = 1.2; // m/s^2 (change these values according to your data)
        // accelerometerY = 3.5; // m/s^2
        // accelerometerZ = 9.8; // m/s^2
        // g = 9.81;  // Acceleration due to gravity (approx. 9.81 m/s^2)
        //// Calculate speed based on sensor data (assuming constant acceleration)
        // Dataprocessing = sqrt(accelerometerX * accelerometerX + accelerometerY * accelerometerY + accelerometerZ * accelerometerZ);
        // // Calculate change in velocity using gyroscope data (assuming constant angular velocity)
        //// Sleep for a certain duration (simulating real-time data acquisition)
        // std::this_thread::sleep_for(std::chrono::milliseconds(500));
        // dt = timeSensor /dt;
        // // Estimate the current speed by integrating acceleration and change in velocity
        // currentSpeed = (Dataprocessing - g) * dt;
        // dv = currentSpeed / dv;
        // acceleration = dv / dt;
        // carpoint.SetaccelerationSpeed(acceleration);
         
        ifstream inputFile("data.txt"); // Open the text file for reading
        if (!inputFile.is_open())
        {
            cerr << "Error opening file." << endl;
          
        }

        string line;

        while (getline(inputFile, line))
        {
            istringstream iss(line);
            iss >> speedX >> speedY; // Extract speed X, speed Y, and time from the line
            speed = sqrt(speedX * speedX + speedY * speedY); // Calculate the total speed
            carpoint.SetcurrentSpeed(speed);
            distance += (speed * 1000 / 3600 * GettimeSensor()); // Calculate the total distance covered directly
            carpoint.Setdistance(distance);
            cout << "Distance covered in current iteration: " << distance << " meters" << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for 1 second between iterations
        }

        inputFile.close(); // Close the file
    //    cout << "Total distance covered: " << distance << " meters" << endl;
     
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




double IMUSensor::GettimeSensor()
{
    return this->timeSensor;
}

void IMUSensor::SettimeSensor(double second)
{
    this->timeSensor = second;
}
