#include "stdafx.h"
#include "ProcessHtmlDecode.h"
#include <string>

using namespace std;

string Replace(string const& strForDecoding, string const& searchString, string const& replaceString)
{
	string newString = "";
	size_t searchPosition = 0;
	size_t replacePosition = strForDecoding.find(searchString);
	while (replacePosition != string::npos)
	{
		newString.append(strForDecoding, searchPosition, replacePosition - searchPosition);
		newString += replaceString;
		searchPosition = replacePosition + searchString.length();
		replacePosition = strForDecoding.find(searchString, searchPosition);
	}
	newString.append(strForDecoding, searchPosition);
	return newString;
}

string HtmlDecode(string const& html)
{
	string decodedHtmlString = html;

	map<string, string> elementsForDecoding = { { "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" } };
	
	for (auto i = elementsForDecoding.begin(); i != elementsForDecoding.end(); ++i)
	{
		decodedHtmlString = Replace(decodedHtmlString, i->first, i->second);
	}

	return decodedHtmlString;
}