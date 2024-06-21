#include "Image.h"

Image::Image(std::string description, std::string content) :Tags(description, content)
{
}

void Image::print() const
{
	std::cout << " Type: Image" << std::endl;
	std::cout << "Description: " << description << std::endl;
	std::cout << "Content: " << content << std::endl;
}

void Image::saveHTML(std::ostream& out) const
{
	//The syntaxis for the HTML tag for image
	out << "<img src=" << '\"' << content << '\"';
	out << " descr=" << '\"' << description << '\"' << ">" << std::endl;
	out << "<br>" << std::endl;
}

std::string Image::returnType() const
{
	return "image";
}

Tags* Image::clone()
{
	return new Image(*this);
}
