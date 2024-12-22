#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>

using namespace std;

namespace MainFrame {
	const char* compactRegister (string filePath, bool deleteOrigin);
	static vector<string> split(const string& str, const string& delimiter);
	static string fixFilePath(string filePath);
	static string getFileName(string fixedPath);
}