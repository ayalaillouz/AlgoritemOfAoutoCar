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
#include <filesystem>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;
namespace fs = filesystem;


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

double DrivingScenarios::GetvelosityX()
{
    lock_guard<mutex>lock(mtxvelosityX);
    return velosityX;
}
double DrivingScenarios::GetvelosityY()
{
    lock_guard<mutex>lock(mtxvelosityY);
    return velosityY;
}
double DrivingScenarios::GetoldvelosityX()
{
    lock_guard<mutex>lock(mtxoldvelosityX);
    return oldvelosityX;
}
double DrivingScenarios::GetoldvelosityY()
{
    lock_guard<mutex>lock(mtxoldvelosityY);
    return oldvelosityY;
}
void DrivingScenarios::Setdirection(string newdirection)
{
    direction = newdirection;
}

double DrivingScenarios::Getdistance()
{
    return distance;
}

void DrivingScenarios::SetvelosityX(double newvelosityX)
{
    lock_guard<mutex>lock(mtxvelosityX);
    velosityX = newvelosityX;
}
void DrivingScenarios::SetvelosityY(double newvelosityY)
{
    lock_guard<mutex>lock(mtxvelosityY);
    velosityY = newvelosityY;
}
void DrivingScenarios::SetoldvelosityX(double newoldvelosityX)
{
    lock_guard<mutex>lock(mtxvelosityX);
     oldvelosityX= newoldvelosityX;
}
void DrivingScenarios::SetoldvelosityY(double newoldvelosityY)
{
    lock_guard<mutex>lock(mtxvelosityY);
    oldvelosityY = newoldvelosityY;
}
void DrivingScenarios::Setdistance(double newdistance)
{
    distance = newdistance;
}

string DrivingScenarios::Getstate()
{
    lock_guard<mutex> lock(mtxstate);
    return state;
    
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
     distance = DistanceFromCarToObject("src/Lidar.txt");
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
         while (GetcurrentSpeed() < maxSpeed && GetTrafficLightColor() != "Red")
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
    while (GetTrafficLightColor() == "Red")
    {
        signal = direction;
    }

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
    string folderPath = "C:/Users/USER/Documents/project/final_modal/yolov5/runs/detect";
    string lastCreatedFolder = getLastCreatedFolder(folderPath);
    try
    {
        string filePath = lastCreatedFolder + "/predictions.csv";

        // Read the Excel file
        ifstream file(filePath);
        if (!file.is_open()) 
        {
            cerr << "Error opening file." << endl;
        }

        // Temporarily store lines that do not contain column B content
        vector<string> fileData;
        string line;
        while (getline(file, line))
        {
            size_t pos = 0;
            int columnCount = 1;
            bool deleteRow = false;
            string res;
      
            // Parse the line to check for column B content
            while ((pos = line.find(',')) != std::string::npos)
            {
                res=line.substr(0, pos);
                line.erase(0, pos + 1);
                if (columnCount == 2)
                {
                    Setstate(res);
                    //cout << "Column B Content: " <<res << endl;
                    deleteRow = true;
                }

                columnCount++;
            }

            if (deleteRow)
            {
                // Skip adding the line to fileData vector
                deleteRow = false;
            }
            else
            {
                fileData.push_back(line);
            }
        }

        file.close();

        // Write the updated data back to the file
        ofstream outFile(filePath);
        try
        {
            if (outFile.is_open())
            {
                for (const auto& data : fileData)
                {
                    outFile << data << std::endl;
                }
                outFile.close();
            }
        }
        catch (const exception& e)
        {
            cerr << "An error occurred: " << e.what() << std::endl;
        }
    }
    catch (const exception& e)
    {
        cerr << "An error occurred: " << e.what() << std::endl;
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

void DrivingScenarios::ConnectKalmanFilter(IMUSensor& imuSensorpoint)
{
    string result = "";
    try
    {
        // Calling the Kalman filter from a Python file with the parameters we recorded
        string command = "python.exe kalmanFilter.py " + to_string(imuSensorpoint.getdt()) + " " + to_string(GetoldvelosityX()) + " " + to_string(GetoldvelosityY()) + " " + to_string(GetvelosityX()) + " " + to_string(GetvelosityY());
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
    catch (const exception& e) {
        cerr << "Exception caught: " << e.what() << endl;
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
        Setdistance(Getdistance() -GetaccelerationSpeed());
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void DrivingScenarios::Straight(double distance=0)
{
    Setdistance(Getdistance() - GetaccelerationSpeed());
    std::this_thread::sleep_for(std::chrono::seconds(1));
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







