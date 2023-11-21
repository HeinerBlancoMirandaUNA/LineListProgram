#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "doubly_linked_list.h"
using std::string;
using std::ifstream; 
using std::ofstream;
using std::to_string;

class FileLoadAndSave
{
public:
	FileLoadAndSave();
	~FileLoadAndSave();
	DoublyLinkedList<string> FileContents;
	string fileID, makeNew;

	int readFile(string thisFile);
	void saveToFile(string thisFile, DoublyLinkedList<string>& Data);

private:
	void resetData();
};

