#include "Tags.h"
#include <iostream>
Tags::Tags(std::string description, std::string content) :description(description), content(content)
{
	
}

bool Tags::checkDescr(std::string description) const
{
	return this->description==description;
}

std::string Tags::getDescr() const
{
	return description;
}
