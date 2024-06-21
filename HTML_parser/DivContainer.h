#pragma once
#include "TagConteiner.h"
class DivContainer
{
public:
	DivContainer();
	DivContainer(const DivContainer&) = delete;
	DivContainer& operator=(const DivContainer&) = delete;
	~DivContainer();

	void newDiv(const char*);
	void newElem(const char*, const char*, const char*, const char*, const char* = nullptr);

	void load(const char*, const char*);
	void save(std::ostream&, const char*) const;
	void print(const char*) const;
	void destroyOldContent();

	void moveTo(const int&, const char*, const int&);
	void removeTag(const char*, const int&);
	void removeDiv(const char*);

	int tagExist(const char*)const;
private:
	void clean(const int&);
	void resize();
	void sort(const int&);

	std::string descriptions;
	int size;
	int maxSize;
	TagConteiner** tags;
};

