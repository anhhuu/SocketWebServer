#include "httpRequest.h"
namespace HTTP
{
	Request::Request(Method method, const std::string& resource, const std::vector<Header>& headers, Version version)
		: _version(version), _method(method), _resource(resource), _headers(headers)
	{
	}

	Request::Request(const std::string& request)
	{
		std::vector<std::string> lines = Utils::split(request, std::string(LINE_END));

		if (lines.size() < 1)
		{
			throw std::runtime_error("HTTP Request ('" + std::string(request) + "') consisted of " + std::to_string(lines.size()) + " lines, should be >= 1.");
		}

		std::vector<std::string> segments = Utils::split(lines[0], " ");

		if (segments.size() != 3)
		{
			throw std::runtime_error("First line of HTTP request ('" + std::string(request) + "') consisted of " + std::to_string(segments.size()) + " space separated segments, should be 3.");
		}

		const Method method = Utils::methodFromString(segments[0]);
		const std::string resource = segments[1];
		const Version version = Utils::versionFromString(segments[2]);

		std::vector<Header> headers;
		std::size_t i;
		for (i = 1; i < lines.size(); i++)
		{
			if (lines[i].size() > 0)
			{
				const Header header(lines[i]);
				headers.push_back(header);
			}

			if (lines[i] == "")
			{
				break;
			}
		}
		std::vector<RequestData> data;
		for (i = i + 1; i < lines.size(); i++)
		{
			if (lines[i].size() > 0)
			{
				const RequestData dat(lines[i]);
				data.push_back(dat);
			}
		}

		this->_headers = headers;
		this->_data = data;
		this->_method = method;
		this->_resource = resource;
		this->_version = version;
	}

	std::string Request::toRequestMessageStr() const
	{
		std::string request;
		request += Utils::toString(this->_method);
		request += " ";
		request += this->_resource;
		request += " ";
		request += Utils::toString(this->_version);
		request += LINE_END;

		for (const Header& header : this->_headers)
		{
			request += header.toHeaderMessageStr();
		}

		request += LINE_END;
		return request;
	}

	std::string Request::getURL(std::string indexURL) const
	{
		return Utils::URLParser(_resource, indexURL);
	}
	Version Request::getVersion() const
	{
		return _version;
	}
	Method Request::getMethod() const
	{
		return _method;
	}
	std::vector<RequestData> Request::getData() const
	{
		return _data;
	}
}
