#include "compacter.h"
#include <cstdio> 
using namespace std;

namespace Compactor {
    string compactFile(string compactedName, string filePath) {
        const string fileCommand = "rar a -m5 -s ../temporary/" + compactedName + " " + filePath;
        FILE* pipe = _popen(fileCommand.c_str(), "r");
        if (!pipe) {
            return "Failed to run command\n";        }

        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr);
        //if(buffer != "Done") return "Failed to run command\n";
        return buffer;
        _pclose(pipe);
    }
    string descompactFile(string fileName, string folderName) {
        const string fileCommand = "rar x ../temporary/" + fileName + " " + folderName;
        FILE* pipe = _popen(fileCommand.c_str(), "r");
        if (!pipe) {
            return "Failed to run command\n";
        }

        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr);
        //if (buffer != "Done") return "Failed to run command\n";
        return buffer;
        _pclose(pipe);
    }

}
