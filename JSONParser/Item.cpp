#include "Item.h"

Item::Item(const std::string& key, const Base* something)
    :key(key)
{
    if (!isKeyValid(this->key))
        throw std::invalid_argument(this->key + " is not a valid key");
    this->something = something->clone();
    this->key.push_back('\0');
}


Item::Item() :something(nullptr), key("")
{
}

Item::Item(const Item& other)
	: key(other.getKey())
{
	this->something = other.getSomething()->clone();
}

Item& Item::operator=(const Item& other)
{
    if (this != &other)
    {
        this->key = other.getKey();
        delete this->something;
        this->something = other.getSomething()->clone();
    }

    return *this;
}

Item::~Item()
{
    delete something;
}

void Item::setKey(const std::string& key)
{

    if (!isKeyValid(key))
        throw std::invalid_argument("Invalid Key!");

    this->key = key;
    this->key.push_back('\0');

}

void Item::setContent(const Base* something)
{
    this->something = something ? something->clone() : nullptr;
}

std::string Item::getKey() const
{
    return key;
}

Base* Item::getSomething() const
{
    return something;
}

void Item::print(std::ostream& out)
{
    out << key << ":";
    something->print(out);
}

bool Item::isKeyValid(const std::string& key)
{
    int len = key.size();

    for (int i = 0; i < len; ++i) {
        char ch = key[i];
        bool Cl = (ch >= 'A' && ch <= 'Z');      //is capital letter
        bool Ll = (ch >= 'a' && ch <= 'z');      //is lowercase letter
        bool num = (ch >= '0' && ch <= '9');     // numbers
        bool other = (ch == '_' || ch == '-' || '\'' || '\"' || " ");
        if (!(Cl || Ll || num || other))
            return false;
    }

    return true;

}



