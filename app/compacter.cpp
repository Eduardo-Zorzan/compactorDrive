#include "compacter.h"
#include <cstdio>

using namespace std;

namespace Compactor {
    
    static vector<string> split(const string& str, const string& delimiter) {
        regex regex(delimiter);
        sregex_token_iterator it(str.begin(), str.end(), regex, -1);
        return { it, {} };
    }

    string compactFile(string filePath, string fileName) {
        string fileCommand;
        fileCommand = "rar a -m5 -s -ep ../temporary/" + fileName + " " + filePath;
        FILE* pipe = _popen(fileCommand.c_str(), "r");
        if (!pipe) {
            return "Failed to run command\n";        
        }
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr);
        //if(buffer != "Done") return "Failed to run command\n";
        _pclose(pipe);
        return buffer;
    }
    string descompactFile(string fileName, string folderName) {
        const string deleteCommand = " & cd ../temporary/ & del " + fileName + ".rar";
        const string fileCommand = "rar x ../temporary/" + fileName + " " + folderName + deleteCommand;
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

    string deleteFile(string fileName) {
        vector<string> splitedFileName = split(fileName, "/");
        string folderPath;
        string fileCommand;
        int acumulator = 0;
        for (const auto& folder : splitedFileName) {
            if (acumulator != splitedFileName.size() - 1) {
                folderPath += folder + "/";
            }
            else {
                fileCommand = "cd " + folderPath + " & del " + folder;
            }
            acumulator++;
        }
        cout << fileCommand << endl;
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
