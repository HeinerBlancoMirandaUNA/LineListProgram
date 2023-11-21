#include "file_load_and_save.h"

FileLoadAndSave::FileLoadAndSave() {
	resetData();
	fileID = "!!!#%^_**v2";
	makeNew = "$new$";
}

FileLoadAndSave::~FileLoadAndSave() {

}

void FileLoadAndSave::resetData() {
	FileContents.~LinkedList();
}

int FileLoadAndSave::readFile(string thisFile) {
	resetData();
	ifstream File(thisFile.c_str());

	if (File.fail()) {
		File.close();
		return -1;
	}

	string currentLine;
	getline(File, currentLine);
	if (currentLine!= fileID) {
		return -2;
	}
	
	FileContents.go(First);
	while (getline(File, currentLine)) {
		FileContents.add(Last,currentLine);
	}

	File.close();
	return 0;
}

void FileLoadAndSave::saveToFile(string thisFile, LinkedList<string>& Data) {

	ofstream File(thisFile.c_str());

	string currentLine;

	Data.go(First);
	while (Data.isValid()) {
		currentLine = Data.getItem();
		File << currentLine << std::endl;
		Data.del(First);
	}

	File.close();

}
