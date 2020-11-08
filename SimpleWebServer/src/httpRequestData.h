#pragma once
#include <string>
#include <map>
#include "httpUtils.h"

namespace HTTP
{
    class RequestData
    {
    private:
        std::map<std::string, std::string> _data;

    public:
        RequestData();
        RequestData(const std::string& data);

        const std::string& getValue(const std::string& key) const;
    };
}
