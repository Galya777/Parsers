#include "Base.h"

Base::~Base()
{
}

Base* Base::operator[](const std::string string)
{
    return getElement(string.c_str());

}

const Base* Base::operator[](const std::string string) const
{
    return getElement(string.c_str());
}
