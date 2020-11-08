#include "FileProcessor.h"
#include <fstream>
#include <iterator>
#include <algorithm>


std::string FileProcessor::readText(std::string path)
{
	std::ifstream fileInput(path);
	std::string str;
	// Check if it opened and if it did, grab the entire contents
	if (fileInput.good())
	{
		str.assign((std::istreambuf_iterator<char>(fileInput)), std::istreambuf_iterator<char>());
	}

	fileInput.close();

	return str;
}

std::string FileProcessor::readBinary(std::string path)
{
	std::ifstream fileInput(path, std::ios::binary);
	std::string str;
	// Check if it opened and if it did, grab the entire contents
	if (fileInput.good())
	{
		str.assign((std::istreambuf_iterator<char>(fileInput)), std::istreambuf_iterator<char>());
	}

	fileInput.close();

	return str;
}
