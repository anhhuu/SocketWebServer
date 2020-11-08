#pragma once
#include <string>
#include "httpUtils.h"

namespace HTTP
{
	class ResponseContent
	{
	private:
		HTTP::Extensions _extens;
		std::string _content;

	public:
		ResponseContent()
			: _extens(HTTP::Extensions::HTML), _content("")
		{
		}

		ResponseContent(HTTP::Extensions extend, std::string content)
			:_extens(extend), _content(content)
		{
		}

		std::string getContentType();
		std::string getContent();

		void setContent(const std::string& resource);
		void setExtens(HTTP::Extensions extens);

	};
}
