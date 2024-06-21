#pragma once
#include "Parcer.h"
#include "Element.h"
#include "Tree.h"
#include "HelpingFunctions.h"
/*
* Този клас представлява прогрмата и наличните ѝ функции
*/
class Commands: public HelpingFunctions
{
public:
    ///стартира програмата
    void run();

private:
    Parser parser;
    Tree tree;
    ///проверява за промяна
    bool hasChanged = false;
    ///отваря файла
    void openFile(std::string);
    ///затваря файла
    void closeFile();
    ///запазва файла
    void saveFile();
    ///запазва файла като
    void saveAs(std::string);
    ///помощ
    void help();
    ///изход
    bool exit();
    ///принтира резултата на екрана
    void print();
    ///принтира атрибутите
    void printAttribute(std::string id, std::string key);
    ///добавя атрибути
    void setAttribute(std::string id, std::string key, std::string value);
    ///принтира наследник по зададен номер
    void printChildren(std::string id);
    ///принтира родителя
    void printParent(std::string id);
    ///принтира по пореден номер
    void printChildByIndex(std::string id, int index);
    ///принтира текста
    void printText(std::string id);
    ///задава текст
    void setText(std::string id);
    ///задава пореден номер
    void setId(std::string oldId);
    ///премахва атрибутите
    void removeAttribute(std::string id, std::string key);
    ///добавя наследник
    void addChild(std::string id, std::string type);
    ///връща поредния номер
    void remove(std::string id);
    ///връща пътя
    void xmlPath(std::string xmlPath);
    ///принтира наследниците
    void printDescendants(std::string id);
    ///проверява дали файла е отворен
    bool fileIsOpened() const;

};

