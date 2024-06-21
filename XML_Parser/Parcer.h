#pragma once
#include <string>
#include "Element.h"
#include "Tree.h"
#include <fstream>
#include "HelpingFunctions.h"
/*
* Parsing the information to a file
* ������� ������������ ��� ����
*/
class Parser: HelpingFunctions
{
   
public:
    ///�����������
    Parser(std::string filePath = "");
    ///������ ���� ��� �����
    void setFilePath(std::string);
    ///��������� ���� ����� � �������
    bool fileIsOpened() const;
    ///������� �������
    void parseTree(Tree&) const;
    ///����� ���� �� �����
    std::string getFilePath() const;
    
private:   
    std::string filePath;
    std::string fileContent;
    ///������� ������������
    void parse(std::string, Tree&,const Element*, int&) const;
    ///������� ������������ �� ����
    void loadFileContent();
    ///minifizing 
    void minify();
    ///���������� �� ���������� �������
    void parseNodeByTagInfo(std::string, Element&) const;
};

