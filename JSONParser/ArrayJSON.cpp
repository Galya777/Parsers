#include "ArrayJSON.h"

ArrayJSON::ArrayJSON()
{

}

ArrayJSON::ArrayJSON(const ArrayJSON& other)
{
	copyItems(other.getAllElements());
}

ArrayJSON::ArrayJSON(const TypeArray& items)
{
	copyItems(items);
}

ArrayJSON::~ArrayJSON()
{
	clear();
}

Base* ArrayJSON::clone() const
{
	return new ArrayJSON(*this);
}

Base* ArrayJSON::getElement(const std::string key)
{
	int index = parseKey(key);

	return items.at(index);
}

const Base* ArrayJSON::getElement(const std::string key) const
{
	int index = parseKey(key);

	return items[index];
}

void ArrayJSON::print(std::ostream& out, bool pretty, int offset) const
{
    out << "[\n";

    int size = items.size();

    if (size > 0) {
        if (pretty)for (int i = 0; i < offset; ++i) out << "\t";
        items[0]->print(out, pretty, offset + 1);
    }

    for (int i = 1; i < size; i++) {
        out << ",";
        if (pretty) {
            out << "\n";
            for (int i = 0; i < offset * pretty; ++i) out << "\t";
        }
        items[i]->print(out, pretty, offset + 1);
    }

    if (pretty) {
        out << "\n";
        for (int i = 0; i < offset - 1 * pretty; ++i) out << "\t";
    }

    out << "]";
}

void ArrayJSON::setOnKey(const std::string key, Base* newValue)
{
    int size = items.size();
    int index = parseKey(key);
    delete items[index];
    items[index] = newValue->clone();

}

void ArrayJSON::addItem(const Base* value, const char* key)
{
    Base* new_value = value->clone();
    items.push_back(new_value);

}

void ArrayJSON::search(Base* fidnValues, const std::string key) const
{
    int size = items.size();
    for (int i = 0; i < size; ++i)
        items[i]->search(fidnValues, key);

}

bool ArrayJSON::isKeyValid(const std::string key) const
{
    int size = key.size();

    for (int i = 0; i < size; ++i)
        if ((key[i] < '0' || key[i]>'9') && key[i] != '\0')
            return false;

    return true;

}

int ArrayJSON::parseKey(const std::string key) const
{
    std::string msg(key);
    msg.c_str();
    if (!(isKeyValid(key))) {
        msg += ": invalid key";
        throw std::invalid_argument(msg);
    }

    int index;
    sscanf_s(key.c_str(), "%d", &index);

    if (index > items.size()) {
        msg += ": size error";
        throw std::invalid_argument(msg);
    }

    return index;

}

void ArrayJSON::clear()
{
    int size = items.size();

    for (int i = 0; i < size; ++i)
        delete items[i];
}

TypeArray ArrayJSON::getAllElements() const
{
    return items;
}

void ArrayJSON::copyItems(const TypeArray& items)
{

    int size = items.size();

    for (int i = 0; i < size; ++i)
        this->items.push_back(items.at(i)->clone());

}
