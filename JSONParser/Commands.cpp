#include "Commands.h"
#include <iostream>
using namespace std;
Commands::Commands(const char* com)
{

}

Commands::Commands()
{
	command = " ";
}

void Commands::open()
{
	std::cin >> file;
	newFile.open(file);
	if (newFile) {
		char arr[MAX_CONTENT];
		while (!newFile.eof()) {
			newFile.getline(arr, MAX_CONTENT);
			std::cout << arr << std::endl;
		}
	}
	else {
		oldFile.open(file, std::ios::app);
		oldFile << "New File";
	}
	std::cout << "File successfully opened!" << std::endl;
	}

void Commands::close()
{
	oldFile.close();
	newFile.close();
	std::cout << "File successfully closed!" << std::endl;
}

void Commands::save()
{
	char* buffer;
	long size;

	std::ifstream infile(file, std::ifstream::binary);
	std::ofstream outfile(file, std::ofstream::binary);
	infile.seekg(0, std::ifstream::end);
	size = infile.tellg();
	infile.seekg(0);
	buffer = new char[size];
	infile.read(buffer, size);
	outfile.write(buffer, size);
	delete[] buffer;

	outfile.close();
	infile.close();
	std::cout << "File successfully saved!" << std::endl;
}

void Commands::saveAs()
{
	char* buffer;
	long size;
	char path[MAX_FILE];
	std::cout << "Enter the path: ";
	std::cin >> path;
	std::ifstream infile(file, std::ifstream::binary);
	std::ofstream outfile(path, std::ofstream::binary);
	infile.seekg(0, std::ifstream::end);
	size = infile.tellg();
	infile.seekg(0);
	buffer = new char[size];
	infile.read(buffer, size);
	outfile.write(buffer, size);
	delete[] buffer;
	outfile.close();
	infile.close();
	std::cout << "File successfully saved!" << std::endl;
}

void Commands::help()
{
	cout << "commands:" << endl;
	cout << "--> exit : exit the demo" << endl;
	cout << "--> help : show help" << endl;
	cout << "--> search (--save/--print/--clear) key_1...key_n : finds all elements by keys. Returns an array of copies of all found elements.\n\t--print prints the array,\n\t--save saves the array,\n\t--clear clears the content of the array " << endl;
	cout << "--> print : prints the selected value" << endl;
	cout << "--> save <string::path> <--override-file/--no> <--pretty/--min> : saves the selected value" << endl;
    cout << "--> create <string::str_1> ... <string::str_n> : adding n parsed strings to currently selected item (array or composite)" << endl;
	cout << "--> move <string/int::key_1> <string/int::key_2> : swaps values of path1 and path2" << endl;
	cout << "--> delete <string/int::key> : removes the element on index key";
	
}

