#pragma once
#include "Dictionary.h"
#include "Element.h"
#include <vector>
class Tree: public Element
{
public:
    ///конструкор
    Tree();
    ///забранява се копирането
    Tree(const Tree&) = delete;
    ///оператор =
    Tree& operator=(const Tree&) = delete;
    ///деструктор
    ~Tree();
    ///връша корена на дървото
    const Element* getRoot() const;
    ///проверява дали съществува елемент със следния номер
    bool hasElementWithId(std::string id) const;
    ///записва във файл
    void saveInFile(std::string filePath) const;
    ///принтира на екрана
    void print() const;
    ///извежда атрибутите
    bool printAttribute(std::string id, std::string key) const;
    ///задава атрибути
    void setAttribute(std::string id, std::string key, std::string value);
    ///задава текст
    void setText(std::string id, std::string textContent);
    ///задава пореден номер
    void setId(std::string oldId, std::string newId);
    ///принтира налседник по даден номер
    void printChildren(std::string id) const;
    ///връща наследник по индекс
    const Element* getChildByIndex(std::string id, int index) const;
    ///връща последния наследник
    const Element* getLastChild(std::string id) const;
    ///връща родителя
    const Element* getParent(std::string id) const;
    ///изтрива атрибутите
    bool deleteAttribute(std::string id, std::string key);
    ///добавя наследник
    void addChild(std::string id, const Element& el);
    ///връща елемент по даден индекс
    const Element* getElement(std::string id) const;
    ///премахва елемент по даден индекс
    bool remove(std::string id);
    ///връша елемент по име
    std::vector<const Element*> getElementsByTagName(std::string tagName) const;
    ///връща елемент по атрибути
    std::vector<const Element*> getElementsByAttribute(std::string attribute, const std::string value = "") const;
    ///връща наследниците по даден индекс
    std::vector<const Element*> getDescendants(std::string id) const;
    void clear();
private:
    Element* root;
    unsigned countOfElements = 0;
    Dictionary<std::string, const Element*> ids;
    Element* getElementById(std::string id, Element*);
    const Element* getElementById(std::string id, const Element*) const;
};

