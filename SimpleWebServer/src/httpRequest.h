#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include "httpHeader.h"
#include "httpRequestData.h"
#include "httpUtils.h"

namespace HTTP
{
    class Request
    {
    private:
        Version _version;
        Method _method;
        std::string _resource;
        std::vector<Header> _headers;
        std::vector<RequestData> _data;

    public:
        Request(Method method, const std::string& resource, const std::vector<Header>& headers, Version version = Version::HTTP_1_1);
        Request(const std::string& request);

        std::string toRequestMessageStr() const;

        std::string getURL(std::string indexDir) const;

        Version getVersion() const;
        Method getMethod() const;
        std::vector<RequestData> getData() const;
    };
}
