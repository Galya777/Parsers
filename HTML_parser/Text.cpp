#include "Text.h"

Text::Text(std::string description, std::string content) :Tags(description, content)
{
}

void Text::print() const
{
	std::cout << " Type: Text" << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Content: " << content << std::endl;
}

void Text::saveHTML(std::ostream& out) const
{
	//The syntaxis for the HTML tag for text
	out << "<p descr=\"" << description << "\">";
	out << content << "</p>" << std::endl;
	out << "<br>" << std::endl;
}

std::string Text::returnType() const
{
	return "text";
}

Tags* Text::clone()
{
	return new Text(*this);
}
