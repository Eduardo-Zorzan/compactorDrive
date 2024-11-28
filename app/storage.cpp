#include "storage.h";
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

namespace storage
{
    void getFiles()
    {
        


    }

    void putFiles()
    {
        ofstream fout;
        fout.open("README.txt");

        if (!fout)
        {
            cerr << "Error, file don't open" << endl;
            return;
        }

        string line;

        cout << "Enter 5 lines of text" << endl;
        int acumulator = 0;
        while (acumulator < 5)
        {
            getline(cin, line);
            fout << line << endl;

            acumulator++;
        }
        fout.close();

        cout << "file writed with success" << endl;
    }

    void deleteFiles()
    {

    }
}
