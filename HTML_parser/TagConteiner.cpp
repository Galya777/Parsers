#include "TagConteiner.h"

TagConteiner::TagConteiner():size(0), maxSize(10), tags(nullptr)
{
	tags= new Tags * [1000];
	
}

TagConteiner::~TagConteiner()
{
	clean(size);
}

void TagConteiner::newElem(std::string type, std::string description, std::string content, std::string link)
{
	if (tagExist(description) >= 0) //Every tag must have unique description
		throw std::invalid_argument("Tag with that description already exists");

	if (size == maxSize) //Check for size
		resize();

	if (type== "heading")
		tags[size++] = new Heather(description, content);
	if (type== "image")
		tags[size++] = new Image(description, content);
	if (type== "link")
		tags[size++] = new Link(description, content, link);
	if (type== "text") 
		tags[size++] = new Text(description, content);
	if (type== "video") 
		tags[size++] = new Video(description, content);
	if (type== "div")
		tags[size++] = new Div(description, "");
}

void TagConteiner::remove(const int& curr)
{
	if (curr >= size || curr < 0)
		throw std::invalid_argument("Invalid position");

	sort(curr);
}

void TagConteiner::moveTo(const int& from, const int& to)
{
	//Moves a tag to a set position
	if (from > to || from < 0) //If the tags current position is bigger then the new position
		moveHighToLow(from, to);
	else
		moveLowToHigh(from, to);
}

void TagConteiner::print(const int& curr) const
{
	if (curr >= size || curr < 0) //If the position set to be printed is not in the range of the container
		throw std::invalid_argument("Invalid position");

	std::cout << "Position: " << curr;
	tags[curr]->print();
}

void TagConteiner::destroyOldContent()
{
	clean(size);
}

void TagConteiner::load(const char* buffer)
{
	int count = 0, //Used for buffer var
		countType = 0; //Used for findType var
	char findType[MAX_SIZE];

	char description[MAX_SIZE],
		content[MAX_SIZE],
		text[MAX_SIZE];

	char type = 0;
	char tempCh = 0;
	do
	{	//Skips the spaces and tabs in the buffer before the actual content
		tempCh = buffer[count++];
		if (tempCh == '\n' || tempCh == 0) //If newline or terminating char are met in the buffer 
		{								  //then there must an error
			clean(size);
			throw std::invalid_argument("File not valid");
		}
	} while (tempCh == ' ' || tempCh == '\t');

	findType[countType++] = tempCh;

	while (true)
	{	//Find what type of tag is contained in the buffer
		findType[countType++] = buffer[count++];
		findType[countType] = 0;

		if (strcmp(findType, "<h2 ") == 0)
		{
			type = 'h'; //Heading
			break;
		}
		if (strcmp(findType, "<p ") == 0)
		{
			type = 't'; //Text
			break;
		}

		if (strcmp(findType, "<img ") == 0)
		{
			type = 'i'; //Image
			break;
		}

		if (strcmp(findType, "<iframe ") == 0)
		{
			type = 'v'; //Video
			break;
		}

		if (strcmp(findType, "<a href=\"") == 0)
		{
			type = 'l'; //Link
			break;
		}

		if (buffer[count - 1] == '\n' || buffer[count - 1] == 0) //If newline or terminating char are met in the buffer
		{													//then there must an error
			//clean(size);
			throw std::invalid_argument("File not valid");
		}
	}

	if (type == 'h' || type == 't') //Heading or Text
	{
		if (!findPhrase(buffer, "descr=\"", count)) //Look for description in the buffer
			throw std::invalid_argument("File not valid");
		if (!getCharUntil(buffer, description, '\"', count)) //Gets the tags description in the buffer
			throw std::invalid_argument("File not valid");
		if (!getCharUntil(buffer, content, '<', count)) //Gets the tags content in the buffer
			throw std::invalid_argument("File not valid");

		if (type == 'h') //Create a new tag object
			newElem("heading", description, content);
		else if (type == 't')
			newElem("text", description, content);
	}

	if (type == 'i')
	{
		if (!findPhrase(buffer, "src=\"", count)) //Look for the image url in the buffer
			throw std::invalid_argument("File not valid");
		if (!getCharUntil(buffer, content, '\"', count)) //Gets the tag image url in the buffer 
			throw std::invalid_argument("File not valid");
		if (!findPhrase(buffer, "descr=\"", count)) //Look for the descriptions in the buffer
			throw std::invalid_argument("File not valid");
		if (!getCharUntil(buffer, description, '\"', count)) //Get the tag description from the buffer
			throw std::invalid_argument("File not valid");

		newElem("image", description, content); //Create a new image object
	}

	if (type == 'v')
	{
		if (!findPhrase(buffer, "src=\"", count)) //Look for the video url in the buffer
			throw std::invalid_argument("File not valid");
		if (!getCharUntil(buffer, content, '\"', count))  //Gets the tag video url from the buffer 
			throw std::invalid_argument("File not valid");
		if (!findPhrase(buffer, "descr=\"", count)) //Look for the descriptions in the buffer
			throw std::invalid_argument("File not valid");
		if (!getCharUntil(buffer, description, '\"', count)) //Get the tag description from the buffer
			throw std::invalid_argument("File not valid");

		newElem("video", description, content, nullptr); //Create a new video object
	}

	if (type == 'l')
	{
		if (!getCharUntil(buffer, content, '\"', count))  //Gets the tag link url from the buffer
			throw std::invalid_argument("File not valid");
		if (!findPhrase(buffer, "descr=\"", count)) // //Look for the descriptions in the buffer
			throw std::invalid_argument("File not valid");
		if (!getCharUntil(buffer, description, '\"', count)) //Get the tag description from the buffer
			throw std::invalid_argument("File not valid");
		if (!getCharUntil(buffer, text, '<', count)) //Get the tags content from the buffer
			throw std::invalid_argument("File not valid");

		newElem("link", description, content, text); //Create a new Link object
	}
}

