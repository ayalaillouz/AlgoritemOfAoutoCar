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
 dt = 1.0;
}


void IMUSensor::calculateSpeed(DrivingScenarios& carpoint)
{
    double prevSpeed = 0.0, acceleration; // Initialize previous speed variable
    string line;
    string filepath = "C:/Users/USER/Documents/פרוייקט/AlgoritemOfAoutoCar/src/IMUsensor.txt";

    while (isRunning)
    {

        ifstream inputFile(filepath); // Open the text file for reading
        if (!inputFile.is_open())
        {
            cerr << "Error opening file IMU in IMU" << endl;
        }

        if (getline(inputFile, line)) // Read a line from the file
        {
            istringstream iss(line);
            iss >> speedX >> speedY; // Extract speed X, speed Y, and time from the line
            speed = sqrt((speedX * speedX) + (speedY * speedY)); // Calculate the total speed
            acceleration = (speed - prevSpeed) / dt; // Calculate acceleration
            print("acceleration: " + to_string(acceleration));
            print("speed: " + to_string(speed));
            carpoint.SetaccelerationSpeed(acceleration);
            carpoint.SetcurrentSpeed(speed);
            distance = (speed * 1000 / 3600 * GettimeSensor()); // 1000=1 k"m, 3600 secoend=1 hour
            carpoint.Setdistance(distance);
            print("Distance covered in current iteration: " + to_string(carpoint.Getdistance()) + " meters");
            prevSpeed = speed; // Update previous speed to current speed
            inputFile.close(); // Close the file

            // Reopen the file in write mode to remove the first line
            ofstream tempFile("C:/Users/USER/Documents/פרוייקט/AlgoritemOfAoutoCar/src/IMUsensorTemp.txt");
            ifstream inputFile2("C:/Users/USER/Documents/פרוייקט/AlgoritemOfAoutoCar/src/IMUsensor.txt"); // Reopen the original file for reading

            // Skip the first line
            if (inputFile2.good() && tempFile.good()) 
            {
                getline(inputFile2, line); // Skip the first line


                // Copy the remaining lines to the temporary file
                while (getline(inputFile2, line))
                {
                    tempFile << line << endl;
                }

                tempFile.close();
                inputFile2.close();

                // Delete the original file
                remove("C:/Users/USER/Documents/פרוייקט/AlgoritemOfAoutoCar/src/IMUsensor.txt");

                // Rename the temporary file to the original filename
                rename("C:/Users/USER/Documents/פרוייקט/AlgoritemOfAoutoCar/src/IMUsensorTemp.txt", "C:/Users/USER/Documents/פרוייקט/AlgoritemOfAoutoCar/src/IMUsensor.txt");
            }
        }
         this_thread::sleep_for(chrono::seconds(1)); // Wait for 1 second between iterations
    }
}

void IMUSensor::startIMUSensor(DrivingScenarios& carpoint)
{
    isRunning = true;
    calculateSpeed(carpoint);
}

void IMUSensor::stopIMUSensor()
{
    isRunning = false;
   
}

double IMUSensor::getCurrentSpeed()
{
    return currentSpeed;
}

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

void IMUSensor::print(const std::string& message)
{
    std::lock_guard<std::mutex> lock(mtxprint);
    std::cout << message << std::endl;
}
