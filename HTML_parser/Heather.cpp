#include "Heather.h"

Heather::Heather(std::string description, std::string content): Tags(description, content)
{
}

void Heather::print() const
{
	std::cout << " Type: Heading" << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Content: " << content << std::endl;
}

void Heather::saveHTML(std::ostream& out) const
{
	out << "<h2 descr=\"" << description << '\"' << '>';
	out << content << "</h2>" << std::endl;
	out << "<br>" << std::endl;
}

std::string Heather::returnType() const
{
	return "heading";
}

Tags* Heather::clone()
{
	return new Heather(*this);;
}