void TagConteiner::save(std::ostream& out, const int& current) const
{
	tags[current]->saveHTML(out); //Save everything from the container to the HTML file
}

int TagConteiner::tagExist(std::string container) const
{	//Look if a tag with the diven description exist
	for (int count = 0; count < size; ++count)
		if (tags[count]->checkDescr(container))
			return count;
	return -1;
}

int TagConteiner::getSize() const
{
	return size; //Return the number of tags in the container
}

std::string TagConteiner::getDescr(const int& pos) const
{
	if (pos >= size)
		throw std::invalid_argument("Position is too big");
	return tags[pos]->getDescr(); //Returns the description of a tag based on its position
}

std::string TagConteiner::returnType(const int& pos) const
{
	if (pos >= size)
		throw std::invalid_argument("Position is too big");
	return tags[pos]->returnType(); //Returns which type of tag based on its position
}

void TagConteiner::clean(const int& current) //Clear the container from all of its data
{
	for (int count = 0; count < current; ++count)
		delete tags[count];
	delete[] tags;

	tags = nullptr;
	size = 0;
	maxSize = 0;
}

void TagConteiner::resize() //Resizes the container by increasing its maximal size by 2
{
	if (maxSize == 0)
	{
		tags = new Tags * [maxSize + 10];
		maxSize = 10;
	}
	else
	{
		Tags** temp = new Tags * [maxSize * 2]; //Creates a new temp pointer
		for (int count = 0; count < size; ++count)
			temp[count] = tags[count]; //Sets the new pointer to point to the old data

		delete[] tags;
		tags = temp;
		maxSize *= 2;
	}
}

void TagConteiner::sort(const int& toRemove) //
{
	delete tags[toRemove];
	for (int count = toRemove; count < size - 1; ++count)
	{	//Swap the tags until the one set to be deleted is at the end of the container
		Tags* temp = tags[count];
		tags[count] = tags[count - 1];
		tags[count - 1] = temp;
	}
	size -= 1;
}

void TagConteiner::moveLowToHigh(const int& startPos, const int& endPos)
{
	for (int count = startPos; count < endPos; ++count)
	{
		Tags* temp = tags[count];
		tags[count] = tags[count + 1];
		tags[count + 1] = temp;
	}
}

void TagConteiner::moveHighToLow(const int& startPos, const int& endPos)
{
	for (int count = startPos; count > endPos; --count)
	{
		Tags* temp = tags[count];
		tags[count] = tags[count - 1];
		tags[count - 1] = temp;
	}
}

bool TagConteiner::getCharUntil(const char* buffer, char* toLoad, const char& delim, int& count)
{
	char tempCh = 0;
	do
	{	//Skips the spaces,tabs and arrow before the actual content
		tempCh = buffer[count++];
		if (tempCh == '\n' || tempCh == 0) //If a newline or terminating char is encountered
			return false; 	//Then there must be an error
	} while (tempCh == ' ' || tempCh == '\t' || tempCh == '<' || tempCh == '>');

	int countLoad = 0;
	toLoad[countLoad++] = tempCh;

	while (true)
	{	//Starts loading from the buffer until a delim char is met
		toLoad[countLoad++] = buffer[count++];
		if (buffer[count - 1] == delim)
		{
			toLoad[countLoad - 1] = 0;
			break;
		}

		if (buffer[count - 1] == '\n' || buffer[count - 1] == 0) //If a newline or terminating char is encountered 	
			return false;										//Then there must be an error
	}
	return true;
}

bool TagConteiner::findPhrase(const char* buffer, const char* toMatch, int& count)
{
	char tempCh = 0;
	do
	{	//Skips the spaces and tabs before the actual content
		tempCh = buffer[count++];
		if (tempCh == '\n' || tempCh == 0) //If a newline or terminating char is encountered 
		{								//Then there must be an error
			//throw std::invalid_argument("File not valid");
			return false;
		}
	} while (tempCh == ' ' || tempCh == '\t');

	char newBuffer[MAX_SIZE];
	int countLoad = 0;
	newBuffer[countLoad++] = tempCh;

	while (true)
	{	//Starts loading from the buffer until a delim phrase is met
		newBuffer[countLoad++] = buffer[count++];
		newBuffer[countLoad] = 0;

		if (strcmp(newBuffer, toMatch) == 0)
			return true;

		if (strlen(newBuffer) > strlen(toMatch))
			return false;

		if (buffer[count - 1] == '\n' || buffer[count - 1] == 0)
			return false;
	}
}
