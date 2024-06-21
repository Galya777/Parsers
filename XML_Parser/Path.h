#pragma once
#include <vector>
#include "Element.h"
#include "Tree.h"
#include <string>
#include <iostream>
#include "HelpingFunctions.h"
/*
* This class represents a vector that stores the elements
*/
class Path: public HelpingFunctions
{
public:
	///връща елементите по зададено дърво
	static std::vector<const Element*> getElements(std::string, const Tree&);
};

