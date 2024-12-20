#include "compacter.h"
#include <cstdio>

using namespace std;

namespace Compactor {
    string fileNameGlobal;
    static vector<string> split(const string& str, const string& delimiter) {
        regex regex(delimiter);
        sregex_token_iterator it(str.begin(), str.end(), regex, -1);
        return { it, {} };
    }

    string returnFileNameGlobal() {
        return fileNameGlobal;
    }

    string compactFile(string filePath) {
        vector<string> splitedFileName = split(filePath, "/");
        string fileCommand;
        string folderPath;
        int acumulator = 0;
        for (const auto& folder : splitedFileName) {
            if (acumulator != splitedFileName.size() - 1) {
                folderPath += folder + "/";
            }
            else {
                vector<string> splitedTypeFile = split(folder, ".");
                fileNameGlobal = folder;
                cout << splitedTypeFile[0] << endl;
                fileCommand = "rar a -m5 -s -ep ../temporary/" + splitedTypeFile[0] + " " + filePath;
            }
            acumulator++;
        }
        
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
                fileCommand = "cd " + folderPath + " & " + "del " + folder;
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
