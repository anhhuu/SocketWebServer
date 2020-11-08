#include "httpHeader.h"
#include <sstream>
#include <algorithm>
namespace HTTP
{
    Header::Header(const std::string& key, const std::string& value)
        : _key(key), _value(value)
    {
    }

    Header::Header(const std::string& header)
    {
        std::size_t  pos = header.find(':');
        if (pos == std::string::npos) {
            throw std::runtime_error("Isn't format of Header");
        }
        std::string key(header.substr(0, pos));

        std::size_t  first = header.find_first_not_of(" \t", pos + 1);
        std::size_t  last = header.find_last_not_of(" \t");
        std::string value(header.substr(first, last - first + 1));

        this->_key = key;
        this->_value = value;
    }

    void Header::setValue(const std::string& value)
    {
        this->_value = value;
    }

    void Header::setKey(const std::string& key)
    {
        this->_key = key;
    }

    const std::string& Header::getKey() const
    {
        return this->_key;
    }

    const std::string& Header::getValue() const
    {
        return _value;
    }

    std::string Header::toHeaderMessageStr() const
    {
        std::string header;
        header += this->_key;
        header += ": ";
        header += this->_value;
        header += LINE_END;

        return header;
    }
}
