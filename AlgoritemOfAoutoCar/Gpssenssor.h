#pragma once
#include "DrivingScenarios.h"
class Gpssenssor
{
	Gpssenssor();
	void UpdatePossion(const std::string& filename, DrivingScenarios& carpoint);
};

