#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool AreFilesOpened(ifstream &input, ofstream &output, string inputFileName, string outputFileName);
string Replace(string fileLine, string searchString, string replaceString, ofstream &output);
bool IsSearchStringReplaced(ifstream &input, ofstream &output, string search, string replace);

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n" << "Usage: copyfile.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	ifstream input(argv[1]);
	ofstream output(argv[2]);
	if (!AreFilesOpened(input, output, argv[1], argv[2]))
		return 1;

	string searchString = argv[3], replaceString = argv[4];
	if (searchString.length() == 0)
	{
		cout << "Search string shouldn't be empty\n";
		return 1;
	}
	if (!IsSearchStringReplaced(input, output, searchString, replaceString))
		cout << "Search string '" << searchString << "' hasn't been found.\n";

	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	return 0;
}

bool AreFilesOpened(ifstream &input, ofstream &output, string inputFileName, string outputFileName)
{
	if (!input.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}
	if (!output.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing\n";
		return false;
	}
	return true;
}

string Replace(string fileLine, string searchString, string replaceString, ofstream &output)
{
	string newString = "";
	size_t searchPosition = 0, replacePosition = fileLine.find(searchString);
	while (replacePosition != string::npos)
	{
		newString.append(fileLine, searchPosition, replacePosition - searchPosition);
		newString += replaceString;
		searchPosition = replacePosition + searchString.length();
		replacePosition = fileLine.find(searchString, searchPosition);
	}
	output << newString.append(fileLine, searchPosition, replacePosition - searchPosition) << "\n";
	return newString;
}

bool IsSearchStringReplaced(ifstream &input, ofstream &output, string search, string replace)
{
	string fileLine;
	bool isSearchStringFound = false;
	while (getline(input, fileLine))
		if (fileLine != Replace(fileLine, search, replace, output))
			isSearchStringFound = true;
	return isSearchStringFound;
}
