#pragma once
#include "DrivingScenarios.h"
#include "Gpssenssor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Gpssenssor::Gpssenssor()
{

}
void Gpssenssor::UpdatePossion(DrivingScenarios& carpoint)
{
    std::ifstream file("src/GPS.txt");
   // std::vector<std::pair<double, double>> values;
    double pos1, pos2;
    try
    {
        std::string line;
        while (std::getline(file, line)) 
        {
            std::istringstream iss(line);
            iss >>pos1>>pos2;
            carpoint.SetvelosityX(pos1);
            carpoint.SetvelosityY(pos2);
            carpoint.ConnectKalmanFilter();
            this_thread::sleep_for(chrono::seconds(2));
        }
        file.close();
    }
    catch (const char* error)
    {
        std::cout << "Error: " << error << std::endl;
    }

}
