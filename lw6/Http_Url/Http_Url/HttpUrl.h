#pragma once
#include "stdafx.h"
#include "UrlParsingError.h"

namespace
{
	const unsigned short MIN_PORT = 1;
	const unsigned short MAX_PORT = 65535;
	const unsigned short DEFAULT_HTTP_PORT = 80;
	const unsigned short DEFAULT_HTTPS_PORT = 443;
}

enum Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document,
		Protocol protocol, unsigned short port);
	CHttpUrl(std::string const& domain, std::string const& document,
		Protocol protocol);
	CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document);
	std::string GetURL()const;
	Protocol GetProtocol()const;
	std::string GetDomain()const;
	unsigned short GetPort()const;
	std::string GetDocument()const;

private:
	Protocol m_protocol;
	std::string m_domain;
	unsigned short m_port;
	std::string m_document;

	void ParseUrl(std::string const& url);
	static Protocol GetProtocol(std::string const& url);
	static std::string GetDomain(std::string const& url);
	static unsigned short GetPort(std::string const& url);
	static std::string GetDocument(std::string const& url);
};

std::string ProtocolToString(Protocol const& protocol);
std::string PortToString(unsigned short const& port, Protocol protocol);