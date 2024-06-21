#pragma once
#include "Tags.h"
#include <iostream>
class Text :public Tags
{
public:
	Text(std::string description, std::string content);

	virtual void print() const;

	virtual void saveHTML(std::ostream& out) const;

	virtual std::string returnType() const;

	virtual Tags* clone();

};
