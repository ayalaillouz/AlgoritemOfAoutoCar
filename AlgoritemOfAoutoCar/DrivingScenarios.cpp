#include "DrivingScenarios.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
using namespace std;

DrivingScenarios::DrivingScenarios()
{
    currentSpeed = 0;
    secondTimer = 0;
    accelerationSpeed = 100 / 8.9; 
}
void DrivingScenarios::StartDriving()
{
   // Declare and initialize the static variable
    std::cout << "Timer started!" << std::endl;//delete
    std::thread t(timer, std::ref(secondTimer)); // Pass the static variable by reference
    std::cin.get(); // Wait for user input
    t.detach();
    std::cout << "Timer stopped!" << std::endl;
    std::cout << "Second variable value: " << secondTimer << std::endl; // Access the second variable
}

void DrivingScenarios::timer(int& seconds)
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        seconds++;
    }
}

void DrivingScenarios::SpeedCar(int maxSpeed)
{
    while (currentSpeed <= maxSpeed)
    {
        currentSpeed = currentSpeed + accelerationSpeed;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void DrivingScenarios::SlowdownCar(int MinSpeed)
{
    while (currentSpeed >= MinSpeed)
    {
        currentSpeed = currentSpeed - accelerationSpeed;
        std::this_thread::sleep_for(std::chrono::seconds(1));   
    }
  
   
}
int DrivingScenarios::DistanceFromCarToObject()
{
     str=ReadFromFile("Lidar.txt");
     temp = std::stoi(str);
     return temp;
}

std::string DrivingScenarios::SignalLight(string direction)
{
    return direction;
}


bool DrivingScenarios::Right(float distance)
{

    while (distance >= 0)
    {
        distance = distance - accelerationSpeed;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return true;
}

bool DrivingScenarios::Left(float distance)
{

    while (distance >= 0)
    {
        distance = distance - accelerationSpeed;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return true;
}

std::string  DrivingScenarios::WaitingForGreenLight(std::string direction)
{
    while (TrafficLightColor()!="Red")
    {
       std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return direction;
}

std::string DrivingScenarios::TrafficLightColor()
{

    str = ReadFromFile("TrafficLightColor.txt");
    return str;
}


std::string DrivingScenarios::ReadFromFile(string filepath)
{
    std::ifstream inputFile(filepath);  // Open the file for reading
    std::string fileContent;  // Variable to store the file content
    try {
        // Read the file content into a variableReadFromFile
        std::string line;
        while(inputFile.is_open())
        {
            std::getline(inputFile, line);
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







