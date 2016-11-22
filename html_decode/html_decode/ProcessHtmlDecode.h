#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

string Replace(string const& html, string const& searchString, string const& replaceString);
string HtmlDecode(string const& html);