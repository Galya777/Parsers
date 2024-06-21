#pragma once
#include "Heather.h"
#include "Text.h"
#include "Video.h"
#include "Link.h"
#include "Image.h"
#include "Div.h"

#include <fstream>
#include <vector>
const int MAX_SIZE = 1000;
class TagConteiner
{
public:
	TagConteiner();
	TagConteiner(TagConteiner& other) = delete;
	TagConteiner& operator=(const TagConteiner& other) = delete;
	~TagConteiner();

	void newElem(std::string type, std::string description, std::string content, std::string link = nullptr); //Adds new Element
	void remove(const int& curr); //Removes existing tag
	void moveTo(const int& from, const int& to); //Moves a tag to a different position
	void print(const int& curr) const; //Print the contents of the container

	void destroyOldContent(); //Clearing the container because of a new file or error in loading the current file
	void load(const char* buffer); //Load a different file
	void save(std::ostream& out, const int& current) const; //Saves the current one

	int tagExist(std::string container)const; //Returns the position of a Tag in the container if it exists
	int getSize()const; //Return the number of Tags in the containers
	std::string getDescr(const int& pos) const; //Returns the Description by giving its position
	std::string returnType(const int& pos) const; //Return the type of a Tag by giving its position

	bool getCharUntil(const char*, char*, const char&, int&); //Fills a char array until a given delim char is met
	bool findPhrase(const char*, const char*, int&); //Look for a given phrase in a char array
private:
	void clean(const int& curr);
	void resize();
	void sort(const int& curr);
	void moveLowToHigh(const int& from, const int& to);
	void moveHighToLow(const int& to, const int& from);



	int size;
	int maxSize;
	Tags** tags;
};

