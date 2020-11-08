#pragma once
#include <string>
#include <vector>

#include "httpHeader.h"
#include "httpResponseContent.h"

namespace HTTP
{
	class Response
	{
	private:
		ResponseCode _responseCode;
		Version _version;
		std::vector<Header> _headers;
		ResponseContent _content;

	public:
		Response(ResponseCode responseCode, Version version, const std::vector<Header>& headers, const ResponseContent& content);
		Response(const std::string& response);

		ResponseCode getResponseCode() const;
		void setResponseCode(const ResponseCode& code);
		
		const std::vector<Header> getHeaders() const;

		std::string toResponseMessageStr();
	};
}
