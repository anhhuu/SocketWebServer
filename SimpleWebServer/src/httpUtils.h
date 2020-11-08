#pragma once
#include <string>
#include <vector>

namespace HTTP
{
	static std::string LINE_END = "\r\n";

	enum class Method
	{
		GET,
		HEAD,
		POST,
		/*PUT,
		DEL,
		TRACE,
		OPTIONS,
		CONNECT,
		PATCH*/
	};

	enum class Extensions
	{
		HTML,
		JS,
		CSS,
		JPG,
		JPEG,
		PNG,
		ICO,
		TTF
	};

	enum class ResponseCode
	{
		OK = 200,
		NOT_FOUND = 404,
		INTERNAL_SERVER_ERROR = 500,
		MOVED_PERMANENTLY = 301
	};

	enum class Version
	{
		HTTP_1_0,
		HTTP_1_1,
		HTTP_2_0
	};

	class Utils
	{
	public:
		//Method utils
		static std::string toString(Method method);
		static Method methodFromString(const std::string& method);

		//Version utils
		static std::string toString(Version version);
		static Version versionFromString(const std::string& version);

		//Extensions utils
		static std::string toString(Extensions extens);
		static Extensions extendFromString(const std::string& extens);

		//Response code utils
		static std::string toString(ResponseCode code);

		//string utils
		static std::vector<std::string> split(const std::string& str, const std::string& delim);
		static std::string concat(const std::vector<std::string>& strings, const std::string& delim = "");

		//URL parser
		static std::string URLParser(std::string url, std::string indexDir);
	};
}