void Commands::print(jsonTable& jt)
{
	char name[200];
	std::cin >> name;

	Base* json = nullptr;
	try {
		json = getElement(name, jt);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	json->print(std::cout);
}

void Commands::search(jsonTable& jt)
{

	char name[200], newname[200], key[200];
	std::cin >> newname >> name >> key;

	Base* json = nullptr;
	try {
		json = getElement(name, jt);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	std::string Key=key;
	Key.append('\0');

	Base* srch = new ArrayJSON;
	json->search(srch, Key);


	JSONTable var(newname, srch);

	try {
		jt.add(var);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		delete json;
		return;
	}
	delete srch;

	std::cout << newname << " was created from search\n";

}

void Commands::set(jsonTable& jt)
{

	char name[64];
	char type[16];
	char value[64];
	char con[1024];

	std::cin >> name >> type >> value;
	std::string t=type;

	std::cin.ignore();
	std::cin.getline(con, 1024);

	Base* json = nullptr;

	try {
		if (t == "-f")
			json = JSONtYPE::CreateFromFile(con);
		else if (t == "-t")
			json = JSONtYPE::CreateFromString(con);
		else if (t == "-j")
			json = getElement(con, jt);
		else {
			std::cout << "<jsonName> -f <filename>  --- add file\n"
				<< "<jsonName> -t <text>      --- add text\n"
				<< "<jsonName> -j <json>      --- add obj\n";
			return;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	Item item;
	item.setKey(value);
	item.setContent(json);

	try {
		Base* base = getElement(name, jt);
		base->addItem(json, value);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		delete json;
		return;
	}

	std::cout << name << " was added\n";
}




void Commands::create(jsonTable& jt)
{
	char name[64];
	char type[16];
	char con[1024];

	std::cin >> name >> type;
	std::string t=type;

	std::cin.ignore();
	std::cin.getline(con, 1024);

	Base* json = nullptr;

	try {
		if (t == "-f")
			json = JSONtYPE::CreateFromFile(con);
		else if (t == "-t")
			json = JSONtYPE::CreateFromString(con);
		else if (t == "-j")
			json = getElement(con, jt);
		else {
			std::cout << "<jsonName> -f <filename>  --- load from file\n"
				<< "<jsonName> -t <text>      --- load from text\n"
				<< "<jsonName> -j <json>      --- empty obj\n";
			return;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	JSONTable var(name, json);
	delete json;

	try {
		jt.add(var);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	std::cout << name << " was created\n";
}

void Commands::del(jsonTable& jt)
{
	char name[128];
	std::cin >> name;
	std::string n=name;
	jt.remove(n);
	std::cout << name << " was deleted \n";
}

void Commands::swap(jsonTable& jt)
{
	std::string name1;
	std::string name2;
	std::cin >> name1 >> name2;

	Base* json1 = nullptr;
	Base* json2 = nullptr;
	Base* temp = nullptr;

	std::string last_key1;
	std::string last_key2;

	try {
		json1 = getPevElent(name1, jt, last_key1);
		json2 = getPevElent(name2, jt, last_key2);

		temp = (*json1)[last_key1]->clone();
		json1->setOnKey(last_key1, (*json2)[last_key2]);
		json2->setOnKey(last_key2, temp);

	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}

}

void Commands::run()
{
	do {
		std::cout << "Enter your command: ";
		std::cin >> command;
		if (command == "open") {
			open();
		} else if (command == "close") {
			close();
		}
		else if (command == "save") {
			save();
		}
		else if (command == "save as") {
			saveAs();
		}
		else if (command == "help") {
			help();
		}
		else if (command == "print") {
			print(usedJsons);
		}
		else if (command == "search") {
			search(usedJsons);
		}
		else if (command == "set") {
			set(usedJsons);
		}
		else if (command == "create") {
			create(usedJsons);
		}
		else if (command == "delete") {
			del(usedJsons);
		}
		else if (command == "swap") {
			swap(usedJsons);
		}
		else {
			cout << "Command is not excisting!\n";
		}
	} while (command != "exit");
}

Base* Commands::getPevElent(const std::string string, jsonTable& jt, std::string lastkey) const
{
	std::vector<std::string> keys = getKeys(string);
	keys[0].append('\0');
	Base* json = jt.find(keys[0]);

	if (!json) {
		throw std::invalid_argument(keys[0] + ": json is not created!");
	}

	if (keys.size() == 1)
		throw std::invalid_argument("jsons cant be swaped");

	int size = keys.size();

	int i;
	for (i = 1; i < size - 1; ++i) {
		keys.at(i).push_back('\0');
		json = json->getElement(keys[i]);


		if (!json) {
			throw std::invalid_argument(keys[i] + ": key not found!");
		}
	}

	lastkey = keys[i];
	lastkey.append('\0');

	return json;

}

std::vector<std::string> Commands::getKeys(const std::string string) const
{
	std::vector<std::string> keys;
	std::string name;
	int size = string.size();

	char ch;
	int cur = 0;

	for (; cur < size; ++cur) {
		ch = string[cur];
		if (ch == '[')
			break;
		name.push_back(ch);
	}
	keys.push_back(name);
	if (cur == size)    return keys;

	std::string key;
	while (cur < size && string[cur] == '[') {
		++cur;
		key = "";
		for (; cur < size && string[cur] != ']'; ++cur) {
			ch = string[cur];
			key.push_back(ch);
		}
		++cur;
		key.append('\0');
		keys.push_back(key);
	}

	if (cur != size) {
		throw std::invalid_argument(key + " missing ] !");
	}

	return keys;
}

Base* Commands::getElement(const std::string string, jsonTable& jt) const
{
	std::vector<std::string> keys = getKeys(string);
	keys.at(0).push_back('\0');
	Base* json = jt.find(keys[0]);

	if (!json) {
		
		throw std::invalid_argument(keys[0] + ": json is not created!");
	}

	if (keys.size() == 1)
		return json;

	int size = keys.size();

	for (int i = 1; i < size; ++i) {
		json = json->getElement(keys[i]);

		if (!json) {
			throw std::invalid_argument(keys[i] + ": key not found!");
		}
	}

	return json->clone();
}



	

		
	
