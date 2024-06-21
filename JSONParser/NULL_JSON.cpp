#include "NULL_JSON.h"

NULL_JSON::~NULL_JSON()
{

}

Base* NULL_JSON::clone() const
{
	return new NULL_JSON(*this);

}

void NULL_JSON::print(std::ostream& out, bool pretty, int offset) const
{
	out << "null";
}

Base* NULL_JSON::getElement(std::string index)
{
	return nullptr;
}

const Base* NULL_JSON::getElement(const std::string index) const
{
	return nullptr;
}

void NULL_JSON::setOnKey(const std::string key, Base* newValue)
{
}

void NULL_JSON::addItem(const Base* value, const char* key)
{
}

void NULL_JSON::search(Base* fidnValues, const std::string key) const
{
}
