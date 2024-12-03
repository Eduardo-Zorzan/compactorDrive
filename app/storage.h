#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;
namespace storage
{
    struct returnObject {
        string nameFile;
        string nameImage;
        string compressFile;
    };
    static vector<string> split(const string& str, const string& delimiter);
    static returnObject separator(string rawData);
    static vector<returnObject> objectVector(string allRawData);
    static string getRawData();
    string getFiles(string nameFile);
    string putFiles(string data);
    string deleteFiles(string nameFile);
    vector<returnObject> getAllFiles();
}
