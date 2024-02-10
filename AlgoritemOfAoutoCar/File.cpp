#include "File.h"
#include <fstream>
#include <sstream>
#include <string>
string File::ReadFromFileAllText(string path)
{
    std::ifstream inputFile;
    std::string str = "";
    inputFile.open(path); 
    if (inputFile.is_open())
    {
        std::string line;
        while (getline(inputFile, line))
        {
            str += line + " ";
        }
        // Close the file after reading
        inputFile.close();
    }
    else
    {
        std::cout << "Failed to open the file." << std::endl;
    }
    return str;
}

string File::ReadFromFileWord(string path)
{
    std::ifstream inputFile;
    std::string line = "";
    inputFile.open(path); // Open the file "example.txt" for reading
    if (inputFile.is_open())
    {
        getline(inputFile, line);
        inputFile.close();
    }
    else
    {
        std::cout << "Failed to open the file." << std::endl;
    }
    return line;
}

void File::deleteFirstLine(string filePath)
{
    std::ifstream inputFile(filePath);
    std::string line; 
    if (inputFile.is_open())
    {
        std::getline(inputFile, line);
        std::ofstream outputFile(filePath, std::ios::trunc);
        if (outputFile.is_open())
        {
            while (std::getline(inputFile, line))
            {
                outputFile << line << std::endl;
            }
            outputFile.close();
            std::cout << "First line deleted successfully!" << std::endl;
        }
        else {
           
            std::cout << "Failed to open the file for writing." << std::endl;
        }
        inputFile.close();
    }
    else {
        std::cout << "Failed to open the file." << std::endl;
    }
}

void File::deleteRowsFromFile(string filePath, int numRowsToDelete)
{
    std::ifstream inputFile(filePath);
    std::ofstream outputFile("temp.txt", std::ios::trunc);
    if (inputFile.is_open() && outputFile.is_open()) {
        std::string line;
        int rowCounter = 0;

        while (std::getline(inputFile, line))
        {
            if (rowCounter >= numRowsToDelete)
            {
                outputFile << line << std::endl;
            }
            rowCounter++;
        }

        inputFile.close();
        outputFile.close();
        std::remove(filePath.c_str());
        std::rename("temp.txt", filePath.c_str());
        std::cout << "Rows deleted successfully!" << std::endl;
    }
    else {
        std::cout << "Failed to open the file." << std::endl;
    }
}

void File::writeToBeginningOfFile(string filePath, string textToWrite)
{
    std::ifstream fileIn(filePath);
    string content((std::istreambuf_iterator<char>(fileIn)), std::istreambuf_iterator<char>());
    fileIn.close();
    std::ofstream fileOut(filePath, std::ios::trunc);
    fileOut << textToWrite << content;
    fileOut.close();
}
