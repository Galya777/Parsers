#pragma once
#include "Tags.h"
#include <iostream>
class Heather : public Tags
{
public:
	Heather(std::string description, std::string content);

	virtual void print() const;

	virtual void saveHTML(std::ostream& out) const;

	virtual std::string returnType() const;

	virtual Tags* clone();
};

