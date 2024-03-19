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
#include <vector>
#include <cmath>
#include <limits>
using namespace std;

DrivingScenarios::DrivingScenarios()
{
    currentSpeed = 0.0;
    accelerationSpeed = 0.0; 
    temp = 0;
    PathOfSpeed = "./src/SpeedCar.txt";
}


double DrivingScenarios::DistanceFromCarToObject(std::string filename)
{
    //Reads a row of values from a file, and returns the minimum value
    std::ifstream file(filename);
    double minVal = std::numeric_limits<double>::max();//Initialize to the maximum value

    if (file.is_open())
    {
        std::string line;
        if (std::getline(file, line))
        {
            std::istringstream iss(line);
            double value;

            while (iss >> value)
            {
                if (value < minVal)
                {
                    minVal = value;
                }
            }

            // Remove the line from the file
            std::vector<std::string> remainingLines;
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    remainingLines.push_back(line);
                }
            }

            file.close();

            std::ofstream outFile(filename, std::ios::out | std::ios::trunc);
            for (const auto& l : remainingLines) {
                outFile << l << std::endl;
            }
            outFile.close();
        }
        else {
            std::cerr << "Error: File is empty." << std::endl;
            file.close();
            return -1.0; // Return -1 to indicate error
        }
    }
    else {
        std::cerr << "Error: Unable to open file." << std::endl;
        return -1.0; // Return -1 to indicate error
    }
    return minVal;
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
 void DrivingScenarios::RedLightStraight()
 {
     SlowdownCar();
     WaitingForGreenLight();
     GreenLight();
     direction = "Straight";
 }
 void DrivingScenarios::RedLightRight()
 {
     SlowdownCar();
     std::thread Signal(SignalLight, "Right");
     std::thread WaitGreen(WaitingForGreenLight);
     Signal.join();
     WaitGreen.join();
     distance = DistanceFromCarToObject("Lidar.txt");
     Right(distance);
     direction = "Right";
 }
 void DrivingScenarios::RedLightLeft()
 {
     SlowdownCar();
     std::thread WaitGreen(WaitingForGreenLight);
     std::thread Signal(SignalLight, "Left");
     WaitGreen.join();
     Signal.join();
     distance = DistanceFromCarToObject("src/Lidar.txt");
     Left(distance);
     direction = "Left";
 }
 void DrivingScenarios::SpeedCar(int maxSpeed = 120)
 {

     try
     {
         std::ifstream inputFile(GetPathOfSpeed()); // Open input file for reading
         std::ofstream outputFile("temp.txt", std::ios::trunc); // Create temporary output file
         while (GetcurrentSpeed() < maxSpeed && TrafficLightColor() != "Red")
         {
             if (std::getline(inputFile, line))
             {
                 std::lock_guard<std::mutex> lock(mtxPathOfSpeed);
                 double num = std::stod(line); // Convert the line to integer
                 num += GetaccelerationSpeed(); // Add 7 to the number read from the file
                 outputFile << num << std::endl; // Write the modified number to the temporary file
             }
             std::this_thread::sleep_for(std::chrono::seconds(1));
         }
         outputFile << inputFile.rdbuf();
         inputFile.close();
         outputFile.close();
     }
     catch (const char* error)
     {
         std::cerr << "Error openAndChange: " << error << std::endl;
     }
     try
     {
         std::remove(GetPathOfSpeed().c_str());
     }
     catch (const char* error)
     {
         std::cerr << "Error remove: " << error << std::endl;
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
 void DrivingScenarios::SlowdownCar(int MinSpeed = 0)
 {

     try
     {
         std::ifstream inputFile(GetPathOfSpeed()); // Open input file for reading
         std::ofstream outputFile("temp.txt", std::ios::trunc); // Create temporary output file
         while (GetcurrentSpeed() > MinSpeed && TrafficLightColor() == "Red")
         {
             if (std::getline(inputFile, line))
             {
                 std::lock_guard<std::mutex> lock(mtxPathOfSpeed);
                 double num = std::stod(line); // Convert the line to integer
                 num -= GetaccelerationSpeed(); // Add 7 to the number read from the file
                 outputFile << num << std::endl; // Write the modified number to the temporary file
             }
             std::this_thread::sleep_for(std::chrono::seconds(1));
         }
         outputFile << inputFile.rdbuf();
         inputFile.close();
         outputFile.close();
     }
     catch (const char* error)
     {
         std::cerr << "Error openAndChange: " << error << std::endl;
     }
     try
     {
         std::remove(GetPathOfSpeed().c_str());
     }
     catch (const char* error)
     {
         std::cerr << "Error remove: " << error << std::endl;
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
     SlowdownCar(80);
 }

void DrivingScenarios::SignalLight(string direction)
{
    while (TrafficLightColor() == "Red")
    {
        signal = direction;
    }

}

void DrivingScenarios::Stop()
{
    SlowdownCar();
}

void DrivingScenarios::Right(double distance)
{

    while (distance >= 0.0)
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

string DrivingScenarios::TrafficLightColor()
{

    str = ReadFromFile("../src/TrafficLightColor.txt");
    return str;
}

void DrivingScenarios::LaneChangeRight()
{
    SignalLight("Right");

}

void DrivingScenarios::LaneChangeLeft()
{
    SignalLight("Left");
}



string DrivingScenarios::ReadFromFile(string filepath)
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







