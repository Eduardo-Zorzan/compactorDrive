#include "mainFrame.h"
#include "storage.h"
#include "compacter.h"
#include <unordered_map>


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

	static string defineImage(string typeFile) {
		transform(typeFile.begin(), typeFile.end(), typeFile.begin(), //Transform typeFile in Lowercase
		[](unsigned char c) { return std::tolower(c); });
		unordered_map<string, string> hashImages = {
			{"jpg", "image.png"},
			{"jpeg", "image.png"},
			{"png", "image.png"},
			{"gif", "image.png"},
			{"bmp", "image.png"},
			{"tiff", "image.png"},
			{"svg", "image.png"},
			{"webp", "image.png"},
			{"pdf", "pdf.png"},
			{"doc", "word.png"},
			{"docx", "word.png"},
			{"dot", "word.png"},
			{"dotx", "word.png"},
			{"dotm", "word.png"},
			{"docm", "word.png"},
			{"rtf", "word.png"},
			{"xls", "excel.png"},
			{"xlsb", "excel.png"},
			{"xlsm", "excel.png"},
			{"xlsx", "excel.png"},
			{"xlt", "excel.png"},
			{"xltm", "excel.png"},
			{"xltx", "excel.png"},
			{"xlw", "excel.png"},
			{"xlam", "excel.png"},
			{"xla", "excel.png"},
			{" ", "folder.png"},
		};
		if (hashImages.find(typeFile) != hashImages.end()) {
			return hashImages[typeFile];
		}
		return "unknown.png";
	}

	static vector<string> getFileName(string fixedPath) {
		string fileNameGlobal = "";
		string folderPath;
		string typeFile = "";
		int acumulator = 0;
		vector<string> splitedFileName = split(fixedPath, "/");
		for (const auto& folder : splitedFileName) {
			if (acumulator != splitedFileName.size() - 1) {
				folderPath += folder + "/";
			}
			else {
				vector<string> splitedTypeFile = split(folder, "");
				bool pastDot = false;
				for (const auto& subString : splitedTypeFile) {
					if (subString != "." && !pastDot) {
						fileNameGlobal = fileNameGlobal + subString;
					}
					else if (subString != "." && pastDot) {
						typeFile = typeFile + subString;
					}
					else {
						pastDot = true;
					}
				}
			}
			acumulator++;
		}
		if (typeFile == "") typeFile = " ";
		vector<string> returnVector = {fileNameGlobal, typeFile};
		return returnVector;
	}

	const char* compactRegister (string filePath, bool deleteOrigin) {
		string fixedFilePath = fixFilePath(filePath);
		vector<string> treatedFileName = getFileName(fixedFilePath);
		string fileNameGlobal = treatedFileName[0];
		string typeFile = treatedFileName[1];
		string nameImage = defineImage(typeFile);
		string data = fileNameGlobal + " " + fixedFilePath + " " + nameImage + " " + fileNameGlobal + ".rar";
		string resultStorage = storage::putFiles(data);
		if (resultStorage != "File name already storaged") {
			 Compactor::StartCompression(fixedFilePath, fileNameGlobal);
		}
		if (deleteOrigin) Compactor::deleteFile(fixedFilePath);
		else return "r"; //review this shit, return isn't working
	}

	int checkProcessing() {
		string checked = Compactor::checkProcess();
		if (checked != "") return stoi(checked);
		return 0;
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