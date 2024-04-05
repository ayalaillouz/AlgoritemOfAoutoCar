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
    double prevSpeed = 0.0,acceleration; // Initialize previous speed variable

    ifstream inputFile("data.txt"); // Open the text file for reading
    if (!inputFile.is_open())
    {
        cerr << "Error opening file." << endl;
    }

    string line;
    while (isRunning)
    {
        getline(inputFile, line);
    
        istringstream iss(line);
        iss >> speedX >> speedY; // Extract speed X, speed Y, and time from the line
        speed = sqrt(speedX * speedX + speedY * speedY); // Calculate the total speed

        acceleration = (speed - prevSpeed); // Calculate acceleration
        carpoint.SetaccelerationSpeed(acceleration);

        carpoint.SetcurrentSpeed(speed);
        distance += (speed * 1000 / 3600 * GettimeSensor()); // Calculate the total distance covered directly
        carpoint.Setdistance(distance);
        cout << "Distance covered in current iteration: " << distance << " meters" << endl;

        prevSpeed = speed; // Update previous speed to current speed
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for 1 second between iterations
    }

    inputFile.close(); // Close the file
    //    cout << "Total distance covered: " << distance << " meters" << endl;
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




int IMUSensor::GettimeSensor()
{
    return this->timeSensor;
}

void IMUSensor::SettimeSensor(int second)
{
    this->timeSensor = second;
}
