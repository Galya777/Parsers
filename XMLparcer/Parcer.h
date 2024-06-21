#pragma once
#include <string>
#include "Element.h"
#include "Tree.h"
#include <fstream>
#include "HelpingFunctions.h"
/*
* Parsing the information to a file
* Записва информацията във файл
*/
class Parser: HelpingFunctions
{
   
public:
    ///конструктор
    Parser(std::string filePath = "");
    ///задава пътя към файла
    void setFilePath(std::string);
    ///проверява дали файла е отворен
    bool fileIsOpened() const;
    ///записва дървото
    void parseTree(Tree&) const;
    ///връща пътя на файла
    std::string getFilePath() const;
    
private:   
    std::string filePath;
    std::string fileContent;
    ///записва информацията
    void parse(std::string, Tree&,const Element*, int&) const;
    ///зарежда информацията от файл
    void loadFileContent();
    ///minifizing 
    void minify();
    ///информация за съответния елемент
    void parseNodeByTagInfo(std::string, Element&) const;
};

