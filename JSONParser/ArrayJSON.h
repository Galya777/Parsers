#pragma once
#include "Base.h"
#include <vector>
class ArrayJSON;
typedef std::vector<Base*> TypeArray; 
class ArrayJSON:public Base
{
public:
    ArrayJSON();
    ArrayJSON(const ArrayJSON& other);
    ArrayJSON(const TypeArray& items);
    ~ArrayJSON();

    virtual Base* clone()const;
    virtual Base* getElement(const std::string key);             // key must be a number
    virtual const Base* getElement(const std::string key) const; // key must be a number
    virtual void print(std::ostream& out, bool pretty = true, int offset = 0) const;
    virtual void setOnKey(const std::string key, Base* newValue);
    virtual void addItem(const Base* value, const char* key = nullptr);
    virtual void search(Base* fidnValues, const std::string key) const;

private:
    bool isKeyValid(const std::string key)const;
    int parseKey(const std::string key)const;
    void clear();
    TypeArray getAllElements()const;
    void copyItems(const TypeArray& items);

private:
    TypeArray items;
}; 

