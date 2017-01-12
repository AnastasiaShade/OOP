#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include "ProcessHtmlDecode.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n" << "Usage: html_decode.exe <input file>\n";
		return 1;
	}

	ifstream input(argv[1]);
	if (!input.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}

	string html, decodedHtml;
	while (getline(input, html))
	{
		decodedHtml = HtmlDecode(html);
		cout << decodedHtml << "\n";
	}
	
	return 0;
}
