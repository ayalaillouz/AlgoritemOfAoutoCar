#pragma once
#include "DrivingScenarios.h"
class Gpssenssor
{
public:
	Gpssenssor();
	void UpdatePossion(const std::string& filename, DrivingScenarios& carpoint, IMUSensor& imuSensorpoint);
};

