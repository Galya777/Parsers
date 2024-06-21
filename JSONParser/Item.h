#pragma once
#include <exception>
#include <ostream>
#include "Base.h"
class Item
{
public:
	Item(const std::string& key, const Base* something);
	Item();
	Item(const Item& other);
	Item& operator=(const Item& other);
   ~Item();

   void setKey(const std::string& key);
   void setContent(const Base* something);

   std::string getKey() const;
   Base* getSomething() const;

   void print(std::ostream& out);

private:
	bool isKeyValid(const std::string& key);

	std::string key;
	Base *something;
};

