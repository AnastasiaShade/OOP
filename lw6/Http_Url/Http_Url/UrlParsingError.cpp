#include "stdafx.h"
#include "UrlParsingError.h"


CUrlParsingError::CUrlParsingError(const std::string &err)
	: std::invalid_argument(err)
{
}
