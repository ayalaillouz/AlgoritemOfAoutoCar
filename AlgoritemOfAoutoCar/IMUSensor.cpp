#pragma once
#include <thread>
#include <corecrt_math.h>
#include <locale>
#include <xlocale>
#include <mutex>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#include "IMUSensor.h"
#include "DrivingScenarios.h"
using namespace std;
IMUSensor::IMUSensor()
{
 timeSensor = 0;
 distance = 0.0;
 currentSpeed = 0.0;
 isRunning = false;
 //dt = 1.0;

}


void IMUSensor::calculateSpeed(DrivingScenarios& carpoint)
{   
    double prevSpeed = 0.0,acceleration; // Initialize previous speed variable
    string line;
    while (isRunning)
    {
       ifstream inputFile("src/IMUsensor.txt"); // Open the text file for reading
       if (!inputFile.is_open())
       {
           cerr << "Error opening file." << endl;
       }
       getline(inputFile, line);
       
       istringstream iss(line);
       iss >> speedX >> speedY; // Extract speed X, speed Y, and time from the line
       speed = sqrt((speedX * speedX) +( speedY * speedY)); // Calculate the total speed
       
       acceleration = (speed - prevSpeed); // Calculate acceleration
       carpoint.SetaccelerationSpeed(acceleration);
       carpoint.SetcurrentSpeed(speed);
       distance += (speed * 1000 / 3600 * GettimeSensor()); // Calculate the total distance covered directly
       carpoint.Setdistance(distance);
       cout << "Distance covered in current iteration: " << distance << " meters" << endl;
       prevSpeed = speed; // Update previous speed to current speed
       inputFile.close(); // Close the file
       this_thread::sleep_for(chrono::seconds(1)); // Wait for 1 second between iterations
    } 
    //    cout << "Total distance covered: " << distance << " meters" << endl;
}


void IMUSensor::startIMUSensor(DrivingScenarios& carpoint)
{
    isRunning = true;
    imuThread = thread(&IMUSensor::calculateSpeed, carpoint);
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

//double IMUSensor::getdt()
//{
//    return dt;
//}




int IMUSensor::GettimeSensor()
{

    lock_guard<mutex> lock(mtxtimeSensor);
    return timeSensor;
}

void IMUSensor::SettimeSensor(int second)
{
    lock_guard<mutex> lock(mtxtimeSensor);
    timeSensor = second;
}
