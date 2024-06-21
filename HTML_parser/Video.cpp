#include "Video.h"

Video::Video(std::string description, std::string content):Tags(description, content)
{
}

void Video::print() const
{
	std::cout << " Type: Video" << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Content: " << content << std::endl;
}

void Video::saveHTML(std::ostream& out) const
{
	//The syntaxis for the HTML tag for video
	out << "<iframe src=" << '\"' << content << '\"';
	out << " descr=" << '\"' << description << '\"';
	out << "></iframe>" << std::endl;
	out << "<br>" << std::endl;
}

std::string Video::returnType() const
{
	return "video";
}

Tags* Video::clone()
{
	return new Video(*this);
}

