#pragma once
#include <fstream>
#include <streambuf>


static std::string StringFromFile(const char *filename)
{
	std::ifstream file(filename);
	std::string fileString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return fileString;
}