#include "httpUtils.h"

namespace HTTP
{
    std::string Utils::toString(Method method)
    {
        switch (method)
        {
        case Method::GET:
            return "GET";
        case Method::HEAD:
            return "HEAD";
        case Method::POST:
            return "POST";
      /*  case Method::PUT:
            return "PUT";
        case Method::DEL:
            return "DELETE";
        case Method::TRACE:
            return "TRACE";
        case Method::OPTIONS:
            return "OPTIONS";
        case Method::CONNECT:
            return "CONNECT";
        case Method::PATCH:
            return "PATCH";*/
        }
    }

    Method Utils::methodFromString(const std::string& method)
    {
        if (method == toString(Method::GET))
        {
            return Method::GET;
        }
        else if (method == toString(Method::HEAD))
        {
            return Method::HEAD;
        }
        else if (method == toString(Method::POST))
        {
            return Method::POST;
        }
       /* else if (method == toString(Method::PUT))
        {
            return Method::PUT;
        }
        else if (method == toString(Method::DEL))
        {
            return Method::DEL;
        }
        else if (method == toString(Method::TRACE))
        {
            return Method::TRACE;
        }
        else if (method == toString(Method::OPTIONS))
        {
            return Method::OPTIONS;
        }
        else if (method == toString(Method::CONNECT))
        {
            return Method::CONNECT;
        }
        else if (method == toString(Method::PATCH))
        {
            return Method::PATCH;
        }*/
    }

    std::string Utils::toString(Version version)
    {
        switch (version)
        {
        case Version::HTTP_1_0:
            return "HTTP/1.0";

        case Version::HTTP_1_1:
            return "HTTP/1.1";

        case Version::HTTP_2_0:
            return "HTTP/2.0";
        }
    }

    Version Utils::versionFromString(const std::string& version)
    {
        if (version == toString(Version::HTTP_1_0))
        {
            return Version::HTTP_1_0;
        }
        else if (version == toString(Version::HTTP_1_1))
        {
            return Version::HTTP_1_1;
        }
        else if (version == toString(Version::HTTP_2_0))
        {
            return Version::HTTP_2_0;
        }
    }

    std::string Utils::toString(Extensions extend)
    {
        switch (extend)
        {
        case Extensions::HTML:
            return "html";
        case Extensions::JS:
            return "js";
        case Extensions::CSS:
            return "css";
        case Extensions::JPEG:
            return "jpeg";
        case Extensions::JPG:
            return "jpg";
        case Extensions::PNG:
            return "png";
        case Extensions::ICO:
            return "ico";
        case Extensions::TTF:
            return "ttf";
        }
    }

    Extensions Utils::extendFromString(const std::string& extend)
    {
        if (extend == toString(Extensions::HTML))
        {
            return Extensions::HTML;
        }
        else if (extend == toString(Extensions::JS))
        {
            return Extensions::JS;
        }
        else if (extend == toString(Extensions::CSS))
        {
            return Extensions::CSS;
        }
        else if (extend == toString(Extensions::PNG))
        {
            return Extensions::PNG;
        }
        else if (extend == toString(Extensions::JPEG))
        {
            return Extensions::JPEG;
        }
        else if (extend == toString(Extensions::JPG))
        {
            return Extensions::JPG;
        }
        else if (extend == toString(Extensions::ICO))
        {
            return Extensions::ICO;
        }
        else if (extend == toString(Extensions::TTF))
        {
            return Extensions::TTF;
        }
    }

    std::string Utils::toString(ResponseCode code)
    {
        switch (code)
        {
        case ResponseCode::OK:
            return "200 OK";
        case ResponseCode::NOT_FOUND:
            return "404 Not Found";
        case ResponseCode::INTERNAL_SERVER_ERROR:
            return "500 Internal Server Error";
        case ResponseCode::MOVED_PERMANENTLY:
            return "301 Moved Permanently";
        }
    }

    std::vector<std::string> Utils::split(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> tokens = std::vector<std::string>();
        std::string strCopy = str;

        std::size_t pos = 0;
        std::string token;

        while ((pos = strCopy.find(delim)) != std::string::npos)
        {
            token = strCopy.substr(0, pos);
            strCopy.erase(0, pos + delim.length());

            tokens.push_back(token);
        }

        if (strCopy.length() > 0)
        {
            tokens.push_back(strCopy);
        }

        return tokens;
    }

    std::string Utils::concat(const std::vector<std::string>& strings, const std::string& delim)
    {
        std::string result;

        for (std::size_t i = 0; i < strings.size(); i++)
        {
            result += strings[i];

            if ((i + 1) != strings.size())
            {
                result += delim;
            }
        }

        return result;
    }

    std::string Utils::URLParser(std::string url, std::string indexDir)
    {
        std::string path = url;
        //path.erase(0, 1);

        path = indexDir + path;

        return path;
    }
}
