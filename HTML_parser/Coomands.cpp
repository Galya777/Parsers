#include "Coomands.h"

Coomands::Coomands() :filename(nullptr), tags(), divs(), fileLoaded(false), upToDate(true)
{
	this->filename = "";
	this->filename[0] = 0;
}


//Adds new Element to a of the containers based on the div description
void Coomands::newElem(std::string type, std::string description, std::string content, std::string linkText, const bool& divEncountered, std::string divDescr)
{
	if (!fileLoaded)
		throw std::invalid_argument("File must first be loaded");

	//There can't be a div inside another div
	if (divEncountered && type== "div") 
		throw std::invalid_argument("You can't add a div tag inside a div tag");

	if (divEncountered) //Only if the user is working with a div
		divs.newElem(divDescr.c_str(), type.c_str(), description.c_str(), content.c_str(), linkText.c_str());
	else //For everything else it adds it to the regular container
		tags.newElem(type, description, content, linkText);

	if (type=="div")  //Creates a new div container
		divs.newDiv(description.c_str());

	std::cout << "New " << type << " has been added" << std::endl;

	upToDate = false; //Remainder to save the update the file before exit
}

void Coomands::remove(std::string description, const bool& divEncountered, std::string divDescr)
{
	if (!fileLoaded)
		throw std::invalid_argument("File must first be loaded");

	if (!divEncountered) //For everything else it removes from to the regular container  
	{
		int toRemovePos = tags.tagExist(description); //Check to see if the tag with that description exist
		if (toRemovePos < 0) //If it exist it should return its position in the container 
			throw std::invalid_argument("Post doesn't exist"); //If not it returns -1
		if (tags.getDescr(toRemovePos)== "div")  //If the tag is of type div
			divs.removeDiv(description.c_str()); //Remove all of its contents
		tags.remove(toRemovePos); //Then remove the tag from the container
	}
	else //Only if the user is working with a div
	{
		int toRemovePos = divs.tagExist(divDescr.c_str()); //Check to see if div tag with that description exist
		if (toRemovePos < 0) //If it exist it should return its position in the div container 
			throw std::invalid_argument("Post doesn't exist"); //If not it returns -1
		divs.removeTag(description.c_str(), toRemovePos); //Then remove the tag from the div container
	}

	std::cout << "Tag " << description << " has been removed" << std::endl;

	upToDate = false; //Remainder to save the update the file before exit
}

void Coomands::moveTo(const int& toMove, std::string description, const bool& divEncountered, std::string divDescr)
{
	if (!fileLoaded)
		throw std::invalid_argument("File must first be loaded");

	if (divEncountered)
	{
		int toFindPos = divs.tagExist(divDescr.c_str()); //Check to see if div tag with that description exist
		if (toFindPos < 0) //If it exist it should return its position in the div container 
			throw std::invalid_argument("There is no div with that description"); //If not it returns -1
		divs.moveTo(toFindPos, description.c_str(), toMove); //Then move the tag from the div container to the desired position
	}
	else
	{
		if (toMove >= tags.getSize()) //If the new position is bigger then the current size of the container 
			throw std::invalid_argument("Invalid position");

		int toFindPos = tags.tagExist(description); // //Check to see if div tag with that description exist
		if (toFindPos < 0) //Check to see if div tag with that description exist
			throw std::invalid_argument("There is no such tag"); //If not it returns -1
		tags.moveTo(toMove, toFindPos); //Then move the tag from the div container to the desired position
	}

	std::cout << "Tag " << description << " has been moved to position " << toMove << std::endl;

	upToDate = false; //Remainder to save the update the file before exit
}

void Coomands::print(const bool& divEncountered, std::string divDescr) const
{
	if (!fileLoaded)
		throw std::invalid_argument("File must first be loaded");

	if (divEncountered) //If the User is working with a div tag
		divs.print(divDescr.c_str());
	else //For normal tags
	{
		std::cout << std::endl;
		for (int count = 0; count < tags.getSize(); ++count)
		{
			tags.print(count);
			std::cout << std::endl;
			if (tags.returnType(count)== "div")  //If there is a div tag inside the container
				divs.print(tags.getDescr(count).c_str()); //Prints the contents inside the div tag 
		}
	}
}

