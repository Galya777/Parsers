#pragma once
#include "Tags.h"
#include <iostream>
class Link :public Tags
{
public:
	Link(std::string description, std::string content, std::string link);

	virtual void print() const;

	virtual void saveHTML(std::ostream& out) const;

	virtual std::string returnType() const;

	virtual Tags* clone();
private:
	std::string linkText;
};

