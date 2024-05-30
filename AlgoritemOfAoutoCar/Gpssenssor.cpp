#pragma once
#include "DrivingScenarios.h"
#include "Gpssenssor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Gpssenssor::Gpssenssor()
{
    onGps = true;

}
void Gpssenssor::UpdatePossion(DrivingScenarios& carpoint)
{
    string filepath = "C:\\Users\\USER\\Documents\\פרוייקט\\AlgoritemOfAoutoCar\\src\\GPS.txt";
    std::ifstream file(filepath);
    double pos1, pos2;
    try
    {
        std::string line;
        while (onGps)
        {
            std::getline(file, line);
            std::istringstream iss(line);
            iss >>pos1>>pos2;
            //cout << pos1 << " " << pos2 << endl;
            print("pos1:"+to_string(pos1) + " " +"pos2:"+to_string(pos2));
            carpoint.SetvelosityX(pos1);
            carpoint.SetvelosityY(pos2);
            carpoint.ConnectKalmanFilter();
            this_thread::sleep_for(chrono::seconds(2));
        }
        file.close();
    }
    catch (const char* error)
    {
        std::cout << "Error GPS : " << error << std::endl;
    }

}

void Gpssenssor::OffGPS()
{
    lock_guard<mutex>lock(mtxGps);
    onGps = false;
}

void Gpssenssor::print(const std::string& message)
{
    std::lock_guard<std::mutex> lock(mtxprint);
    std::cout << message << std::endl;
}
