#pragma once

#include "stdio.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio> 
#include <regex>

using namespace std;

namespace Compactor {
    void StartCompression(const std::string& filePath, const std::string& fileName);
    static vector<string> split(const string& str, const string& delimiter);
    string checkProcess();
    void compactFile(const std::string& filePath, const std::string& fileName);
    string descompactFile(string fileName, string folderName);
    string deleteFile(string fileName);
}
