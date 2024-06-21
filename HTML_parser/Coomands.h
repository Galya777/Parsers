#pragma once
#include "TagConteiner.h"
#include "DivContainer.h"
#include <iostream>
#pragma warning(disable:4996)
class Coomands
{
public:
	Coomands();


	void newElem(std::string, std::string, std::string, std::string, const bool& = false, std::string = nullptr);
	void remove(std::string, const bool& = false, std::string = nullptr);
	void moveTo(const int&, std::string, const bool& = false, std::string = nullptr);
	void print(const bool& = false, std::string = nullptr) const;
	void load(std::string);
	void save(std::string);
	void exit();

	bool divTagExist(std::string); //Checks if there is a div tag with Given description

	void run();
private:
	void newFile();
	void changeFilename(std::string);

	bool checkFileExtension(const char*, const char*); //Checks the file extension
	void inputFirst(char*); //Gets the first input needed to know the command 
	void inputRest(const char*, char*, char*, char*, char*, int&, char*); //Gets the rest of the input needed to complete the command

	std::string filename;
	TagConteiner tags;
	DivContainer divs;
	bool fileLoaded;
	bool upToDate;
};

