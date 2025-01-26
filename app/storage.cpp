#include "storage.h";


namespace storage
{
    vector<string> split(const string& str, const string& delimiter) { //function to split string in vector
        regex regex(regex_replace(delimiter, regex(R"([.^$|(){}\[\]+*?\\])"), R"(\$&)")); //Escaping special characters for delete work properly
        sregex_token_iterator it(str.begin(), str.end(), regex, -1);
        return { it, {} };
    }

    static returnObject separator(string rawData) { //separate the raw data from storage.txt to an object
        returnObject object;
        vector<string> splitedData = split(rawData, "     ");
        object.nameFile = splitedData[0];
        object.pathFile = splitedData[1];
        object.nameImage = splitedData[2];
        object.compressFile = splitedData[3];
        return object;
    }

    static vector<returnObject> objectVector(string allRawData) { //take the raw data and convert to a vector with the data separated on an object
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

    static string getRawData() { //take raw data from storage.txt
        ifstream fin;
        fin.open("./storage.txt");

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

    vector<returnObject> getAllFiles() {// runs getRawData and obejectVector
        string temporary = getRawData();
        vector<returnObject> treatedTemporary = objectVector(temporary);
        return treatedTemporary;
    }

    string getFiles(string nameFile)// get raw data of one file by nameFile
    {
        ifstream fin;
        fin.open("./storage.txt");

        if (!fin)
        {
            return "Error, file it's taking a shit";
        }

        string line;

        while (fin) {
            getline(fin, line);
            vector<string> name = split(line, "     ");
            if (nameFile == name[0]) return line;
        }
        fin.close();
        return "Error: file don't exist";

    }

    string putFiles(string data) //put files on storage.txt and test if the file it's already in storage.txt
    {
        vector<string> testName = split(data, "     ");
        if (getFiles(testName[0]) != "Error: file don't exist") {  
            return string("File name already storaged");
        }

        string allFiles = getRawData();

        ofstream fout;
        fout.open("./storage.txt");

        if (!fout)
        {
            return string("Error, file don't open");
        }

        allFiles = allFiles + data;
        fout << allFiles << endl;
        fout.close();

        return string("file writed with success");
    }

    string deleteFiles(string nameFile)//delete one file from storage.txt by the file name
    {
        string allFiles = getRawData();
        string fileToDelete = getFiles(nameFile);
        if (fileToDelete == "Error: file don't exist") {
            cerr << fileToDelete + "File .rar don't created" << endl;
        }

        vector<string> splitedFile = split(allFiles, fileToDelete);
        ofstream fout;
        fout.open("./storage.txt");

        if (!fout)
        {
            return "Error, file don't open";
        }
        string updatedFile;
        if (splitedFile.size() > 1) updatedFile = splitedFile[0] + splitedFile[1];
        else updatedFile = splitedFile[0];
        fout << updatedFile << endl;
        fout.close();

        return updatedFile;
    }
}
