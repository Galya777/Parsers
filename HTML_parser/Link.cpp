#include "Link.h"

Link::Link(std::string description, std::string content, std::string link):Tags(description, content), linkText(link)
{
}

void Link::print() const
{
	std::cout << " Type: Link" << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Content: " << content << std::endl;
	std::cout << "Link text: " << linkText << std::endl;
}

void Link::saveHTML(std::ostream& out) const
{
	//The syntaxis for the HTML tag for link
	out << "<a href=" << '\"' << content << '\"';
	out << " descr=" << '\"' << description << '\"';
	out << "> " << linkText << "</a>" << std::endl;
	out << "<br>" << std::endl;
}

std::string Link::returnType() const
{
	return "link";
}

Tags* Link::clone()
{
	return new Link(*this);
}
