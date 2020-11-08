#include "httpResponse.h"
#include "httpUtils.h"
#include <sstream>

namespace HTTP
{
    Response::Response(ResponseCode responseCode, Version version, const std::vector<Header>& headers, const ResponseContent& content)
        : _responseCode(responseCode), _headers(headers), _content(content), _version(version)
    {
    }

    ResponseCode Response::getResponseCode() const
    {
        return this->_responseCode;
    }

    void Response::setResponseCode(const ResponseCode& code)
    {
        this->_responseCode = code;
    }

    const std::vector<Header> Response::getHeaders() const
    {
        return this->_headers;
    }

    std::string Response::toResponseMessageStr()
    {
        std::ostringstream oss;
        oss << Utils::toString(this->_version) << " " << Utils::toString(this->_responseCode) << "\r\n";
        for (const Header& h : _headers)
        {
            oss << h.getKey() << ": " << h.getValue() << "\r\n";
        }

        oss << "\r\n";
        oss << (this->_content).getContent();

        std::string result = oss.str();

        return result;
    }

    Response::Response(const std::string& response)
    {
        std::vector<std::string> segments = Utils::split(response, std::string(LINE_END) + std::string(LINE_END));

        std::string headerSegment = segments[0];
        segments.erase(segments.begin());

        ResponseContent content;
        content.setContent(Utils::concat(segments));

        std::vector<std::string> headerLines = Utils::split(headerSegment, std::string(LINE_END));

        const std::string& responseCodeLine = headerLines[0];

        std::vector<std::string> responseCodeSegments = Utils::split(responseCodeLine, " ");

        Version version = Utils::versionFromString(responseCodeSegments[0]);
        int responseCode = std::stoi(responseCodeSegments[1]);

        headerLines.erase(headerLines.begin());

        std::vector<Header> headers;

        Header contentType("Content-Type", "");

        for (const std::string& line : headerLines)
        {
            const Header header(line);
            headers.push_back(header);
            if (header.getKey() == "Content-Type")
            {
                contentType.setValue(header.getValue());
            }
        }

        content.setExtens(Utils::extendFromString(contentType.getValue()));

        this->_responseCode = ResponseCode(responseCode);
        this->_version = version;
        this->_headers = headers;
        this->_content = content;
    }

}
