// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace web::json;
using namespace concurrency::streams;       // Asynchronous streams

pplx::task<void> HttpGetAsync()
{
	http_client client( U( "https://github.com/Microsoft/cpprestsdk/wiki/How-to-build-for-Windows" ) );
	return client.request( methods::GET)
	.then( [] ( http_response response ) -> pplx::task<std::wstring>
	{
		std::wostringstream stream;
		stream.str(std::wstring());
		stream << U( "Content Type : " ) << response.headers().content_type() << std::endl;
		stream << U( "Content Length : ") << response.headers().content_length() << U("bytes") << std::endl;
		std::wcout << stream.str();

		return response.extract_string();
	})
	.then( [] ( pplx::task<std::wstring> previousTask )
	{
		std::wcout << previousTask.get().c_str() << std::endl;
	});
}

int main()
{
	try
	{
		HttpGetAsync().wait();
	}
	catch ( const std::exception &e )
	{
		printf("Error exception:%s\n", e.what());
	}

	getchar();
    return 0;
}

