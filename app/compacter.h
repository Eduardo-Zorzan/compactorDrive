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
    string returnFileNameGlobal();
    static vector<string> split(const string& str, const string& delimiter);
    string compactFile(string filePath);
    string descompactFile(string fileName, string folderName);
    string deleteFile(string fileName);
}
