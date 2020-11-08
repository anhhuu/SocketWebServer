#pragma once
#include <string>

#include "httpUtils.h"

namespace HTTP
{
    class Header
    {
    private:
        std::string _key;
        std::string _value;

    public:
        Header(const std::string& key, const std::string& value);
        Header(const std::string& header);

        void setValue(const std::string& value);
        void setKey(const std::string& key);

        std::string toHeaderMessageStr() const;

        const std::string& getKey() const;
        const std::string& getValue() const;
    };
}