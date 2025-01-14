#include "compacter.h"
#include <cstdio>
#include <sstream>
#include "imgui.h"
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>


using namespace std;

std::atomic<bool> isRunning(false);      // Flag to track if the thread is active
std::mutex outputMutex;                  // Mutex to protect shared output
std::string threadOutput;                // Shared output from the thread

namespace Compactor { 

    static vector<string> split(const string& str, const string& delimiter) {
        regex regex(delimiter);
        sregex_token_iterator it(str.begin(), str.end(), regex, -1);
        return { it, {} };
    }

    void compactFile(const std::string& filePath, const std::string& fileName)
    {
        std::string fileCommand = "rar a -m5 -s -ep ../temporary/" + fileName + " " + filePath;
        FILE* pipe = _popen(fileCommand.c_str(), "r");
        if (!pipe)
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            threadOutput = "Failed to run command\n";
            isRunning = false;
            return;
        }

        char buffer[128];
        std::ostringstream output;
        std::string progress = " ";
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {

            {
                output << buffer;
                // Example: Display progress
                std::string line(buffer);
                cout << line;
                if (line.find("%") != std::string::npos)
                {
                    size_t percentPos = line.find('%');
                    size_t startPos = line.find_last_of(" ", percentPos) + 1;
                    if (startPos < percentPos)
                    {
                        progress = line.substr(startPos, percentPos - startPos);
                        try
                        {
                            threadOutput = progress;
                            std::lock_guard<std::mutex> lock(outputMutex);

                            // Update a progress bar, e.g., pass progressValue to an ImGui widget
                        }
                        catch (...)
                        {
                            // Handle parsing error
                        }
                    }
                }
            }
        }
        _pclose(pipe);
        {
            isRunning = false;
        }
    }

    string checkProcess() {
        if (isRunning) {
            return threadOutput;
        }
        return "";
    }

    void StartCompression(const std::string& filePath, const std::string& fileName)
    {
        if (isRunning) {
            return;
        }// Prevent multiple threads from starting
        isRunning = true;
        std::thread compressionThread(compactFile, filePath, fileName);
        compressionThread.detach(); // Detach the thread to let it run independently
        return;
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
