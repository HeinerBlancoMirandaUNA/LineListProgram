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
protected:
	FileLoadAndSave();
	~FileLoadAndSave();
	LinkedList<string> FileContents;
	string fileID, makeNew;

	int readFile(string thisFile);
	void saveToFile(string thisFile, LinkedList<string>& Data);

private:
	void resetData();
};

