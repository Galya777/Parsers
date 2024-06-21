#pragma once
#include "Base.h"
class NULL_JSON: public Base
{
public:
    ~NULL_JSON();
    virtual Base* clone()const;
    virtual void print(std::ostream& out, bool pretty = true, int offset = 0) const;

    virtual Base* getElement(std::string index);
    virtual const Base* getElement(const std::string index)const;
    virtual void setOnKey(const std::string key, Base* newValue);
    virtual void addItem(const Base* value, const char* key = nullptr);
    virtual void search(Base* fidnValues, const std::string key)const;
};

