#include "Gpssenssor.h"
#include "IMUSensor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

Gpssenssor::Gpssenssor()
{

}
void Gpssenssor::UpdatePossion(const std::string& filename, DrivingScenarios& carpoint, IMUSensor& imuSensorpoint)
{
    std::ifstream file(filename);
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
            carpoint.SetvelosityX(pos2);
            carpoint.ConnectKalmanFilter(imuSensorpoint);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
        file.close();
    }
    catch (const char* error)
    {
        std::cout << "Error: " << error << std::endl;
    }

}
