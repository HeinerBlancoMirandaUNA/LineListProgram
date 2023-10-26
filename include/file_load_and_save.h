#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::ifstream; 
using std::ofstream;


class FileLoadAndSave
{
public:
	FileLoadAndSave();
	~FileLoadAndSave();
	string filename;
	vector<string> fileContents;

	bool fileIsLoaded();
	void readFile(string thisFile);
	void saveToFile(string thisFile, vector<string> data);

private:
	bool fileReady;
	void resetData();
};

