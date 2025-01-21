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
    void StartCompression(const vector<string> filePath, const vector<string> fileName, const bool deleteOrigin);
    static vector<string> split(const string& str, const string& delimiter);
    string checkProcess();
    void compactFile(const string& filePath, const string& fileName, const bool deleteOrigin);
    void descompactFile(string fileName, string folderName);
    void StartDecompression(const string& fileName, vector<string> listToDescompress);
    string deleteFile(string fileName);
}
