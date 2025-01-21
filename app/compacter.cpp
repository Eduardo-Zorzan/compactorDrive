#include "compacter.h"
#include <cstdio>
#include <sstream>
#include "imgui.h"
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>


using namespace std;

namespace Compactor { 
    atomic<bool> isRunning(false);      // Flag to track if the thread is active
    mutex outputMutex;                  // Mutex to protect shared output
    string threadOutput = "";                // Shared output from the thread

    static vector<string> split(const string& str, const string& delimiter) {
        regex regex(delimiter);
        sregex_token_iterator it(str.begin(), str.end(), regex, -1);
        return { it, {} };
    }

    void compactFile(const string& filePath, const string& fileName, const bool deleteOrigin)
    {
        string fileCommand = "rar a -m5 -s -ep \"../temporary/" + fileName + "\"" + " \"" + filePath + "\"";
        FILE* pipe = _popen(fileCommand.c_str(), "r");
        if (!pipe)
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            threadOutput = "Failed to run command\n";
            isRunning = false;
            return;
        }
        int accumulator = 0;
        char buffer[128];
        std::ostringstream output;
        std::string progress = " ";
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            {
                output << buffer;
                // Example: Display progress
                std::string line(buffer);
                if (line.find("OK") != string::npos) accumulator++;
                if (line.find("%") != std::string::npos)
                {
                    size_t percentPos = line.find('%');
                    size_t startPos = line.find_last_of(" ", percentPos) + 1;
                    if (startPos < percentPos)
                    {
                        progress = line.substr(startPos, percentPos - startPos);
                        try
                        {
                            threadOutput = progress + " " + to_string(accumulator);
                            std::lock_guard<std::mutex> lock(outputMutex);
                        }
                        catch (string e)
                        {
                            cout << e << endl;
                        }
                    }
                }
            }
        }
        _pclose(pipe);
        {
            isRunning = false;
        }
        if (deleteOrigin) deleteFile(filePath);
    }

    string checkProcess() {
        if (isRunning) {
            return threadOutput;
        }
        return "";
    }

    void StartCompression(const vector<string> filePath, const vector<string> fileName, const bool deleteOrigin)
    {
        int accumulator = 0;
        if (isRunning) {
            return;
        }// Prevent multiple threads from starting
        for (const auto& path: filePath) {
            std::thread compressionThread(compactFile, path, fileName[accumulator], deleteOrigin);
            compressionThread.detach(); // Detach the thread to let it run independently
            accumulator++;
        }
        isRunning = true;
        return;
    }

    void descompactFile(string fileName, string folderName) {
        const string deleteCommand = " & cd \"../temporary/\" & del \"" + fileName + ".rar\"";
        const string fileCommand = "rar x \"../temporary/" + fileName + "\"" + " \"" + folderName + "\"" + deleteCommand;
        FILE* pipe = _popen(fileCommand.c_str(), "r");
        int foundAllOk = 0;
        if (!pipe)
        {
            std::lock_guard<std::mutex> lock(outputMutex);
            threadOutput = "Failed to run command\n";
            isRunning = false;
            return;
        }
        int accumulator = 0;
        char buffer[128];
        std::ostringstream output;
        std::string progress = " ";
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            {
                output << buffer;
                // Example: Display progress
                std::string line(buffer);
                if (line.find("OK") != string::npos) accumulator++;
                if (line.find("ALL OK") != string::npos) foundAllOk = 1;
                if (line.find("%") != string::npos)
                {
                    size_t percentPos = line.find('%');
                    size_t startPos = line.find_last_of(" ", percentPos) + 1;
                    if (startPos < percentPos)
                    {
                        progress = line.substr(startPos, percentPos - startPos);
                        try
                        {
                            threadOutput = progress + " " + to_string(accumulator) + " " + to_string(foundAllOk);
                            std::lock_guard<std::mutex> lock(outputMutex);
                        }
                        catch (string e)
                        {
                            cout << e << endl;
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

    void StartDecompression(const string& fileName, vector<string> listToDescompress)
    {
        if (isRunning) {
            return;
        }// Prevent multiple threads from starting
        for (const auto& filePath : listToDescompress) {
            std::thread decompressionThread(descompactFile, filePath, fileName);
            decompressionThread.detach(); // Detach the thread to let it run independently
        }
        isRunning = true;
        return;
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
                fileCommand = "cd \"" + folderPath + "\" & del \"" + folder + "\"";
            }
            acumulator++;
        }
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
