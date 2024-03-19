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

void File::processFile(const std::string& filename)
{
    std::ifstream inputFile(filename); // Open input file for reading
    std::ofstream outputFile("temp.txt", std::ios::trunc); // Create temporary output file

    if (!inputFile.is_open()) {
        std::cerr << "Error opening input file." << std::endl;
        return;
    }

    if (!outputFile.is_open()) {
        std::cerr << "Error opening output file." << std::endl;
        return;
    }

    std::string line;
    int numToAdd = 7;

    if (std::getline(inputFile, line)) {
        int num = std::stoi(line); // Convert the line to integer
        num += numToAdd; // Add 7 to the number read from the file
        outputFile << num << std::endl; // Write the modified number to the temporary file
    }

    // Copy the rest of the lines from input file to the output file
    outputFile << inputFile.rdbuf();

    inputFile.close();
    outputFile.close();

    // Remove the original file
    if (std::remove(filename.c_str()) != 0) {
        std::cerr << "Error deleting original file." << std::endl;
    }

    // Rename the temporary file to the original file
    if (std::rename("temp.txt", filename.c_str()) != 0) {
        std::cerr << "Error renaming file." << std::endl;
    }
}

double File::calculateNearestPointDistance(std::string filename)
{
    std::ifstream file(filename);
    double minVal = std::numeric_limits<double>::max();

    if (file.is_open()) {
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
