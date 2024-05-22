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



DrivingScenarios::DrivingScenarios()
{
    currentSpeed = 0.0;
    accelerationSpeed = 0.0;
    temp = 0;
    PathOfSpeed = "src/IMUsensor.txt";
    velosityX = 0;
    velosityY = 0;
    oldvelosityX = 0;
    oldvelosityY = 0;
    dt = 1.0;
    onyolo = false;
    play = true;
    maxspeed = 100;
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

void DrivingScenarios::Setplay(bool newplay)
{

    lock_guard<mutex>lock(mtxplay);
    play = newplay;
}

bool DrivingScenarios::Getplay()
{
    lock_guard<mutex>lock(mtxplay);
    return play;
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
    distance = newdistance;
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
     print("RedLightStraight function now play");
    // cout << "RedLightStraight function now play" << endl;
     Setplay(false);
     SetTrafficLightColor("Red");
     while (GetTrafficLightColor() == "Red")
     {
         SlowdownCar();
         //WaitingForGreenLight();
         //GreenLight();
         std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     Setplay(true);
     arrState.reset(0);
     Straight(Getdistancetoturn());
  
 }

 void DrivingScenarios::RedLightRight()
 {
     print("RedLightRight function now play");
    // cout << "RedLightRight function now play" << endl;
     Setplay(false);
     if (directiontotravel == "Right")
     {
         SetTrafficLightColor("Red");
         while (GetTrafficLightColor()=="Red")
         {
             SlowdownCar();
             //  std::thread WaitGreen(&DrivingScenarios::WaitingForGreenLight, this);
             SignalLight("Right");
             // Assuming SignalLight is also a member function, use '&' to create a pointer to it
             //std::thread Signal(&DrivingScenarios::SignalLight, this, "Right");
             //Signal.join();
            // WaitGreen.join();
             this_thread::sleep_for(chrono::seconds(1));
         }
      
     }
     Setplay(true);
     arrState.reset(1);
     Right(distancetoturn);
 }


 void DrivingScenarios::RedLightLeft()
 {
     print("RedLightLeft function now play");
    // cout << "RedLightLeft function now play" << endl;
     Setplay(false);
     if (directiontotravel == "Left")
     {
         SetTrafficLightColor("Red");
         while (GetTrafficLightColor() == "Red")
         {
             SlowdownCar();
             //// Create threads for WaitingForGreenLight and SignalLight
             //std::thread WaitGreen(&DrivingScenarios::WaitingForGreenLight, this);
             //std::thread Signal(&DrivingScenarios::SignalLight, this, "Left");
             //// Wait for the threads to finish before continuing
             //WaitGreen.join();
             //Signal.join();
             SignalLight("Left");
             this_thread::sleep_for(chrono::seconds(1));
         }
     }
     Setplay(true);
     arrState.reset(2);
     Left(Getdistancetoturn());
     
 }

 void DrivingScenarios::SpeedCar(int maxSpeed)
 {
     print("SpeedCar function now play");
     //cout << "SpeedCar function now play" << endl;
     if (GetcurrentSpeed() < maxSpeed)
     {
     try
     {
         string line;
         ifstream inputFile(GetPathOfSpeed()); // Open input file for reading
         ofstream outputFile("temp.txt",ios::trunc); // Create temporary output file
         double speedX, speedY, deltaX, deltaY,speed;
         if (getline(inputFile, line))
         {
            istringstream iss(line);
            iss >> speedX >> speedY;
            // double num = std::stod(line); // Convert the line to integer
            speed = sqrt((speedX * speedX) + (speedY * speedY));
            deltaX = GetaccelerationSpeed() * (speedX / speed);
            deltaY = GetaccelerationSpeed() * (speedY / speed);
            speedX = speedX+deltaX;
            speedY = speedY+deltaY;
            print("speedX:" + to_string(speedX)+" "+ "speedY:"+to_string(speedY));
            //cout << "speedX:" << speedX << " " << "speedY:" << speedY << endl;
            outputFile << speedX << " " << speedX << endl; // Write the modified number to the temporary file 
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
 }
 void DrivingScenarios::SlowdownCar(int MinSpeed)
 {
     print("SlowdownCar function now play");
    // cout << "SlowdownCar function now play" << endl;
     if (GetcurrentSpeed() > MinSpeed)
     {
         try
         {
             string line;
             ifstream inputFile(GetPathOfSpeed()); // Open input file for reading
             ofstream outputFile("temp.txt", ios::trunc); // Create temporary output file
             double speedX, speedY, deltaX, deltaY, speed;
             if (getline(inputFile, line))
             {
                 istringstream iss(line);
                 iss >> speedX >> speedY;
                 // double num = std::stod(line); // Convert the line to integer
                 speed = sqrt((speedX * speedX) + (speedY * speedY));
                 deltaX = GetaccelerationSpeed() * (speedX / speed);
                 deltaY = GetaccelerationSpeed() * (speedY / speed);
                 speedX = speedX - deltaX;
                 speedY = speedY - deltaY;
                 print("speedX:" + to_string(speedX) + " " + "speedY:" + to_string(speedY));
                // cout << "speedX:" << speedX << " " << "speedY:" << speedY << endl;
                 Setdistancetoturn(Getdistancetoturn()-GetaccelerationSpeed());
                 outputFile << speedX << " " << speedX << endl; // Write the modified number to the temporary file 
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
     

 }
 void DrivingScenarios::GreenLight()
 {
     print("GreenLight function now play");
     //cout << "GreenLight function now play" << endl;
     SetTrafficLightColor("Green");
     while (GetcurrentSpeed() < MaxSpeed())
     {
         SpeedCar(MaxSpeed());
         this_thread::sleep_for(chrono::seconds(1));
     }
     arrState.reset(3);
 }
 void DrivingScenarios::Stop()
 {
     while (GetcurrentSpeed() > 0.0)
     {
         SlowdownCar();
         this_thread::sleep_for(chrono::seconds(1));
     }
     arrState.reset(4);
 }

 int DrivingScenarios::MaxSpeed()
 {
     return maxspeed;
 }

 void DrivingScenarios::Setmaxspeed(int newmaxspeed)
 {
     maxspeed = newmaxspeed;
 }

 void DrivingScenarios::SpeedLimitSignFor80()
 {
     print("SpeedLimitSignFor80 function now play");
    // cout << "SpeedLimitSignFor80 function now play" << endl;
     Setmaxspeed(80);
     while (GetcurrentSpeed() > 80)
     {
         SlowdownCar(80);
         this_thread::sleep_for(chrono::seconds(1));
     }
     arrState.reset(5);
 }

 void DrivingScenarios::SignalLight(string direction)
 {
     signal = direction;
     print("signal:"+signal);
     //cout << "signal:" << signal << endl;
 }



 void DrivingScenarios::Right(double distancetoturnRight)
 {
     print("Right function now play");
     //cout << "Right function now play" << endl;
     directiontotravel = "Right";
     Setdistancetoturn(distancetoturnRight);
     while (Getdistancetoturn() >= Getdistance() && Getplay())
     {
         Setdistancetoturn(Getdistancetoturn() - GetaccelerationSpeed());
         std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     if (Getdistancetoturn() < Getdistance())
     {

         Setdistance(0.0);
         Setdirection("Right");
     }
 }

 void DrivingScenarios::Left(double distancetoturnLeft)
 {
     print("Left function now play");
    // cout << "Left function now play" << endl;
     directiontotravel = "Left";
     Setdistancetoturn(distancetoturnLeft);
     while (Getdistancetoturn() >= Getdistance() && Getplay())
     {
         Setdistancetoturn(Getdistancetoturn() - GetaccelerationSpeed());
         std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     if (Getdistancetoturn() < Getdistance())
     {

         Setdistance(0.0);
         Setdirection("Left");
     }


 }

 void DrivingScenarios::Straight(double distancetoturnStraight)
 {
     print("Straight function now play");
    // cout << "Straight function now play" << endl;
     directiontotravel = "Straight";
     Setdirection("Straight");
     Setdistancetoturn(distancetoturnStraight);
     while (Getdistancetoturn() >= Getdistance() && Getplay())
     {
         Setdistancetoturn(Getdistancetoturn() - GetaccelerationSpeed());
         std::this_thread::sleep_for(std::chrono::seconds(1));
     }
     if (Getdistancetoturn() < Getdistance())
     {

         Setdistance(0.0);
     }
 }

 //void  DrivingScenarios::WaitingForGreenLight()
 //{
 //    while (GetTrafficLightColor() =="Red")
 //    {
 //       std::this_thread::sleep_for(std::chrono::seconds(1));
 //    }
 //
 //}

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
    string lastCreatedFolder ="C:\\Users\\USER\\Documents\\פרוייקט\\final_modal\\yolov5\\runs\\detect\\exp31\\labels";
    processTxtFiles(lastCreatedFolder);
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
        string command = "python.exe kalmanFilter.py " + to_string(dt) + " " + to_string(GetoldvelosityX()) + " " + to_string(GetoldvelosityY()) + " " +
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


        // Access and manipulate the filtered positions as needed
        print("Filtered positions as double array:");
        cout << "Filtered positions as double array:" << endl;
        for (double position : filtered_positions)
        {
            print(to_string(position));
            //cout << position << " ";
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

    inputFile.close(); // Close the file after processing

    // Close the file and then delete it
    std::remove(filePath.c_str());
    print("File " + filePath + " processed and deleted");
    //std::cout << "File " << filePath << " processed and deleted.\n";
}
//void DrivingScenarios::runYolo()
//{
//    string batchFilePath = "C:\\Users\\USER\\Documents\\פרוייקט\\final_modal\\yolov5\\CMD.bat";
//
//    // Build the command to run the batch file
//    string fullCommand = "\"";
//    fullCommand += batchFilePath;
//    fullCommand += "\"";
//
//    // Execute the command to run the batch file
//    system(fullCommand.c_str());
//}



void DrivingScenarios::Offyolo()
{
    onyolo = false;
}

void DrivingScenarios::print(const std::string& message)
{
    std::lock_guard<std::mutex> lock(mtxprint);
    std::cout << message << std::endl;
}


