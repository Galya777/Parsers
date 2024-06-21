#include "Div.h"

Div::Div(std::string description, std::string content): Tags(description, content)
{
}

void Div::print() const
{
	std::cout << " Type: Div" << std::endl;
	std::cout << "Contents of div " << description << std::endl;
}

void Div::saveHTML(std::ostream& out) const
{
	out << "<div descr=\"" << description << "\">" << std::endl;
}

std::string Div::returnType() const
{
	return "div";
}

Tags* Div::clone()
{
	return new Div(*this);
}
