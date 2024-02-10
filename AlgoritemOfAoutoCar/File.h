#pragma once
#include <iostream>
using namespace std;
class File
{
public:
	string ReadFromFileAllText(string path);
	string ReadFromFileWord(string path);
	void deleteFirstLine(string filePath);
	void deleteRowsFromFile(string filePath, int numRowsToDelete);
	void writeToBeginningOfFile(string filePath, string textToWrite);
	void processFile(const std::string& filename);
};

