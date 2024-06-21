#include "NumberJSON.h"

NumberJSON::NumberJSON(double number)
{
	this->num = number;
}

NumberJSON::~NumberJSON()
{

}

Base* NumberJSON::clone() const
{
	return new NumberJSON(*this);

}

void NumberJSON::print(std::ostream& out, bool pretty, int offset) const
{
	out << num;
}

Base* NumberJSON::getElement(std::string index)
{
	return nullptr;
}

const Base* NumberJSON::getElement(const std::string index) const
{
	return nullptr;
}

void NumberJSON::setOnKey(const std::string key, Base* newValue)
{
}

void NumberJSON::addItem(const Base* value, const char* key)
{
}

void NumberJSON::search(Base* fidnValues, const std::string key) const
{
}
