#include "JSONTable.h"

jsonTable::jsonTable()
{

}

jsonTable::~jsonTable()
{
	for (int i = 0; i < size; ++i)
		delete data[i].json;
}

Base* jsonTable::find(const std::string string)
{
    int size = this->size;
    for (int i = 0; i < size; ++i)
        if (data[i].name == string)
            return data[i].json;
    return nullptr;

}

void jsonTable::add(const JSONTable& newItem)
{
    if (find(newItem.name))
        throw std::invalid_argument("name is used");

    vector::push_back(newItem);
    ++size;
}

void jsonTable::remove(const std::string string)
{
    int size = this->size;
    for (int i = 0; i < size; ++i)
        if (data[i].name == string)
        {
            delete data[i].json;
            data[i].json = nullptr;
            return;
        }
}
