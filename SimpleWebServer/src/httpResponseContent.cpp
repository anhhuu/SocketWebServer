#include "httpResponseContent.h"
namespace HTTP
{
    std::string ResponseContent::getContentType()
    {
        if (_extens == Extensions::CSS)
            return "text/css";
        if (_extens == Extensions::HTML)
            return "text/html";
        if (_extens == Extensions::JS)
            return "text/javascript";
        if (_extens == Extensions::JPEG)
            return "image/jpeg";
        if (_extens == Extensions::PNG)
            return "image/png";
        if (_extens == Extensions::JPG)
            return "image/jpg";
        if (_extens == Extensions::ICO)
            return "image/x-icon";
        if (_extens == Extensions::TTF)
            return "font/ttf";
    }

    std::string ResponseContent::getContent()
    {
        return _content;
    }

    void ResponseContent::setContent(const std::string& resource)
    {
        _content = resource;
    }

    void ResponseContent::setExtens(HTTP::Extensions extens)
    {
        _extens = extens;
    }
}
