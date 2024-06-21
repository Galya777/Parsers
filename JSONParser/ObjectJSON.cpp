#include "ObjectJSON.h"

ObjectJSON::ObjectJSON()
{
}

ObjectJSON::ObjectJSON(const ObjectJSON& other)
{
	copyItems(other.getAllElement());
}

ObjectJSON::ObjectJSON(const ItemVector& items)
{
	copyItems(items);

}

ObjectJSON::~ObjectJSON()
{
	clear();
}

Base* ObjectJSON::clone() const
{
	return new ObjectJSON(*this);

}

Base* ObjectJSON::getElement(const std::string key)
{
	int el_key = checkID(key);
	return (el_key == -1) ? nullptr : items[el_key]->getSomething();

}

const Base* ObjectJSON::getElement(const std::string key) const
{
	int el_key = checkID(key);
	return (el_key == -1) ? nullptr : items[el_key]->getSomething();

}

void ObjectJSON::print(std::ostream& out, bool pretty, int offset) const
{

    out << "{";
    if (pretty) out << "\n";
    int size = items.size();

    if (size) {
        if (pretty) for (int i = 0; i < offset; ++i) out << "\t";
        items[0]->print(out);
    }
    for (int i = 1; i < size; i++) {
        out << ",";
        if (pretty) {
            out << "\n";
            for (int i = 0; i < offset; ++i) out << "\t";
        }
        items[i]->print(out);
    }
    if (pretty) {
        out << "\n";
        for (int i = 0; i < offset - 1; ++i) out << "\t";
    }
    out << "}";


}

void ObjectJSON::setOnKey(const std::string key, Base* newValue)
{
    int size = this->items.size();

    for (int i = 0; i < size; i++) {
        if (items[i]->getKey() == key) {
            items[i]->setContent(newValue);
            return;
        }
    }
}

void ObjectJSON::search(Base* fidnValues, const std::string key) const
{
    int size = this->items.size();

    for (int i = 0; i < size; i++) {
        if (items[i]->getKey() == key) {
            fidnValues->addItem(items[i]->getSomething());
        }
        items[i]->getSomething()->search(fidnValues, key);
    }


}

void ObjectJSON::addItem(const Item& newItem)
{
    Item* item = new Item(newItem);

    int index = checkID(newItem.getKey());

    std::string msg="Warning: 2 or more items with same key : ";
    msg += newItem.getKey();

    if (index > -1) {
        std::string msg="Warning: 2 or more items with same key : ";
        msg += newItem.getKey();
        throw std::invalid_argument(msg);
    }

    items.push_back(item);

}

void ObjectJSON::addItem(const Base* value, const char* key)
{
    Item item;
    if (key == nullptr)
        throw std::invalid_argument("JSON type need key!");
    item.setKey(key);
    item.setContent(value);

    addItem(item);
}

void ObjectJSON::copyItems(const ItemVector& items)
{
    int size = items.size();

    for (int i = 0; i < size; ++i) {
        this->items.push_back(new Item(*(items[i])));
    }
}

void ObjectJSON::clear()
{
    int size = items.size();

    for (int i = 0; i < size; ++i)
        delete items[i];

}

int ObjectJSON::checkID(const std::string str) const
{
    int size = this->items.size();

    for (int i = 0; i < size; i++) {
        if (items[i]->getKey() == str)
            return i;
    }

    return -1;

}

ItemVector ObjectJSON::getAllElement() const
{
    return items;
}
