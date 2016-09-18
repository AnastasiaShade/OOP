#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n" << "Usage: copyfile.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}
	// Объявили переменную типа ifstream (input file stream, поток для чтения из файла), проинициализировав его именем входного файла
	ifstream input(argv[1]);
	// вызываем метод is_open() у объекта input, который вернет true, если файл был открыт
	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}
	// создали поток для записи в выходной файл
	ofstream output(argv[2]);
	if (!output.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}
	string searchString = argv[3], replaceString = argv[4], fileString, tempString;
	bool findStr = false;
	if (searchString.length() == 0)
	{
		cout << "Search string shouldn't be empty\n";
		return 1;
	}
	// построчно считываем файл
	while (getline(input, fileString))
	{
		//поиск подстроки в строке
		tempString = "";
		size_t pos = 0, startPos = 0, lenght = 0;
		while ((pos = fileString.find(searchString, pos)) != string::npos)
		{
			tempString += fileString.substr(startPos, pos - startPos) + replaceString;
			pos += searchString.length();
			startPos = pos;
			if ((pos != 0) && !findStr)
				findStr = true;
		}
		//вывод строки в файл
		if (!findStr)
			output << fileString << "\n";
		else
		{
			tempString += fileString.substr(startPos, string::npos - startPos);
			output << tempString << "\n";
		}
	}
	if (!output.flush()) // Если не удалось сбросить данные на диск
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}
	else
		if (!findStr)
			cout << "The string " << searchString << " has'n been found\n";

	return 0;
}
