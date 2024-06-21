#pragma once
#include <string>
#include <vector>
/*
* Helping functions
*/
class HelpingFunctions
{
public:
	bool hasEnding(std::string const& fullString, std::string const& ending);
	static std::vector<std::string> split(std::string& s, char seperator);
};

