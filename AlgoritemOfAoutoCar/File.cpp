#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
using namespace std;

string GetWordAfterLastDash(const std::string& sentence)
{
    size_t lastDashPos = sentence.rfind('-');

    if (lastDashPos != std::string::npos && lastDashPos < sentence.length() - 1)
    {
        size_t nextSpace = sentence.find(' ', lastDashPos);

        if (nextSpace != std::string::npos)
        {
            return sentence.substr(lastDashPos + 1, nextSpace - lastDashPos - 1);
        }
        else
        {
            return sentence.substr(lastDashPos + 1);
        }
    }

    return ""; // Return an empty string if no word is found after the last dash
}

double ExtractLastWordToDouble(const string& sentence) {
    istringstream iss(sentence);
    string word;
    string lastWord;
    // Read words from the sentence
    while (iss >> word) {
        lastWord = word;
    }
    // Convert the last word to double
    double convertedValue = std::stod(lastWord);

    return convertedValue;
}
