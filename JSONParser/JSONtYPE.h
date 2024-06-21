#pragma once
#include "ObjectJSON.h"
#include "StringJSON.h"
#include "NumberJSON.h"
#include "ArrayJSON.h"
#include "NULL_JSON.h"
#include "BoolJSON.h"
#include "Base.h"
#include "Item.h"
#include <string>
#include <fstream>
#include <iostream>
class JSONtYPE: public Base
{
public:

	static ObjectJSON* CreateFromFile(std::string filname);
	static Base*  CreateFromString(std::string string);
    static ObjectJSON* CreateJSONObject();
    
    static Base* CreateNewItemValue();
    static std::string ItemKey();
    static void init(std::istream& in);
    static StringJSON* CreateString();
    static NumberJSON* CreateNumber();
    static Base* CreateWordType();  //true,false,null
    static ArrayJSON* CreateArray();
    static void initString(const std::string str);
   

private:
	static std::string jsFile;
	static int cur;
	static int size;
};

