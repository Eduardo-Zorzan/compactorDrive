#include "mainFrame.h"
#include "storage.h"
#include "compacter.h"

using namespace std;

namespace MainFrame {
	void compactRegister(string filePath) {
		Compactor::compactFile(filePath);
		string fileName = Compactor::returnFileNameGlobal();
		string nameImage = "asdf.png";
		storage::putFiles(fileName + " " + filePath + " " + nameImage + " " + fileName + ".rar");
	}
}