void Coomands::load(std::string filename)
{
	if (fileLoaded) //If it is not the first load
	{
		if (this->filename== filename)  //Check if the file is already loaded
			throw(std::invalid_argument("File already loaded"));
		newFile(); //Save the content of the previous file and clean up the containers
	}

	std::ifstream input(filename);

	//Quick check if the file exists
	//If it doesn't there is no need for loading
	if (!input.is_open())
	{	//Tries to create a new file
		std::cout << "File doesn't exist. Creating a new one\n";
		std::ofstream createFile(filename);
		if (!createFile.is_open()) //If the creation failed exits the loading
			std::cout << "File couldn't be created" << std::endl;
		createFile.close();
		//After the new file has been created saves its name for fture use
		changeFilename(filename);
		return;
	}

	bool divEncountered = false; //If a "<div>" line has been encountered
								//Means that a div tag is inside
	char buffer[MAX_SIZE];
	char divDescr[MAX_SIZE];

	//Read the contents before the "<body>" line
	do
	{
		input.getline(buffer, MAX_SIZE, '\n');
		if (input.eof())
			throw std::invalid_argument("File not valid");
	} while (strcmp(buffer, "<body>") != 0);	//And checks if there is a "<body>" line

	try
	{
		while (true)
		{
			int countBuffer = 0;
			input.getline(buffer, MAX_SIZE, '\n'); //Gets a line from the file

			if (strcmp(buffer, "</body>") == 0 || input.eof()) //If it reaches to "</body>" then all the tags in the file have been loaded
				break;

			if (tags.findPhrase(buffer, "<div descr=\"", countBuffer)) //Looks if there is a div tag in the file
			{
				if (tags.getCharUntil(buffer, divDescr, '\"', countBuffer)) //Tries to get the divs description
				{
					divEncountered = true;
					tags.newElem("div", divDescr, nullptr); //Adds the div in the regular container
					divs.newDiv(divDescr); //And adds it into the container for divs
				}
			}
			else if (strcmp(buffer, "</div>") == 0) //Signals that the div has ended
			{
				divEncountered = false;
			}
			else if (strcmp(buffer, "<br>") != 0) //Everything except <br>  
			{
				if (divEncountered)
					divs.load(buffer, divDescr);
				else
					tags.load(buffer);
			}
		}
	}
	catch (std::invalid_argument& ia)
	{	//If error is encountered when loading
		//The entire  file read is considered invalid and everything saved up to this point is deleted
		tags.destroyOldContent();
		divs.destroyOldContent();
		fileLoaded = false;
		throw;
	}

	changeFilename(filename); //After the loading has passed without error save the name of the file
	fileLoaded = true; //First loading has passed so at every other loading the contents must be saved in the file and the containers to be cleared
	upToDate = true;
	input.close();

	std::cout << "File loaded" << std::endl;
}

void Coomands::save(std::string filename)
{
	if (!fileLoaded)
		throw std::invalid_argument("File must first be loaded");

	if (this->filename != filename)  //Checks if the same file is loaded into the system
		throw (std::invalid_argument("Different file loaded"));

	std::ofstream output(filename);
	if (!output.is_open())
		throw (std::logic_error("File couldn't be opened"));

	//Outputs the first part of a HTML file
	output << "<!DOCTYPE html>" << std::endl;
	output << "<html>" << std::endl;
	output << "<head></head>" << std::endl;
	output << "<body>" << std::endl;

	for (int count = 0; count < tags.getSize(); ++count)
	{	//Save every tag from the regular container one by one
		tags.save(output, count);
		if (tags.returnType(count)=="div")  //If there are div tag in the regular container
			divs.save(output, tags.getDescr(count).c_str()); //Save every one of their items as well
	}

	//Outputs the last part of a HTML file
	output << "</body>" << std::endl;
	output << "</html>" << std::endl;

	output.close();

	upToDate = true; //Signals that every change made so far has been saved 
	std::cout << "File saved" << std::endl;
}

void Coomands::exit()
{
	if (!upToDate) //Check if every change made is saved
		save(filename);
}

