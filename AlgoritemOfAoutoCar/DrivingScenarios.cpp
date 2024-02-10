#include "DrivingScenarios.h"
#include "File.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <mutex>
using namespace std;

DrivingScenarios::DrivingScenarios()
{
    currentSpeed = 0.0;
    accelerationSpeed = 0.0; 
    temp = 0;
    PathOfSpeed = "./src/SpeedCar.txt";
}
void DrivingScenarios::SpeedCar(int maxSpeed = 120)
{
    std::lock_guard<std::mutex> lock(mtxPathOfSpeed);
    try
    {
        std::ifstream inputFile(GetPathOfSpeed()); // Open input file for reading
        std::ofstream outputFile("temp.txt", std::ios::trunc); // Create temporary output file
        while (GetcurrentSpeed() <= maxSpeed)
        {
            if (std::getline(inputFile, line))
            {
                int num = std::stoi(line); // Convert the line to integer
                num += accelerationSpeed; // Add 7 to the number read from the file
                outputFile << num << std::endl; // Write the modified number to the temporary file
            }
            // Copy the rest of the lines from input file to the output file
            outputFile << inputFile.rdbuf();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        inputFile.close();
        outputFile.close();
    }
    catch (const char* error) 
    {
        std::cerr << "Error openAndChange: " << error << std::endl;
    }

    try
    {
        std::rename("temp.txt", GetPathOfSpeed().c_str());
    }
    catch (const char* error)
    {
        std::cerr << "Error Rename: " << error << std::endl;
    }
}


void DrivingScenarios::SlowdownCar(int MinSpeed=0)
{
    std::lock_guard<std::mutex> lock(mtxPathOfSpeed);
    try
    {
        std::ifstream inputFile(GetPathOfSpeed()); // Open input file for reading
        std::ofstream outputFile("temp.txt", std::ios::trunc); // Create temporary output file
        while (GetcurrentSpeed()>= MinSpeed)
        {
            if (std::getline(inputFile, line))
            {
                int num = std::stoi(line); // Convert the line to integer
                num -= accelerationSpeed; // Add 7 to the number read from the file
                outputFile << num << std::endl; // Write the modified number to the temporary file
            }
            // Copy the rest of the lines from input file to the output file
            outputFile << inputFile.rdbuf();
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        inputFile.close();
        outputFile.close();
    }
    catch (const char* error)
    {
        std::cerr << "Error openAndChange: " << error << std::endl;
    }

    try
    {
        std::rename("temp.txt", GetPathOfSpeed().c_str());
    }
    catch (const char* error)
    {
        std::cerr << "Error Rename: " << error << std::endl;
    }
}

void DrivingScenarios::GreenLight()
{
    SpeedCar(MaxSpeed());
}

void DrivingScenarios::SpeedLimitSignFor80()
{
    std::thread slow(SlowdownCar,80);
    std::thread speed(SpeedCar, 80);
    slow.join();
    speed.join();
}

int DrivingScenarios::DistanceFromCarToObject()
{
     str=ReadFromFile("Lidar.txt");
     temp = std::stoi(str);
     return temp;
}

 void DrivingScenarios::RedLightStraight()
 {
    std::thread slowdown(SlowdownCar, 0);
    std::thread WaitGreen(WaitingForGreenLight);
    slowdown.join();
    WaitGreen.join();
    GreenLight();
}

 void DrivingScenarios::SettimeCar(double second)
 {
     std::lock_guard<std::mutex> lock(mtxTimeCar);
     timeCar = second;
 }

 double DrivingScenarios::GettimeCar()
 {
     std::lock_guard<std::mutex> lock(mtxTimeCar);
     return timeCar;
 }

 string DrivingScenarios::GetPathOfSpeed()
 {
     return PathOfSpeed;
 }

 double DrivingScenarios::GetaccelerationSpeed()
 {
     std::lock_guard<std::mutex> lock(mtxAccelerationSpeed);
     return accelerationSpeed;
 }

 double DrivingScenarios::GetcurrentSpeed()
 {
     std::lock_guard<std::mutex> lock(mtxCurrentSpeed);
     return currentSpeed;
 }

 void DrivingScenarios::SetcurrentSpeed(double speed)
 {
     std::lock_guard<std::mutex> lock(mtxCurrentSpeed);
     currentSpeed = speed;
 }

 void DrivingScenarios::SetaccelerationSpeed(double newaccelationspeed)
 {
     std::lock_guard<std::mutex> lock(mtxAccelerationSpeed);
     accelerationSpeed = newaccelationspeed;
 }
 
 void DrivingScenarios::RedLightRight()
 {
     std::thread slowdown(SlowdownCar, 0);
     std::thread Signal(SignalLight, "Right");
     std::thread WaitGreen(WaitingForGreenLight);
     slowdown.join();
     Signal.join();
     WaitGreen.join();
     temp = DistanceFromCarToObject();
     Right(temp);
 }
 void DrivingScenarios::RedLightLeft()
 {
     std::thread slowdown(SlowdownCar, 0);
     std::thread WaitGreen(WaitingForGreenLight);
     std::thread Signal(SignalLight, "Left");
     slowdown.join();
     WaitGreen.join();
     Signal.join();
     temp = DistanceFromCarToObject();
     Left(temp);
 }


void DrivingScenarios::SignalLight(string direction)
{
    signal= direction;
}

void DrivingScenarios::Stop()
{
    SlowdownCar();
}





void DrivingScenarios::Right(double distance)
{

    while (distance >= 0)
    {
        distance = distance - accelerationSpeed;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}

void DrivingScenarios::Left(double distance)
{

    while (distance >= 0.0)
    {
        distance = distance - accelerationSpeed;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void  DrivingScenarios::WaitingForGreenLight()
{
    while (TrafficLightColor()!="Red")
    {
       std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}

std::string DrivingScenarios::TrafficLightColor()
{

    str = ReadFromFile("../src/TrafficLightColor.txt");
    return str;
}


std::string DrivingScenarios::ReadFromFile(string filepath)
{
    std::ifstream inputFile(filepath);  // Open the file for reading
    std::string fileContent;  // Variable to store the file content
    std::string line;
    try {
        // Read the file content into a variableReadFromFile
        while(inputFile.is_open())
        {
            std::getline(inputFile,line);
            fileContent += line + "\n";
        }
        inputFile.close();  // Close the file after reading
    }
    catch (const char* error)
    {
        std::cout << "Error: " << error << std::endl;
    }
    return fileContent;
}

int DrivingScenarios::MaxSpeed()
{
    return 0;
}







