#include "storage.h";
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>


using namespace std;

namespace storage
{
    static vector<string> split(const string& str, const string& delimiter) {
        regex regex(delimiter);
        sregex_token_iterator it(str.begin(), str.end(), regex, -1);
        return { it, {} };
    }

    static returnObject separator(string rawData) {
        returnObject object;
        vector<string> splitedData = split(rawData, " ");
        object.nameFile = splitedData[0];
        object.nameImage = splitedData[1];
        object.compressFile = splitedData[2];
        return object;
    }

    static vector<returnObject> objectVector(string allRawData) {
        vector<returnObject> vectorObject;
        vector<string> separatedData = split(allRawData, "\n");
        for (const auto& data : separatedData) {
            if (data != "") {
                returnObject dataObject = separator(data);
                vectorObject.push_back(dataObject);
            }
        }
        return vectorObject;
    }

    static string getRawData() {
        ifstream fin;
        fin.open("../README.txt");

        if (!fin)
        {
            cerr << "file it's taking a shit" << endl;
        }
        string lineRead;
        string temporary;

        while (fin) {
            getline(fin, lineRead);
            temporary = lineRead + "\n" + temporary;
        }
        fin.close();
        return temporary;
    }

    vector<returnObject> getAllFiles() {
        string temporary = getRawData();
        vector<returnObject> treatedTemporary = objectVector(temporary);
        return treatedTemporary;
    }

    string getFiles(string nameFile)
    {
        ifstream fin;
        fin.open("../README.txt");

        if (!fin)
        {
            return "Error, file it's taking a shit";
        }

        string line;

        while (fin) {
            getline(fin, line);
            vector<string> name = split(line, " ");
            if (nameFile == name[0]) return line;
        }
        fin.close();
        return "Error: file don't exist";

    }

    string putFiles(string data)
    {
        vector<string> testName = split(data, " ");
        if (getFiles(testName[0]) != "Error: file don't exist") {  
            return "File name already storaged";
        }

        string allFiles = getRawData();

        ofstream fout;
        fout.open("../README.txt");

        if (!fout)
        {
            return "Error, file don't open";
        }

        allFiles = allFiles + data;
        fout << allFiles << endl;
        fout.close();

        return "file writed with success";
    }

    string deleteFiles(string nameFile)
    {
        string allFiles = getRawData();
        string fileToDelete = getFiles(nameFile);
        if (fileToDelete == "Error: file don't exist") {
            return fileToDelete;
        }

        vector<string> splitedFile = split(allFiles, fileToDelete);
        ofstream fout;
        fout.open("../README.txt");

        if (!fout)
        {
            return "Error, file don't open";
        }

        string updatedFile = splitedFile[0] + splitedFile[1];
        fout << updatedFile << endl;
        fout.close();

        return updatedFile;
    }
}
