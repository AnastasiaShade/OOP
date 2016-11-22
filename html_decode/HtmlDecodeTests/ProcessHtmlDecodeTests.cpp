#include "stdafx.h"
#include "..\html_decode\ProcessHtmlDecode.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(ProcessHtmlDecode_function)
	BOOST_AUTO_TEST_CASE(make_test_with_replace)
	{
		string html = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
		string decodedHtml = HtmlDecode(html);
		BOOST_CHECK(StringsAreEqual(decodedHtml, "Cat <says> \"Meow\". M&M's"));
	}
	BOOST_AUTO_TEST_CASE(make_test_without_replace)
	{
		string html = "Cat says <Meow>";
		string decodedHtml = HtmlDecode(html);
		BOOST_CHECK(StringsAreEqual(decodedHtml, "Cat says <Meow>"));
	}
	BOOST_AUTO_TEST_CASE(make_test_with_empty_input_string)
	{
		string html = "";
		string decodedHtml = HtmlDecode(html);
		BOOST_CHECK(StringsAreEqual(decodedHtml, ""));
	}
	BOOST_AUTO_TEST_CASE(make_test_with_empty_input_string2)
	{
		string html = "aa &amp;amp; bb";
		string decodedHtml = HtmlDecode(html);
		BOOST_CHECK(StringsAreEqual(decodedHtml, "aa &amp; bb"));
	}

BOOST_AUTO_TEST_SUITE_END()
