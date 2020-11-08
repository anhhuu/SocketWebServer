#pragma once
#include <string>

class FileProcessor
{
public:
	static std::string readText(std::string path);
	static std::string readBinary(std::string path);
};
