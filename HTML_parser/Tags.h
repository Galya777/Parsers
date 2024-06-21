#pragma once
#include <fstream>
#include <string>
class Tags
{
public:
	Tags(std::string description, std::string content);

	bool checkDescr(std::string description) const; //Checks if the given Description matches with the member var description

	virtual void print() const = 0; //Print the type of the tag and its contents

	virtual void saveHTML(std::ostream& out) const = 0; //Saves the tag into a file

	virtual std::string returnType() const = 0; //Return which type of tag it is
	std::string getDescr() const; //Return the value of the description member var

	virtual Tags* clone() = 0; //Clones the object
protected:
	std::string description;
	std::string content;
};
