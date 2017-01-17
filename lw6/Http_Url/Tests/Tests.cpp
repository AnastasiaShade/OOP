#include "stdafx.h"
#include <string>
#include <algorithm>
#include "../Http_Url/HttpUrl.h"
#include "../Http_Url/UrlParsingError.h"

using namespace std;

void URLVerification(CHttpUrl &url, const std::string &expectedURL, const Protocol expectedProtocol,
	const std::string &expectedDomain, const unsigned short expectedPort, const std::string &expectedDocument)
{
	BOOST_CHECK_EQUAL(url.GetURL(), expectedURL);
	BOOST_CHECK_EQUAL(url.GetProtocol(), expectedProtocol);
	BOOST_CHECK_EQUAL(url.GetDomain(), expectedDomain);
	BOOST_CHECK_EQUAL(url.GetPort(), expectedPort);
	BOOST_CHECK_EQUAL(url.GetDocument(), expectedDocument);
}

BOOST_AUTO_TEST_SUITE(Http_url)

	BOOST_AUTO_TEST_SUITE(throw_exception_if_it_contains_invalid)

		BOOST_AUTO_TEST_CASE(protocol_name)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("htp://domain.ru"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("htttps://domain.ru"), CUrlParsingError);
		}

		BOOST_AUTO_TEST_CASE(separator_between_protocol_and_domain)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http:/domain.ru"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("https//domain.ru"), CUrlParsingError);
		}

		BOOST_AUTO_TEST_CASE(domain)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http://do*ma%in.ru"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("https://domain . ru"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("https://"), CUrlParsingError);
		}

		BOOST_AUTO_TEST_CASE(port)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http://domain.ru:/"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("https://domain.ru:a"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("https://domain.ru:0"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("http://domain.ru:65536/"), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("http://domain.ru:100000000000000000000/"), CUrlParsingError);
		}

		BOOST_AUTO_TEST_CASE(document)
		{
			BOOST_REQUIRE_THROW(CHttpUrl url("http://domain.ru/ "), CUrlParsingError);
			BOOST_REQUIRE_THROW(CHttpUrl url("https://domain.ru/&document"), CUrlParsingError);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_be_constructed_from)

		struct ExpectedURLParts
		{
			Protocol expectedHttpProtocol = HTTP;
			Protocol expectedHttpsProtocol = HTTPS;
			std::string expectedDomain = "domain.ru";
			unsigned short expectedDefaultHttpPort = 80;
			unsigned short expectedDefaultHttpsPort = 443;
			std::string expectedDocument = "/document";
		};

		BOOST_FIXTURE_TEST_SUITE(various_parts_such_as, ExpectedURLParts)

			BOOST_AUTO_TEST_CASE(domain_and_document)
			{
				std::string domain = "domain.ru";
				std::string document = "document";
				std::string expectedUrl = "http://domain.ru/document";
				CHttpUrl url(domain, document);
				URLVerification(url, expectedUrl, expectedHttpProtocol, expectedDomain, expectedDefaultHttpPort, expectedDocument);
			}

			BOOST_AUTO_TEST_CASE(protocol_domain_and_document)
			{
				std::string domain = "domain.ru";
				std::string document = "document";
				Protocol protocol = HTTPS;
				std::string expectedURL("https://domain.ru/document");
				CHttpUrl url(domain, document, protocol);
				URLVerification(url, expectedURL, expectedHttpsProtocol, expectedDomain, expectedDefaultHttpsPort, expectedDocument);
			}

			BOOST_AUTO_TEST_CASE(domain_document_protocol_and_valid_port)
			{
				std::string domain = "domain.ru";
				std::string document = "document";
				Protocol protocol = HTTPS;
				unsigned short port = 80;
				CHttpUrl url(domain, document, protocol, port);
				std::string expectedUrl = "https://domain.ru:80/document";
				URLVerification(url, expectedUrl, expectedHttpsProtocol, expectedDomain, expectedDefaultHttpPort, expectedDocument);
			}

		BOOST_AUTO_TEST_SUITE_END()

		BOOST_FIXTURE_TEST_SUITE(string_with, ExpectedURLParts)

			BOOST_AUTO_TEST_CASE(http_protocol_domain_and_empty_document)
			{
				std::string urlStr = "http://domain.ru/";
				std::string expectedURL = "http://domain.ru/";
				std::string expectedDocument = "/";
				CHttpUrl url(urlStr);
				URLVerification(url, expectedURL, expectedHttpProtocol, expectedDomain, expectedDefaultHttpPort, expectedDocument);
			}

			BOOST_AUTO_TEST_CASE(https_protocol_domain_and_empty_document) //
			{
				std::string urlStr = "https://domain.ru";
				std::string expectedURL = "https://domain.ru/";
				std::string expectedDocument = "/";
				CHttpUrl url(urlStr);
				URLVerification(url, expectedURL, expectedHttpsProtocol, expectedDomain, expectedDefaultHttpsPort, expectedDocument);
			}

			BOOST_AUTO_TEST_CASE(protocol_domain_min_port_and_document)
			{
				std::string urlStr = "http://domain.ru:1/document";
				std::string expectedURL = "http://domain.ru:1/document";
				unsigned short expectedNonDefaultPort = 1;
				CHttpUrl url(urlStr);
				URLVerification(url, expectedURL, expectedHttpProtocol, expectedDomain, expectedNonDefaultPort, expectedDocument);
			}

			BOOST_AUTO_TEST_CASE(protocol_domain_max_port_and_document)
			{
				std::string urlStr = "http://domain.ru:65535/document";
				std::string expectedURL = "http://domain.ru:65535/document";
				unsigned short expectedNonDefaultPort = 65535;
				CHttpUrl url(urlStr);
				URLVerification(url, expectedURL, expectedHttpProtocol, expectedDomain, expectedNonDefaultPort, expectedDocument);
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()