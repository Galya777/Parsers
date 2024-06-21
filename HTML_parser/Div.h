#pragma once
#include "Tags.h"
#include <iostream>
class Div :public Tags
{
public:
	Div(std::string description, std::string content);

	void print() const;
	void saveHTML(std::ostream& out) const;

	virtual std::string returnType() const;

	virtual Tags* clone();
};
