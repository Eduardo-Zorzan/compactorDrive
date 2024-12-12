#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>

using namespace std;

namespace storage
{
    struct returnObject {
        string nameFile;
        string nameImage;
        string compressFile;
    };
    vector<string> split(const string& str, const string& delimiter);
    static returnObject separator(string rawData);
    static vector<returnObject> objectVector(string allRawData);
    static string getRawData();
    string getFiles(string nameFile);
    string putFiles(string data);
    string deleteFiles(string nameFile);
    vector<returnObject> getAllFiles();
}