void Coomands::newFile()
{	//When loading a new file the old one must be saved and the contents of the containers to be clear 
	std::cout << "New file loaded. Saving the contents of the previous one" << std::endl;
	if (!upToDate)
		save(filename);
	tags.destroyOldContent();
	divs.destroyOldContent();
}

bool Coomands::divTagExist(std::string divDescr)
{	//Checks if a tag exists in the container
	int tagPos = tags.tagExist(divDescr);
	if (tagPos < 0)
		throw std::invalid_argument("There is no such tag with that description");
	if (tags.returnType(tagPos)== "div") 
		return true;
	return false;
}

void Coomands::run()
{
	char filename[MAX_SIZE], //Used for storing the filename
		command[MAX_SIZE], //Used for storing the command
		content[MAX_SIZE], //Used for storing the content of each tag like text or image url
		description[MAX_SIZE], //Used for storing the tag description
		linkDescription[MAX_SIZE], //Used for storing the description to the link url
		divDescr[MAX_SIZE]; //Used for storing the description of the div

	int pos = 0; //Used for storing a position 

	bool exit = false; //Check if the program should exit

	bool divEncountered = false; //Check if div tag is in use

	Coomands S1;

	while (!exit)
	{
		try
		{
			std::cout << "Enter command: " << std::endl;
			inputFirst(command); //Inputs the first part of the command

					//Commands like print,exit,deselect don't need other input
			if (strcmp(command, "print") != 0 && strcmp(command, "exit") != 0 && strcmp(command, "deselect") != 0)
				inputRest(command, description, linkDescription, content, filename, pos, divDescr);

			if (strcmp(command, "add heading") == 0) //Heading
				S1.newElem("heading", description, content, nullptr, divEncountered, divDescr);
			else if (strcmp(command, "add text") == 0) //Text
				S1.newElem("text", description, content, nullptr, divEncountered, divDescr);
			else if (strcmp(command, "add image") == 0) //Image
				S1.newElem("image", description, content, nullptr, divEncountered, divDescr);
			else if (strcmp(command, "add video") == 0) //Video
				S1.newElem("video", description, content, nullptr, divEncountered, divDescr);
			else if (strcmp(command, "add link") == 0) //Link
				S1.newElem("link", description, content, linkDescription, divEncountered, divDescr);
			else if (strcmp(command, "add div") == 0)
				S1.newElem("div", description, nullptr, nullptr);
			else if (strcmp(command, "remove") == 0) //Remove tag
				S1.remove(description, divEncountered, divDescr);
			else if (strcmp(command, "print") == 0) //Prints content
				S1.print(divEncountered, divDescr);
			else if (strcmp(command, "moveTo") == 0) //Moves a tag to position
				S1.moveTo(pos, description, divEncountered, divDescr);
			else if (strcmp(command, "save") == 0) //Save
				S1.save(filename);
			else if (strcmp(command, "load") == 0) //Loads a file into the System
			{
				if (!checkFileExtension(filename, ".html")) //The files are required to have .html extension 
					throw std::invalid_argument("File does not have .html extension");
				S1.load(filename);
			}
			else if (strcmp(command, "select") == 0) //Selects a div tag 
			{
				if (!S1.divTagExist(divDescr)) //Check if a div with that description exists in the System
					throw std::invalid_argument("The tag with that description isn't a div tag");
				std::cout << "Working with div tag with description: " << divDescr << std::endl;
				divEncountered = true;
			}
			else if (strcmp(command, "deselect") == 0) //Deselects a div tag
			{										   //And continues to work with the System
				if (!divEncountered) //Error if there isn't any div tag selected
					throw std::invalid_argument("You are not working with any div tag");
				std::cout << "Deselecting div tag with description: " << divDescr << std::endl;
				divEncountered = false;
			}
			else if (strcmp(command, "exit") == 0) //Exits the program
			{
				S1.exit();
				exit = true;
			}
			else //If neither of the other ifs were triggered then the command must be invalid
				throw std::invalid_argument("Wrong command");
		}
		catch (std::invalid_argument& ia)
		{
			std::cerr << ia.what() << std::endl;
		}
		catch (std::bad_alloc& ba)
		{
			std::cerr << "Memory allocation problem" << std::endl;
		}
	}
}

