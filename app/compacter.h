#pragma once

#include "stdio.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cstdio> 

using namespace std;

namespace Compactor {
    string compactFile(string compactedName, string filePath);
    string descompactFile(string fileName, string folderName);
    //string deleteFile(string fileName);
}
