#pragma once
#include <vector>
#include <string>
#include "Base.h"
class JSONTable
{
public:
    std::string name;
    Base* json;

    JSONTable()
        : json(nullptr)
    {}
    JSONTable(const std::string key, const Base* value) {
        name = key;
        this->name.push_back('\0');
        json = value->clone();
    }
    ~JSONTable()
    {}

    JSONTable& operator =(const JSONTable& other)
    {
        name = other.name;
        json = other.json->clone();
        return *this;
    }
};

class jsonTable :
    public std::vector<JSONTable> 
{
public:
    jsonTable();
    ~jsonTable();
    Base* find(const std::string string);
    void add(const JSONTable& newItem);
    void remove(const std::string string);

private:
   JSONTable* data;
   int size = 0;
};


