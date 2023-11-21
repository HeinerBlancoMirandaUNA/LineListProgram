#include "file_load_and_save.h"

FileLoadAndSave::FileLoadAndSave() {
	resetData();
	fileID = "!!!#%^_**v2";
	makeNew = "$new$";
}

FileLoadAndSave::~FileLoadAndSave() {

}

void FileLoadAndSave::resetData() {
	FileContents.~DoublyLinkedList();
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
	
	while (getline(File, currentLine)) {
		FileContents.add(Last,currentLine);
	}

	FileContents.go(First);
	while (FileContents.isValid()) {
		std::cout << FileContents.getItem() << "\n";
		FileContents.go(Next);
	}

	File.close();
	return 0;
}

void FileLoadAndSave::saveToFile(string thisFile, DoublyLinkedList<string>& Data) {

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
