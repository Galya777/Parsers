#pragma once
#include <string>
#include "Base.h"
class StringJSON: public Base
{
public:
    StringJSON() = default;
    StringJSON(const std::string string);
    ~StringJSON();
    virtual Base* clone()const;
    virtual void print(std::ostream & out, bool pretty = true, int offset = 0) const;

    virtual Base* getElement(std::string index);
    virtual const Base* getElement(const std::string index)const;
    virtual void setOnKey(const std::string key, Base* newValue);
    virtual void addItem(const Base* value, const char* key = nullptr);
    virtual void search(Base* fidnValues, const std::string key)const;
private:
	std::string str;
};

