#pragma once
#include <iostream>
#include <string.h>
using namespace std;
class File
{
public:
	File();
	string GetWordAfterLastDash(const std::string& sentence);
	double ExtractLastWordToDouble(const string& sentence);

};

