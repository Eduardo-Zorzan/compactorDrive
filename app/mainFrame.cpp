#include "mainFrame.h"
#include "storage.h"
#include "compacter.h"

namespace MainFrame {
	static vector<string> split(const string& str, const string& delimiter) {
		regex regex(delimiter);
		sregex_token_iterator it(str.begin(), str.end(), regex, -1);
		return { it, {} };
	}

	static string fixFilePath(string filePath) {
		string fixedFilePath = "";
		for (const auto& character : filePath) {
			if (character == '\\') fixedFilePath += "/";
			else if (character == '\"') continue;
			else fixedFilePath += character;
		}
		return fixedFilePath;
	}

	static string getFileName(string fixedPath) {
		string fileNameGlobal = "";
		string folderPath;
		int acumulator = 0;
		vector<string> splitedFileName = split(fixedPath, "/");
		for (const auto& folder : splitedFileName) {
			if (acumulator != splitedFileName.size() - 1) {
				folderPath += folder + "/";
			}
			else {
				vector<string> splitedTypeFile = split(folder, "");
				for (const auto& test : splitedTypeFile) {
					if (test != ".") {
						fileNameGlobal = fileNameGlobal + test;
					}
					else break;
				}
			}
			acumulator++;
		}
		return fileNameGlobal;
	}

	const char* compactRegister (string filePath, bool deleteOrigin) {
		string nameImage = "asdf.png";
		string fixedFilePath = fixFilePath(filePath);
		string fileNameGlobal = getFileName(fixedFilePath);
		string data = fileNameGlobal + " " + fixedFilePath + " " + nameImage + " " + fileNameGlobal + ".rar";
		string resultStorage = storage::putFiles(data);
		if (resultStorage != "File name already storaged") {
			string fileName = Compactor::compactFile(fixedFilePath, fileNameGlobal);
		}
		if (deleteOrigin) Compactor::deleteFile(fixedFilePath);
		else return "r"; //review this shit, return isn't working
	}

	string descompressDeleteRegister(string filePath, vector<string> listToDescompress) {
		string fixedPath = fixFilePath(filePath);
		for (const auto& fileName : listToDescompress) {
			if (Compactor::descompactFile(fileName, fixedPath) == "Failed to run command\n") {
				return "something isn't right";
			}
			storage::deleteFiles(fileName);
		}
		return " ";
	}

	string delteFileAndRegister(vector<string> filesToDelete) {
		for (const auto& fileName : filesToDelete) {
			if (Compactor::deleteFile("../temporary/" + fileName + ".rar") == "Failed to run command\n") {
				return "something isn't right";
			}
			storage::deleteFiles(fileName);
		}
		return " ";
	}

}