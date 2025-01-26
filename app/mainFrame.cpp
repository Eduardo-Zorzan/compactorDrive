#include "mainFrame.h"
#include "storage.h"
#include "compacter.h"
#include <unordered_map>


namespace MainFrame {
	int resultDecompression;
	static vector<string> split(const string& str, const string& delimiter) { //function to split string in vector
		regex regex(delimiter);
		sregex_token_iterator it(str.begin(), str.end(), regex, -1);
		return { it, {} };
	}

	static string fixFilePath(string filePath) { // adjust the file path string origined by windows explorer API to run winrar commands
		string fixedFilePath = "";
		for (const auto& character : filePath) {
			if (character == '\\') fixedFilePath += "/";
			else if (character == '\"') continue;
			else fixedFilePath += character;
		}
		return fixedFilePath;
	}

	static string defineImage(string typeFile) { //define what icon shows depending on type file
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

	static vector<string> getFileName(string fixedPath) { //get file name from full path
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

	const char* compactRegister (vector<string> filePath, bool deleteOrigin) {//run the compress function winrar and the delete function from storage
		vector<string> fixedFilePath;
		vector<string> fileName;
		for (const auto& path : filePath) {
			string fixed = fixFilePath(path);
			vector<string> treatedFileName = getFileName(fixed);
			string fileNameGlobal = treatedFileName[0];
			string typeFile = treatedFileName[1];
			string nameImage = defineImage(typeFile);
			string data = fileNameGlobal + "     " + fixed + "     " + nameImage + "     " + fileNameGlobal + ".rar";
			string resultStorage = storage::putFiles(data);
			if (resultStorage != "File name already storaged") {
				fixedFilePath.push_back(fixed);
				fileName.push_back(fileNameGlobal);
			}
		}
		if (fixedFilePath.size() > 0) Compactor::StartCompression(fixedFilePath, fileName, deleteOrigin);
		else return "r"; //review this shit, return isn't working
	}

	vector<int> checkProcessing() {//check if the second thread processor finished the process
		string checked = Compactor::checkProcess();
		vector<string> checkErrorInFormatation = split(checked, "\b");
		if (checked != "") {
			vector<string> treatedCheckedString = split(checkErrorInFormatation[size(checkErrorInFormatation) - 1], " ");
			vector<int> treatedCheckedInt = { stoi(treatedCheckedString[0]), stoi(treatedCheckedString[1]) };
			return treatedCheckedInt;
		}
		return { -1 };
	}

	string descompressDeleteRegister(string filePath, vector<string> listToDescompress) {//run the descompress function and the delete function from storage
		string fixedPath = fixFilePath(filePath);
		for (const auto& fileName : listToDescompress) {
			storage::deleteFiles(fileName);
		}
		Compactor::StartDecompression(fixedPath, listToDescompress);
		return " ";
	}

	string delteFileAndRegister(vector<string> filesToDelete) {//run the delete function in compressed files and in the storage
		for (const auto& fileName : filesToDelete) {
			if (Compactor::deleteFile("../temporary/" + fileName + ".rar") == "Failed to run command\n") {
				return "something isn't right";
			}
			cout << fileName << endl;
			storage::deleteFiles(fileName);
		}
		return " ";
	}

}