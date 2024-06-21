#pragma once
#include <fstream>
#include <cstring>
#include "JSONtYPE.h"
#include "JSONTable.h"
const int MAX_CONTENT = 100;
const int MAX_FILE = 100;
class Commands
{
public:
	Commands(const char* com);
	Commands();
	void open();
	void close();
	void save();
	void saveAs();
	void help();

	void print(jsonTable& jt);
	void search(jsonTable& jt);
	void set(jsonTable& jt);
	void create(jsonTable& jt);
	void del(jsonTable& jt);
	void swap(jsonTable& jt);

	void run();
private:
	jsonTable usedJsons;

	Base* getPevElent(const std::string string, jsonTable& jt, std::string lastkey) const;
	std::vector<std::string> getKeys(const std::string string)const;
	Base* getElement(const std::string string, jsonTable& jt)const;

	std::string command;
	std::ofstream oldFile;
	std::ifstream newFile;
	char file[MAX_FILE];
};

