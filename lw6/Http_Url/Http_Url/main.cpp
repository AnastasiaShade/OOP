#include "stdafx.h"
#include "HttpUrl.h"
#include "UrlParsingError.h"

int main()
{
	std::string url;
	std::cout << "Enter the url: ";
	while (std::getline(std::cin, url))
	{
		try
		{
			CHttpUrl httpUrl(url);
			std::cout << "Full url: " << httpUrl.GetURL() << std::endl;
			std::cout << "Protocol: " << ProtocolToString(httpUrl.GetProtocol()) << std::endl;
			std::cout << "Domain: " << httpUrl.GetDomain() << std::endl;
			std::cout << "Port: " << std::to_string(httpUrl.GetPort()) << std::endl;
			std::cout << "Document: " << httpUrl.GetDocument() << std::endl;
			return 0;
		}
		catch (std::invalid_argument const& err)
		{
			std::cout << "Error: " << err.what() << std::endl;
			return 1;
		}
		std::cout << "Enter the url: ";
	}
}

