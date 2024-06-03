#pragma once
#include "File.h"
#include "DrivingScenarios.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <thread>
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
#include <locale>
#include <codecvt>


#define check_RedLightStraight(state)((state ==0||state==3)?0:1);
#define check_RedLightRight(state)(state ==5?0:1);
#define check_RedLightLeft(state)(state ==4?0:1);
#define check_GreenLight(state)((state ==1||state==6||state==7||state==8)?0:1);
#define check_Stop(state)((state ==9||state==11)?0:1);
#define check_SpeedLimitSignFor80(state)(state ==10?0:1);


using namespace std;
namespace fs = filesystem;



DrivingScenarios::DrivingScenarios()
{
    currentSpeed = 0.0;
    accelerationSpeed = 0.0;
    temp = 0;
    PathOfSpeed = "C:/Users/USER/Documents/פרוייקט/AlgoritemOfAoutoCar/src/IMUsensor.txt";
    oldvelosityX = 32.3500 ;
    oldvelosityY = 35.1000;
    velosityX = 0;
    velosityY = 0;
    dt = 2;
    onyolo = false;
    maxspeed = 100;
    i = 2;
    distance = 0.0;
    distancetoturn = 0.0;
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

string DrivingScenarios::Getdirection()
{
    return direction;
}

void DrivingScenarios::Setdirection(string newdirection)
{
    direction = newdirection;
}

double DrivingScenarios::GetoldvelosityX()
{
    lock_guard<mutex>lock(mtxoldvelosityX);
    return oldvelosityX;
}

void DrivingScenarios::SetoldvelosityX(double newoldvelosityX)
{
    lock_guard<mutex>lock(mtxvelosityX);
    oldvelosityX = newoldvelosityX;
}

double DrivingScenarios::GetoldvelosityY()
{
    lock_guard<mutex>lock(mtxoldvelosityY);
    return oldvelosityY;
}

void DrivingScenarios::SetoldvelosityY(double newoldvelosityY)
{
    lock_guard<mutex>lock(mtxoldvelosityY);
    oldvelosityY = newoldvelosityY;
}

double DrivingScenarios::GetvelosityY()
{
    lock_guard<mutex>lock(mtxvelosityY);
    return velosityY;
}

void DrivingScenarios::SetvelosityY(double newvelosityY)
{
    lock_guard<mutex>lock(mtxvelosityY);
    velosityY = newvelosityY;
}

double DrivingScenarios::GetvelosityX()
{
    lock_guard<mutex>lock(mtxvelosityX);
    return velosityX;
}

void DrivingScenarios::SetvelosityX(double newvelosityX)
{
    lock_guard<mutex>lock(mtxvelosityX);
     velosityX= newvelosityX;
}

double DrivingScenarios::Getdistance()
{
    lock_guard<mutex>lock(mtxdistance);
    return distance;

}

void DrivingScenarios::Setdistance(double newdistance)
{
    lock_guard<mutex>lock(mtxdistance);
    distance += newdistance;
    if (Getdistancetoturn()-newdistance>=0)
    {
        Setdistancetoturn(Getdistancetoturn()-newdistance);
    }
    else
    {
        Setdistancetoturn(0.0);
        distance = 0.0;
        print("Setdistancetoturn 0.0");
    }
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

double DrivingScenarios::GetaccelerationSpeed()
{
    std::lock_guard<std::mutex> lock(mtxAccelerationSpeed);
    return accelerationSpeed;
}

void DrivingScenarios::SetaccelerationSpeed(double newaccelationspeed)
{
    std::lock_guard<std::mutex> lock(mtxAccelerationSpeed);
    accelerationSpeed = newaccelationspeed;
}

double DrivingScenarios::Getdistancetoturn()
{
    return distancetoturn;
}

void DrivingScenarios::Setdistancetoturn(double newdistancetoturn)
{
    distancetoturn = newdistancetoturn;
}

int DrivingScenarios::GettimeCar()
{
    std::lock_guard<std::mutex> lock(mtxTimeCar);
    return timeCar;
}

void DrivingScenarios::SettimeCar(int second)
{
    std::lock_guard<std::mutex> lock(mtxTimeCar);
    timeCar = second;
}

string DrivingScenarios::GetPathOfSpeed()
{
    std::lock_guard<std::mutex> lock(mtxSpeed);
    return PathOfSpeed;
}

void DrivingScenarios::PlayHashFunctionDirection(int placeinhash, double dist)
{

    (this->*HashFunctionDirection[placeinhash])(dist);
}

void DrivingScenarios::PlayHashFunctionDrivingScenarios(int placeinhash)
{
    (this->*HashFunctionDrivingScenarios[placeinhash])();
}

//double DrivingScenarios::DistanceFromCarToObject(std::string filename)
//{
//    //Reads a row of values from a file, and returns the minimum value
//    std::ifstream file(filename);
//    double minVal = std::numeric_limits<double>::max();//Initialize to the maximum value
//
//    if (file.is_open())
//    {
//        std::string line;
//        if (std::getline(file, line))
//        {
//            istringstream iss(line);
//            double value;
//
//            while (iss >> value)
//            {
//                if (value < minVal)
//                {
//                    minVal = value;
//                }
//            }
//
//            // Remove the line from the file
//           vector<string> remainingLines;
//            while (getline(file, line)) {
//                if (!line.empty()) {
//                    remainingLines.push_back(line);
//                }
//            }
//
//            file.close();
//
//            std::ofstream outFile(filename, std::ios::out | std::ios::trunc);
//            for (const auto& l : remainingLines) {
//                outFile << l << std::endl;
//            }
//            outFile.close();
//        }
//        else {
//            std::cerr << "Error: File is empty." << std::endl;
//            file.close();
//            return -1.0; // Return -1 to indicate error
//        }
//    }
//    else {
//        std::cerr << "Error: Unable to open file." << std::endl;
//        return -1.0; // Return -1 to indicate error
//    }
//    return minVal;
//}

 void DrivingScenarios::RedLightStraight()
 {
     if (directiontotravel.compare("Straight")==0)
     {
         print("RedLightStraight function now play");
         SetTrafficLightColor("Red");
         while (GetTrafficLightColor().compare("Red") == 0)
         {
             SlowdownCar();
             std::this_thread::sleep_for(std::chrono::seconds(1));
         }
         arrState.reset(0);
     }
 }

 void DrivingScenarios::RedLightRight()
 {
     
     if (directiontotravel.compare("Right")==0)
     {
         print("RedLightRight function now play");
         SetTrafficLightColor("Red");
         while (GetTrafficLightColor().compare("Red")==0)
         {
             SlowdownCar();
             SignalLight("Right");
             this_thread::sleep_for(chrono::seconds(1));
         }
         arrState.reset(1);
     }
 }

 void DrivingScenarios::RedLightLeft()
 {
     if (directiontotravel.compare("Left")==0)
     {
         print("RedLightLeft function now play");
         SetTrafficLightColor("Red");
         while (GetTrafficLightColor().compare("Red")==0)
         {
             SlowdownCar();
             SignalLight("Left");
             this_thread::sleep_for(chrono::seconds(1));
         }
         arrState.reset(2);
     }  
 }

 void DrivingScenarios::SpeedCar(int maxSpeed)
 {
     print("SpeedCar function now play");

     if (GetcurrentSpeed() < maxSpeed)
     {
      
         string line;
         ifstream inputFile(GetPathOfSpeed()); // Open input file for reading
         ofstream outputFile("temp.txt", ios::trunc); // Create temporary output file
         double speedX, speedY, deltaX, deltaY, speed;

         if (!inputFile.is_open())
         {
             cerr << "Error opening file IMU" << endl;
             
         }

         if (getline(inputFile, line))
         {
             istringstream iss(line);
             iss >> speedX >> speedY;
             speed = sqrt((speedX * speedX) + (speedY * speedY));
             deltaX = GetaccelerationSpeed() * (speedX / speed);
             deltaY = GetaccelerationSpeed() * (speedY / speed);
             speedX = speedX + deltaX;
             speedY = speedY + deltaY;
             outputFile << speedX << " " << speedY << endl;
         }

         outputFile << inputFile.rdbuf();
         inputFile.close();
         outputFile.close();

         if (std::remove(GetPathOfSpeed().c_str()) != 0)
         {
             std::cerr << "Error remove: Unable to remove file." << std::endl;
         }

         if (std::rename("temp.txt", GetPathOfSpeed().c_str()) != 0)
         {
             std::cerr << "Error Rename: Unable to rename file." << std::endl;
         }
     }
 }

 void DrivingScenarios::SlowdownCar(int MinSpeed)
 {
     print("SlowdownCar function now play");

     if (GetcurrentSpeed() > MinSpeed)
     {
         string line;
         ifstream inputFile(GetPathOfSpeed()); 
         ofstream outputFile("temp.txt", ios::trunc); 
         double speedX, speedY, deltaX, deltaY, speed;
         if (!inputFile.is_open())
         {
             cerr << "Error opening file IMU" << endl;
             return;
         }

         if (getline(inputFile, line))
         {
             istringstream iss(line);
             iss >> speedX >> speedY;
             speed = sqrt((speedX * speedX) + (speedY * speedY));
             deltaX = GetaccelerationSpeed() * (speedX / speed);
             deltaY = GetaccelerationSpeed() * (speedY / speed);
             speedX = speedX - deltaX;
             speedY = speedY - deltaY;
             outputFile << speedX << " " << speedY << endl; // Write the modified number to the temporary file 
         }

         outputFile << inputFile.rdbuf();
         inputFile.close();
         outputFile.close();

         if (std::remove(GetPathOfSpeed().c_str()) != 0)
         {
             std::cerr << "Error remove: Unable to remove file." << std::endl;
         }

         if (std::rename("temp.txt", GetPathOfSpeed().c_str()) != 0)
         {
             std::cerr << "Error Rename: Unable to rename file." << std::endl;
         }
     }
 }

 void DrivingScenarios::GreenLight()
 {
     SetTrafficLightColor("Green");
     print("GreenLight function now play");
     while (GetcurrentSpeed() <MaxSpeed())
     {
         SpeedCar(MaxSpeed());
         this_thread::sleep_for(chrono::seconds(1));
     }
     arrState.reset(3);
 }

 void DrivingScenarios::Stop()
 {
     while (GetcurrentSpeed()>0.0)
     {
         SlowdownCar();
         this_thread::sleep_for(chrono::seconds(1));
     }
     arrState.reset(4);
 }

 int DrivingScenarios::MaxSpeed()
 {
     lock_guard<mutex>lock(mtxmaxspeed);
     return maxspeed;
 }

 void DrivingScenarios::Setmaxspeed(int newmaxspeed)
 {
     lock_guard<mutex>lock(mtxmaxspeed);
     maxspeed = newmaxspeed;
 }

 void DrivingScenarios::SpeedLimitSignFor80()
 {
     print("SpeedLimitSignFor80 function now play");
     Setmaxspeed(80);
     while (GetcurrentSpeed()>80)
     {
         SlowdownCar(80);
         this_thread::sleep_for(chrono::seconds(1));
     }
     arrState.reset(5);
 }

 void DrivingScenarios::SignalLight(string direction)
 {
     signal = direction;
     print("signal: "+signal);
 }



 void DrivingScenarios::Right(double distancetoturnRight)
 {
     directiontotravel = "Right";
     print("Right function now play");
     Setdistancetoturn(distancetoturnRight);
     while (Getdistancetoturn() > 0.0)
     {
         std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     if (Getdistancetoturn()==0.0)
     {
         Setdirection("Right");
     }
 }

 void DrivingScenarios::Left(double distancetoturnLeft)
 {
     directiontotravel = "Left";
     print("Left function now play");
     Setdistancetoturn(distancetoturnLeft);
     while (Getdistancetoturn() > 0.0)
     {
         std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     if (Getdistancetoturn()==0.0)
     {
         Setdirection("Left");
     }


 }

 void DrivingScenarios::Straight(double distancetoturnStraight)
 {
     directiontotravel = "Straight";
     print("Straight function now play");
     Setdirection("Straight");
     Setdistancetoturn(distancetoturnStraight);
     while (Getdistancetoturn() > 0.0)
     {
         std::this_thread::sleep_for(std::chrono::seconds(1));
     }
 }


 string DrivingScenarios::ReadFromFile(string filepath)
 {
     std::ifstream inputFile(filepath);  // Open the file for reading
     std::string fileContent;  // Variable to store the file content
     std::string line;
     try {
         // Read the file content into a variableReadFromFile
         while (inputFile.is_open())
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

void DrivingScenarios::UpdateStateFromYolo()
{
    string path = "C:\\Users\\USER\\Documents\\פרוייקט\\final_modal\\yolov5\\runs\\detect";
    string lastCreatedFolder =getLastCreatedFolder(path)+"\\labels";
    processTxtFiles(lastCreatedFolder);
}

void DrivingScenarios::processTxtFiles(const std::string& folderPath)
{
    onyolo = true;
    while (onyolo)
    {
        for (const auto& entry : fs::directory_iterator(folderPath))
        {
            if (entry.path().extension() == ".txt")
            {
                processFile(entry.path().string());
            }
        }
    }
}

void DrivingScenarios::processFile(const string& filePath)
{
    ifstream inputFile(filePath);
    int state, placeinHashFunctionDrivingScenarios;
    if (!inputFile)
    {
        std::cerr << "Error opening the file of yolo: " << filePath << "\n";
        return;
    }

    std::string line, word;
    while (std::getline(inputFile, line))
    {
        std::istringstream iss(line);
        iss >> word;
        int state = std::stoi(word);
        placeinHashFunctionDrivingScenarios = check_RedLightStraight(state) + check_RedLightRight(state)
            + check_RedLightLeft(state) + check_GreenLight(state) + check_Stop(state) + check_SpeedLimitSignFor80(state);

        if (placeinHashFunctionDrivingScenarios >= 0 && placeinHashFunctionDrivingScenarios < 6)
        {
            if (!arrState.test(placeinHashFunctionDrivingScenarios))
            {
                arrState.set(placeinHashFunctionDrivingScenarios);
                thread t(&DrivingScenarios::PlayHashFunctionDrivingScenarios, this, placeinHashFunctionDrivingScenarios);
                t.detach();
            }
        }

    }

    inputFile.close(); 
    std::remove(filePath.c_str());
    print("File " + filePath + " processed and deleted");
}

void DrivingScenarios::runYolo()
{
    std::wstring batchFilePath = L"C:\\Users\\USER\\Documents\\פרוייקט\\final_modal\\yolov5\\CMD.bat";

    // Build the command to run the batch file
    std::wstring fullCommand = L"\"";
    fullCommand += batchFilePath;
    fullCommand += L"\"";

    // Execute the command to run the batch file
    _wsystem(fullCommand.c_str());
}

void DrivingScenarios::Offyolo()
{
    onyolo = false;
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

void DrivingScenarios::ConnectKalmanFilter()
{
  
    string result = "";
    try
    {
        // Calling the Kalman filter from a Python file with the parameters we recorded
        string command = "python.exe kalmanFilter.py " + to_string(GetoldvelosityX()) + " " + to_string(GetoldvelosityY()) + " " +
            to_string(GetvelosityX()) + " " + to_string(GetvelosityY());
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
        SetoldvelosityX(GetvelosityX());
        SetoldvelosityY(GetvelosityY());
        SetvelosityX(filtered_positions[i]);
        SetvelosityY(filtered_positions[i+1]);
        print("velosityX:" + to_string(filtered_positions[i]) + " " + "velosityY:" + to_string(filtered_positions[i+1]));
        i = i + 2;
        _pclose(pipe);
    }
    catch (const exception& e) 
    {
        cerr << "Exception caught: " << e.what() << endl;
    }
}


void DrivingScenarios::print(const std::string& message)
{
    std::lock_guard<std::mutex> lock(mtxprint);
    std::cout << message << std::endl;
}