void Coomands::changeFilename(std::string filename)
{
	this->filename== filename;
}

bool Coomands::checkFileExtension(const char* filename, const char* extension)
{
	int countFile = strlen(filename) - 1;
	int countExtn = strlen(extension) - 1;

	while (countExtn >= 0)
	{
		if (filename[countFile--] != extension[countExtn--]) //Compares the last char of each variable to see wheather the extension of valid
			return false;
	}
	return true;
}

void Coomands::inputFirst(char* str)
{
	char temp[MAX_SIZE];
	int countTemp = 0;
	while (temp[countTemp - 1] != ' ' && temp[countTemp - 1] != '\n' && temp[countTemp - 1] != '\t') //Gets a single char until one the delim char are met
		std::cin.get(temp[countTemp++]);

	char lastChar = temp[countTemp - 1]; //Saves the last char with the delim char
	temp[countTemp - 1] = 0;

	if (strcmp(temp, "print") == 0 || strcmp(temp, "exit") == 0 || strcmp(temp, "deselect") == 0) //For commands like print,deselect,exit any further input is not required
	{
		if (lastChar != '\n')
		{
			char ch = 0;
			do
			{ //Checks if there is any other input after the commands
				std::cin.get(ch);
				if (ch == '\n')
					break;
				if (ch != '\n' && ch != ' ' && ch != '\t') //Spaces and tabs are considered valid input 
				{
					std::cin.ignore(MAX_SIZE, '\n');
					throw std::invalid_argument("Wrong input");
				}
			} while (ch == ' ' || ch == '\t');
		}
		strcpy(str, temp);
		return;
	}

	if (lastChar == '\n')
		throw std::invalid_argument("Wrong command");

	temp[countTemp - 1] = lastChar;
	temp[countTemp] = 0;

	if (strcmp(temp, "add ") == 0) //If the command is for adding new tags
	{
		do
		{
			std::cin.get(temp[countTemp++]);
		} while (temp[countTemp - 1] != ' ' && temp[countTemp - 1] != '\n' && temp[countTemp - 1] != '\t');
	}

	if (temp[countTemp - 1] == '\n') //The last char can't be newline because more data should be added
		throw(std::invalid_argument("Incomplete input"));

	temp[countTemp - 1] = 0;
	strcpy(str, temp);
}

