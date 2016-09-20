#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isFilesOpen(char * argv[], ifstream &input, ofstream &output)
{
	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return false;
	}
	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return false;
	}
	return true;
}

bool isStringFind(ifstream &input, ofstream &output, string search, string replace)
{
	string fileLine, tempLine;
	bool find = false;
	while (getline(input, fileLine))
	{
		tempLine = "";
		size_t pos = 0, startPos = 0;
		while ((pos = fileLine.find(search, pos)) != string::npos)
		{
			tempLine += fileLine.substr(startPos, pos - startPos) + replace;
			pos += search.length();
			startPos = pos;
			if ((pos != 0) && !find)
				find = true;
		}
		if (!find)
			output << fileLine << "\n";
		else
		{
			tempLine += fileLine.substr(startPos, string::npos - startPos);
			output << tempLine << "\n";
		}
	}
	return find;
}

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n" << "Usage: copyfile.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}
	ifstream input(argv[1]);
	ofstream output(argv[2]);
	if (!isFilesOpen(argv, input, output))
		return 1;
	string searchString = argv[3], replaceString = argv[4];
	if (searchString.length() == 0)
	{
		cout << "Search string shouldn't be empty\n";
		return 1;
	}
	bool findStr = isStringFind(input, output, searchString, replaceString);
	if (!output.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	else
		if (!findStr)
			cout << "The string '" << searchString << "' has'n been found\n";

	return 0;
}
