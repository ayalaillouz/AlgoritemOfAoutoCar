#pragma once
#include "File.h"
#include "DrivingScenarios.h"
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
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <stdbool.h>

#define check_RedLightStraight(state)((state ==0||state==3)?0:1);
#define check_RedLightRight(state)(state ==5?0:1);
#define check_RedLightLeft(state)(state ==4?0:1);
#define check_GreenLight(state)((state ==1||state==6||state==7||state==8)?0:1);
#define check_Stop(state)((state ==9||state==11)?0:1);
#define check_SpeedLimitSignFor80(state)(state ==10?0:1);
using namespace std;
namespace fs = filesystem;
/// <summary>
/// 
/// </summary>

void DrivingScenarios::PlayHashFunctionDirection(int placeinhash, double distance)
{

    (this->*HashFunctionDirection[placeinhash])(distance);
}
void DrivingScenarios::PlayHashFunctionDrivingScenarios(int placeinhash)
{
    (this->*HashFunctionDrivingScenarios[placeinhash])();
}


string DrivingScenarios::Getdirection()
{
    return direction;
}

string DrivingScenarios::GetTrafficLightColor()
{
    lock_guard<mutex> lock(mtxTrafficLightColor);
    return TrafficLightColor;
}

void DrivingScenarios::SetTrafficLightColor(string newTrafficLightColor)
{
    lock_guard<mutex>lock(mtxTrafficLightColor);
    TrafficLightColor =newTrafficLightColor;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
double DrivingScenarios::GetoldvelosityX()
{
    lock_guard<mutex>lock(mtxoldvelosityX);
    return oldvelosityX;
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
double DrivingScenarios::GetoldvelosityY()
{
    lock_guard<mutex>lock(mtxoldvelosityY);
    return oldvelosityY;
}
/// <summary>
/// 
/// </summary>
/// <param name="newvelosityY"></param>
void DrivingScenarios::SetvelosityY(double newvelosityY)
{
    lock_guard<mutex>lock(mtxvelosityY);
    velosityY = newvelosityY;
}
/// <summary>
/// 
/// </summary>
/// <param name="newoldvelosityX"></param>
void DrivingScenarios::SetoldvelosityX(double newoldvelosityX)
{
    lock_guard<mutex>lock(mtxvelosityX);
    oldvelosityX = newoldvelosityX;
}

/// <summary>
/// 
/// </summary>
/// <param name="newdirection"></param>
void DrivingScenarios::Setdirection(string newdirection)
{
    direction = newdirection;
}

/// <summary>
/// 

double DrivingScenarios::Getdistance()
{
    lock_guard<mutex>lock(mtxdistance);
    return distance;

}
/// <summary>
/// 
/// </summary>

void DrivingScenarios::Setdistance(double newdistance)
{
    lock_guard<mutex>lock(mtxdistance);
    distance = newdistance;
}

string DrivingScenarios::Getstate()
{
    lock_guard<mutex> lock(mtxstate);
    return state;
    
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
double DrivingScenarios::Getdistancetoturn()
{
    return distancetoturn;
}



void DrivingScenarios::Setstate(string s)
{
    lock_guard<mutex> lock(mtxstate);
    state = s;
}

DrivingScenarios::DrivingScenarios()
{
    currentSpeed = 0.0;
    accelerationSpeed = 0.0; 
    temp = 0;
    PathOfSpeed = "./src/SpeedCar.txt";
    velosityX=0;
    velosityY=0;
    oldvelosityX=0;
    oldvelosityY=0;
    dt = 1.0;
   // arrState.fill(false);
    onyolo=false;
    ////fill HashFunctionDrivingScenarios
    //HashFunctionDrivingScenarios[0] = &DrivingScenarios::RedLightStraight;
    //HashFunctionDrivingScenarios[1] = &DrivingScenarios::RedLightRight;
    //HashFunctionDrivingScenarios[2] = &DrivingScenarios::RedLightLeft;
    //HashFunctionDrivingScenarios[3] = &DrivingScenarios::GreenLight;//condition:After the traffic light turns green.
    //HashFunctionDrivingScenarios[4] = &DrivingScenarios::Stop;//condition: Stop sign,crosswalk.
    //HashFunctionDrivingScenarios[5] = &DrivingScenarios::SpeedLimitSignFor80;
    ////fill HashFunctionDirection
    //HashFunctionDirection[0] = &DrivingScenarios::Left;
    //HashFunctionDirection[1] = &DrivingScenarios::Right;
    //HashFunctionDirection[2] = &DrivingScenarios::Straight;
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
/// <summary>
/// 
/// </summary>

void DrivingScenarios::SetcurrentSpeed(double speed)
{
    std::lock_guard<std::mutex> lock(mtxCurrentSpeed);
    currentSpeed = speed;
}
/// <summary>
/// 
/// </summary>
void DrivingScenarios::SetaccelerationSpeed(double newaccelationspeed)
{
    std::lock_guard<std::mutex> lock(mtxAccelerationSpeed);
    accelerationSpeed = newaccelationspeed;
}

 void DrivingScenarios::SettimeCar(int second)
 {
     std::lock_guard<std::mutex> lock(mtxTimeCar);
     timeCar = second;
 }

 int DrivingScenarios::GettimeCar()
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
     SetTrafficLightColor("Red");
     SlowdownCar();
     //WaitingForGreenLight();
     //GreenLight();
     direction = "Straight";
     std::this_thread::sleep_for(std::chrono::seconds(1)); 
 }

 //void DrivingScenarios::RedLightRight()
 //{
 //    SlowdownCar();
 //    
 //    std::thread Signal(SignalLight, "Right");

 //    std::thread WaitGreen(WaitingForGreenLight);
 //    Signal.join();
 //    WaitGreen.join();
 //    distance = DistanceFromCarToObject("src/Lidar.txt");
 //    Right(distance);
 //    direction = "Right";
 //}
 void DrivingScenarios::RedLightRight()
 {
     SlowdownCar();

     // Use '&' to create a pointer to the member function WaitingForGreenLight
     std::thread WaitGreen(&DrivingScenarios::WaitingForGreenLight, this);

     // Assuming SignalLight is also a member function, use '&' to create a pointer to it
     std::thread Signal(&DrivingScenarios::SignalLight, this, "Right");

     Signal.join();
     WaitGreen.join();

     distance = DistanceFromCarToObject("src/Lidar.txt");
     Right(distance);
     direction = "Right";
 }

 void DrivingScenarios::RedLightLeft()
 {
     SlowdownCar();
     std::thread WaitGreen( &DrivingScenarios::WaitingForGreenLight, this);
     std::thread Signal(&DrivingScenarios::SignalLight,this, "Left");
     WaitGreen.join();
     Signal.join();
     distance = DistanceFromCarToObject("src/Lidar.txt");
     Left(distance);
     direction = "Left";
 }
 void DrivingScenarios::SpeedCar(int maxSpeed)
 {
     try
     {
         std::ifstream inputFile(GetPathOfSpeed()); // Open input file for reading
         std::ofstream outputFile("temp.txt", std::ios::trunc); // Create temporary output file
         while (GetcurrentSpeed() <maxSpeed && GetTrafficLightColor() != "Red")
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

         int result = std::rename("temp.txt", GetPathOfSpeed().c_str());
         if (result != 0)
         {
             std::cerr << "Error Rename: Unable to rename file." << std::endl;
         }

     }
     catch (const char* error)
     {
         std::cerr << "Error Rename: " << error << std::endl;
     }
 }
 void DrivingScenarios::SlowdownCar(int MinSpeed)
 {

     try
     {
         std::ifstream inputFile(GetPathOfSpeed()); // Open input file for reading
         std::ofstream outputFile("temp.txt", std::ios::trunc); // Create temporary output file
         while (GetcurrentSpeed() > MinSpeed && GetTrafficLightColor() == "Red")
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

         int result = std::rename("temp.txt", GetPathOfSpeed().c_str());
         if (result != 0)
         {
             std::cerr << "Error Rename: Unable to rename file." << std::endl;
         }
        
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
    while (GetTrafficLightColor() == "Red")
    {
        signal = direction;
    }

}
/// <summary>
/// 
/// </summary>

string DrivingScenarios::getLastCreatedFolder(const string& path)
{
    fs::path folderPath(path);
    time_t latestTime = 0;
    string latestFolder;
    try
    {
        for (const auto& entry : fs::directory_iterator(folderPath))
        {
            if (fs::is_directory(entry)) {
                time_t lastWriteTime = fs::last_write_time(entry).time_since_epoch().count();
                if (lastWriteTime > latestTime) {
                    latestTime = lastWriteTime;
                    latestFolder = entry.path().string();
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }
    return latestFolder;
}

/// <summary>
/// </summary>
void DrivingScenarios::UpdateStateFromYolo()
{
    string folderPath = "C:/Users/USER/Documents/project/final_modal/yolov5/runs/detect";
    string lastCreatedFolder = getLastCreatedFolder(folderPath)+"/labels";
    onyolo = true;
    while (onyolo)
    {
        for (const auto& entry : filesystem::directory_iterator(folderPath))
        {
            if (entry.path().extension() == ".txt")
            {
                processFile(entry.path().string());
            }
            //std::this_thread::sleep_for(std::chrono::seconds(2));
        }

        // Wait for 1 second before checking again
        this_thread::sleep_for(chrono::seconds(1));
    }
}

string DrivingScenarios::extractFirstWord(const string& input)
{
    size_t pos = input.find(' '); // Find the first space character

    if (pos !=string::npos)
    {
        return input.substr(0, pos); // Extract the substring up to the first space
    }
    else 
    {
        return " "; // Return the whole string if no space is found
    }
}
/// <summary>
/// 
/// </summary>
/// <param name="imuSensorpoint"></param>
void DrivingScenarios::ConnectKalmanFilter()
{
    string result = "";
    try
    {
        // Calling the Kalman filter from a Python file with the parameters we recorded
        string command = "python.exe kalmanFilter.py " + to_string(dt) + " " + to_string(GetoldvelosityX()) + " " + to_string(GetoldvelosityY()) + " " + to_string(GetvelosityX()) + " " + to_string(GetvelosityY());
        pipe = _popen(command.c_str(), "r");
        while (!feof(pipe))
        {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }


        stringstream ss(result);
        double pos;
        while (ss >> pos)
        {
            filtered_positions.push_back(pos);
        }


        // Access and manipulate the filtered positions as needed
        cout << "Filtered positions as double array:" << endl;
        for (double position : filtered_positions)
        {
            cout << position << " ";
        }
        SetoldvelosityX(filtered_positions[2]);
        SetoldvelosityY(filtered_positions[3]);
        _pclose(pipe);
    }
    catch (const exception& e) 
    {
        cerr << "Exception caught: " << e.what() << endl;
    }
}
/// <summary>
/// 
/// </summary>

void DrivingScenarios::processFile(const string& filePath)
{
    ifstream inputFile(filePath);
    int state, placeinHashFunctionDrivingScenarios;
    if (!inputFile)
    {
        std::cerr << "Error opening the file: " << filePath << "\n";
        return;
    }

    string word;
    while (inputFile >> word)
    {
       state= stoi(word);
       placeinHashFunctionDrivingScenarios = check_RedLightStraight(state) + check_RedLightRight(state) + check_RedLightLeft(state) + check_GreenLight(state) + check_Stop(state) + check_SpeedLimitSignFor80(state);
       arrState[state] = true;
       
        // Ignore the rest of the line
        inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    inputFile.close(); // Close the file after processing

    // Close the file and then delete it
    std::remove(filePath.c_str());
    std::cout << "File " << filePath << " processed and deleted.\n";
}

/// <summary>
/// </summary>
void DrivingScenarios::Offyolo()
{
    onyolo = false;
}

void DrivingScenarios::Stop()
{
    SlowdownCar();
}

/// <summary>
/// 
/// </summary>

void DrivingScenarios::Right(double distancetoturnRight)
{
    Setdistancetoturn(distancetoturnRight);
    while (Getdistancetoturn() >= Getdistance())
    {
        Setdistancetoturn(Getdistancetoturn() - GetaccelerationSpeed());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    Setdistance(0.0);
    Setdirection("Right");
}

/// <summary>
/// 
/// </summary>
/// <param name="distance"></param>
void DrivingScenarios::Left(double distancetoturnLeft)
{
    Setdistancetoturn(distancetoturnLeft);
    while (Getdistancetoturn()>=Getdistance())
    {
        Setdistancetoturn(Getdistancetoturn()-GetaccelerationSpeed());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    Setdistance(0.0);
    Setdirection("Left");
}
/// <summary>
/// 
/// </summary>
/// <param name="newdistancetoturn"></param>
void DrivingScenarios::Setdistancetoturn(double newdistancetoturn)
{
    distancetoturn = newdistancetoturn;
}
/// <summary>
/// 
/// </summary>
/// <param name="distancetoturnStraight"></param>
void DrivingScenarios::Straight(double distancetoturnStraight)
{
    Setdirection("Straight");
    Setdistancetoturn(distancetoturnStraight);
    while (Getdistancetoturn() >= Getdistance())
    {
        Setdistancetoturn(Getdistancetoturn() - GetaccelerationSpeed());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    Setdistance(0.0);
}

void  DrivingScenarios::WaitingForGreenLight()
{
    while (GetTrafficLightColor() =="Red")
    {
       std::this_thread::sleep_for(std::chrono::seconds(1));
    }

}


void DrivingScenarios::LaneChangeRight()
{
    Setdirection("Right");
    SignalLight("Right");

}

void DrivingScenarios::LaneChangeLeft()
{
    Setdirection("Left");
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







