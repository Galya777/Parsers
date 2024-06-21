#include "StringJSON.h"

StringJSON::StringJSON(const std::string string)
{
	this->str = string;
}

StringJSON::~StringJSON()
{
	
}

Base* StringJSON::clone() const
{
	return new StringJSON(*this);
}

void StringJSON::print(std::ostream& out, bool pretty, int offset) const
{
	out<< "\"" << str << "\"";
}

Base* StringJSON::getElement(std::string index)
{
	return nullptr;
}

const Base* StringJSON::getElement(const std::string index) const
{
	return nullptr;
}

void StringJSON::setOnKey(const std::string key, Base* newValue)
{
}

void StringJSON::addItem(const Base* value, const char* key)
{
}

void StringJSON::search(Base* fidnValues, const std::string key) const
{
}
