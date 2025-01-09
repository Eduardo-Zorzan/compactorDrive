#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>
#include <unordered_map>


using namespace std;

namespace MainFrame {
	const char* compactRegister (string filePath, bool deleteOrigin);
	static vector<string> split(const string& str, const string& delimiter);
	static string fixFilePath(string filePath);
	static vector<string> getFileName(string fixedPath);
	string descompressDeleteRegister(string filePath, vector<string> listToDescompress);
	string delteFileAndRegister(vector<string> filesToDelete);
	static string defineImage(string typeFile);
}