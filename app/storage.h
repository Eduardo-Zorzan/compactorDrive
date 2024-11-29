#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;
namespace storage
{
    static vector<string> split(const string& str, const string& delimiter);
    string getFiles(string nameFile);
    string putFiles(string data);
    string deleteFiles(string nameFile);
    string getAllFiles();
}
