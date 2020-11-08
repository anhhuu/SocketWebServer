#include "httpRequestData.h"
#include <sstream>
#include <algorithm>
#include <iostream>
namespace HTTP
{
    RequestData::RequestData()
        :_data()
    {
    }

    RequestData::RequestData(const std::string& data)
    {
        std::vector<std::string> lines = Utils::split(data, "&");

        for (const std::string line : lines)
        {
            std::vector<std::string> index = Utils::split(line, "=");
            _data.insert(std::pair<std::string, std::string>(index[0], index[1]));
            //_data[index[0]] = _data[index[1]];
        }
    }

    const std::string& RequestData::getValue(const std::string& key) const
    {
        return _data.at(key);
    }
}
