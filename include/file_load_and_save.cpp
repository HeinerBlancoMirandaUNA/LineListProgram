#include "file_load_and_save.h"

FileLoadAndSave::FileLoadAndSave() {
	resetData();
}

FileLoadAndSave::~FileLoadAndSave() {

}

void FileLoadAndSave::resetData() {
	fileContents.clear();
	filename = "";
	fileReady = false;
}

bool FileLoadAndSave::fileIsLoaded() {

	return fileReady;

}

void FileLoadAndSave::readFile(string thisFile) {
	resetData();
	ifstream File(thisFile.c_str());

	if (File.fail()) {
		File.close();
		return;
	}

	string currentLine;
	while (getline(File, currentLine)) {
		fileContents.push_back(currentLine);
	}

	fileReady = true;
	File.close();
}

void FileLoadAndSave::saveToFile(string thisFile, vector<string> thisData) {

	ofstream File(thisFile.c_str());

	string currentLine;
	while (!thisData.empty()) {
		currentLine = thisData[0];
		File << currentLine << std::endl;
		thisData.erase(thisData.begin());
	}

	File.close();

}
