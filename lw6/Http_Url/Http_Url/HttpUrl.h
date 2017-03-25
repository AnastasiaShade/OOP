#pragma once
#include "stdafx.h"
#include "UrlParsingError.h"

const unsigned short MIN_PORT = 1;
const unsigned short MAX_PORT = 65535;
const unsigned short DEFAULT_HTTP_PORT = 80;
const unsigned short DEFAULT_HTTPS_PORT = 443;

enum Protocol
{
	HTTP = 80,
	HTTPS = 443
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol);
	CHttpUrl(std::string const& domain, std::string const& document);

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
	static Protocol ParseProtocol(std::string const& url);
	static std::string ParseDomain(std::string const& url);
	static unsigned short ParsePort(std::string const& url);
	static std::string ParseDocument(std::string const& url);
};

std::string ProtocolToString(Protocol const& protocol);
std::string PortToString(unsigned short const& port, Protocol protocol);