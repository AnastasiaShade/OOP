#include "stdafx.h"
#include "HttpUrl.h"


CHttpUrl::CHttpUrl(std::string const& url)
{
	ParseUrl(url);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document,
	Protocol protocol, unsigned short port)
	: m_domain(GetDomain(domain))
	, m_document(GetDocument(document))
	, m_protocol(protocol)
{
	if (port >= MIN_PORT && port <= MAX_PORT)
	{
		m_port = port;
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: m_protocol(protocol)
	, m_domain(GetDomain(domain))
	, m_document(GetDocument(document))
{
	m_port = (m_protocol == HTTP) ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document)
	: m_protocol(HTTP)
	, m_port(DEFAULT_HTTP_PORT)
	, m_domain(GetDomain(domain))
	, m_document(GetDocument(document))
{
}

std::string CHttpUrl::GetURL()const
{
	return ProtocolToString(m_protocol) + "://" + m_domain
		+ PortToString(m_port, m_protocol) + m_document;
}

Protocol CHttpUrl::GetProtocol()const
{
	return m_protocol;
}

std::string CHttpUrl::GetDomain()const
{
	return m_domain;
}

unsigned short CHttpUrl::GetPort()const
{
	return m_port;
}

std::string CHttpUrl::GetDocument()const
{
	return m_document;
}

void CHttpUrl::ParseUrl(std::string const& url)
{
	std::string urlCopy = url;
	m_protocol = GetProtocol(urlCopy);
	size_t domainBegining = url.find("://") + 3;
	urlCopy = urlCopy.substr(domainBegining);
	m_domain = GetDomain(urlCopy);
	if (urlCopy.find(':') != std::string::npos)
	{
		size_t portBeginning = urlCopy.find(":") + 1;
		urlCopy = urlCopy.substr(portBeginning);
		m_port = GetPort(urlCopy);
	}
	else
	{
		m_port = (m_protocol == HTTP) ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT;
	}
	size_t documentBeginning = urlCopy.find('/');
	if (documentBeginning == std::string::npos)
	{
		m_document = "/";
	}
	else
	{
		urlCopy = urlCopy.substr(documentBeginning);
		m_document = GetDocument(urlCopy);
	}
}

Protocol CHttpUrl::GetProtocol(std::string const& url)
{
	size_t protocolEnd = url.find("://");

	if (protocolEnd == std::string::npos)
	{
		throw CUrlParsingError("Invalid url protocol");
	}

	std::string protocolName = url.substr(0, protocolEnd);
	std::transform(protocolName.begin(), protocolName.end(), protocolName.begin(), ::tolower);

	Protocol protocol;
	if (protocolName != "http" && protocolName != "https")
	{
		throw CUrlParsingError("Invalid url protocol");
	}
	protocol = (protocolName == "http") ? HTTP : HTTPS;
	return protocol;
}

std::string CHttpUrl::GetDomain(std::string const& url)
{
	size_t domainEnd = url.find(":");

	if (domainEnd == std::string::npos)
	{
		domainEnd = url.find("/");
	}

	std::string domain = url.substr(0, domainEnd);
	if (domain.empty())
	{
		throw CUrlParsingError("Domain should not be empty");
	}
	auto HasInvalidChars = [&](char ch)
	{
		return ((!isalpha(ch)) && (!isdigit(ch)) && (ch != '.'));
	};
	if (any_of(domain.begin(), domain.end(), HasInvalidChars))
	{
		throw CUrlParsingError("Domain can only contain letters, numbers, and dots");
	}
	return domain;
}

unsigned short CHttpUrl::GetPort(std::string const& url)
{
	unsigned short port;
	size_t protocolEnd = url.find("/");
	std::string portStr = url.substr(0, protocolEnd);
	try
	{
		int userPort = stoi(portStr);
		if (userPort < MIN_PORT || userPort > MAX_PORT)
		{
			throw CUrlParsingError("Port should be from " + std::to_string(MIN_PORT) + " to " + std::to_string(MAX_PORT));
		}
		port = static_cast<unsigned short>(userPort);
	}
	catch (const std::invalid_argument &)
	{
		throw CUrlParsingError("Invalid port");
	}
	catch (const std::out_of_range &)
	{
		throw CUrlParsingError("Port should be from " + std::to_string(MIN_PORT) + " to " + std::to_string(MAX_PORT));
	}

	return port;
}

std::string CHttpUrl::GetDocument(std::string const& url)
{
	std::string document = url;
	if (document[0] != '/')
	{
		document = "/" + document;
	}
	auto HasInvalidChars = [&](char ch)
	{
		return ((!isalpha(ch)) && (!isdigit(ch)) && (ch != '.') && (ch != '/'));
	};
	if (any_of(document.begin(), document.end(), HasInvalidChars))
	{
		throw CUrlParsingError("Document can only contain letters, numbers, dots and slashes");
	}

	return document;
}

std::string ProtocolToString(Protocol const& protocol)
{
	return (protocol == HTTP) ? "http" : "https";
}

std::string PortToString(unsigned short const& port, Protocol protocol)
{
	if (!(port == DEFAULT_HTTP_PORT && protocol == HTTP) && !(port == DEFAULT_HTTPS_PORT && protocol == HTTPS))
	{
		return (":" + std::to_string(port));
	}
	return "";
}