void Coomands::inputRest(const char* command, char* description, char* linkDescription, char* content, char* filename, int& pos, char* divDescr)
{										//For heading,text,image,video
	if (strcmp(command, "add text") == 0 || strcmp(command, "add heading") == 0 || strcmp(command, "add image") == 0 || strcmp(command, "add video") == 0 || strcmp(command, "add link") == 0)
	{
		char ch = 0;
		while (true)
		{	//Ignores spaces and tabs until '<' is met
			std::cin.get(ch);
			if (ch == '<')
				break;
			if (ch == '\n') //If newline is met then the input is invalid
				throw std::invalid_argument("Input too short");
			if (ch != ' ' && ch != '\t') //If any other char is not space or tab then the input is invalid
			{
				std::cin.ignore(MAX_SIZE, '\n');
				throw std::invalid_argument("Wrong command");
			}
		}

		int countDescr = 0; //Gets the tag Description
		while (description[countDescr - 1] != '>' && description[countDescr - 1] != '\n')
			std::cin.get(description[countDescr++]);

		//If the last char is newline then the input is invalid because the content of the tag must be inputed
		if (description[countDescr - 1] == '\n')
			throw std::invalid_argument("Invalid input");

		description[countDescr - 1] = 0;

		do
		{   //Look ahead to see if there is a newline while skipping spaces and tabs
			std::cin.get(ch);
			if (ch == '\n')
				throw std::invalid_argument("Wrong command");
		} while (ch == ' ' || ch == '\t');

		int countCont = 0;
		content[countCont++] = ch;

		do
		{
			std::cin.get(content[countCont++]);
		} while (content[countCont - 1] != '\n');

		content[countCont - 1] = 0;

		//Continuation of link input
		if (strcmp(command, "add link") == 0)
		{	//For the link tag there is another input which is the description of the link url
			int countLink = 0;
			do
			{
				std::cin.get(linkDescription[countLink++]);
			} while (linkDescription[countLink - 1] != '\n');
			linkDescription[countLink - 1] = 0;
		}
		return;
	}

	//For adding div tag
	if (strcmp(command, "add div") == 0)
	{
		char ch = 0;

		while (ch != '<')
		{	//Ignores spaces and tabs until '<' is met
			std::cin.get(ch);
			if (ch == '\n') //If newline is met then the input is invalid
				throw std::invalid_argument("Input too short");
			if (ch != ' ' && ch != '\t') //If any other char is not space or tab then the input is invalid
			{
				std::cin.ignore(MAX_SIZE, '\n');
				throw std::invalid_argument("Wrong command");
			}
		}

		//For the div tag only a Description a needed
		int countDescr = 0;
		do
		{
			std::cin.get(description[countDescr++]);
			if (description[countDescr - 1] == '\n')
				throw std::invalid_argument("Wrong input");
		} while (description[countDescr - 1] != '>');
		description[countDescr - 1] = 0;

		do
		{ //Checks if there is any other input after the Descriptions
			std::cin.get(ch);
			if (ch == '\n')
				break;
			if (ch != '\n' && ch != ' ' && ch != '\t') //Spaces and tabs are considered valid input 
			{
				std::cin.ignore(MAX_SIZE, '\n');
				throw std::invalid_argument("Wrong input");
			}
		} while (ch == ' ' || ch == '\t');
		return;
	}

	//Remove post
	if (strcmp(command, "remove") == 0)
	{
		//When removing posts only their Description is needed
		int countDescr = 0;
		do
		{
			std::cin.get(description[countDescr++]);
		} while (description[countDescr - 1] != '\n');

		description[countDescr - 1] = 0;
		return;
	}

	//For moving to Pos
	if (strcmp(command, "moveTo") == 0)
	{
		std::cin >> pos; //The new move position 

		if (std::cin.fail()) //If a number is not entered then the cin flag is triggered
		{
			std::cin.clear();
			std::cin.ignore(MAX_SIZE, '\n');
			throw std::invalid_argument("Wrong input");
		}

		char tempCh = 0;
		do
		{   //Ignores spaces and tabs until something other is met 
			std::cin.get(tempCh);
			if (tempCh == '\n') //Unless it is a newline
				throw std::invalid_argument("Input too short");
		} while (tempCh == ' ' || tempCh == '\t');

		int countDescr = 0;
		description[countDescr++] = tempCh;

		do
		{	//Gets the tag Description 
			std::cin.get(description[countDescr++]);
		} while (description[countDescr - 1] != '\n');

		description[countDescr - 1] = 0;
		return;

	}

	//For saving and loading
	if (strcmp(command, "save") == 0 || strcmp(command, "load") == 0)
	{
		char tempCh = 0;
		do
		{   //Ignores spaces and tabs until something other is met 
			std::cin.get(tempCh);
			if (tempCh == '\n') //Unless it is a newline
				throw std::invalid_argument("Input too short");
		} while (tempCh == ' ' || tempCh == '\t');

		int countFile = 0;
		filename[countFile++] = tempCh;
		do
		{	//Gets the name of the file
			std::cin.get(filename[countFile++]);
		} while (filename[countFile - 1] != '\n');

		filename[countFile - 1] = 0;
		return;
	}

	//For selecting a div tag
	if (strcmp(command, "select") == 0)
	{
		char tempCh = 0;
		do
		{   //Ignores spaces and tabs until something other is met 
			std::cin.get(tempCh);
			if (tempCh == '\n') //Unless it is a newline
				throw std::invalid_argument("Input too short");
		} while (tempCh == ' ' || tempCh == '\t');

		int countDiv = 0;
		divDescr[countDiv++] = tempCh;
		do
		{
			std::cin.get(divDescr[countDiv++]);
		} while (divDescr[countDiv - 1] != '\n');
		divDescr[countDiv - 1] = 0;
		return;
	}

	//If the command isn't valid
	std::cin.ignore(MAX_SIZE, '\n');
	throw std::invalid_argument("Wrong command");
}
