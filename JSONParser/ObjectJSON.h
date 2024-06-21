#pragma once
#include "Base.h"
#include "Item.h"
#include <vector>
class ObjectJSON;
typedef std::vector<Item*> ItemVector;
class ObjectJSON: public Base
{
public: 
   
    ObjectJSON();
    ObjectJSON(const ObjectJSON& other);
    ObjectJSON(const ItemVector& items);
    ~ObjectJSON();

    virtual Base* clone()const;
    virtual Base* getElement(const std::string key);
    virtual const Base* getElement(const std::string key) const;
    virtual void print(std::ostream& out, bool pretty = true, int offset = 0) const;
    virtual void setOnKey(const std::string key, Base* newValue);
    virtual void search(Base* fidnValues, const std::string key)const;

    void addItem(const Item& newItem);
    virtual void addItem(const Base* value, const char* key = nullptr);

private:
    void copyItems(const ItemVector& items);
    void clear();
    int checkID(const std::string str)const;
    ItemVector getAllElement()const;
    ObjectJSON& operator=(const ObjectJSON&) = delete;
    ItemVector items;

};

