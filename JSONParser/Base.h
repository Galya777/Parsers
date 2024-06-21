#pragma once
#include <ostream>
class Base
{
public:
    virtual ~Base();

    virtual Base* clone()const = 0;

    virtual Base* getElement(std::string index)=0;
    virtual const Base* getElement(const std::string index)const=0;

    virtual void print(std::ostream& out, bool pretty = true, int offset = 0)const = 0;
    virtual void setOnKey(const std::string key, Base* newValue) = 0;
    virtual void addItem(const Base* value, const char* key = nullptr) = 0;
    virtual void search(Base* fidnValues, const std::string key)const = 0;
    Base* operator[](const std::string string);
    const Base* operator [](const std::string string)const;
};

