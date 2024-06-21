#include "BoolJSON.h"

BoolJSON::BoolJSON(bool value)
{
	this->value = value;
}

BoolJSON::~BoolJSON()
{

}

Base* BoolJSON::clone() const
{
	return new BoolJSON(*this);
}

void BoolJSON::print(std::ostream& out, bool pretty, int offset) const
{
	out<< (value ? "True" : "False");

}

Base* BoolJSON::getElement(std::string index)
{
	return nullptr;
}

const Base* BoolJSON::getElement(const std::string index) const
{
	return nullptr;
}

void BoolJSON::setOnKey(const std::string key, Base* newValue)
{
}

void BoolJSON::addItem(const Base* value, const char* key)
{
}

void BoolJSON::search(Base* fidnValues, const std::string key) const
{
}
