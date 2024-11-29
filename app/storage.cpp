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

    string getAllFiles() {
        ifstream fin;
        fin.open("../README.txt");

        if (!fin)
        {
            return "Error, file it's taking a shit";
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

        string allFiles = getAllFiles();

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
        string allFiles = getAllFiles();
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
