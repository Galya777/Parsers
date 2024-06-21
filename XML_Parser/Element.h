#pragma once
#include "Dictionary.h"
#include <iostream>
#include <vector>
#include <string>
/*
* Base class representing an element in general
* The other elements will be its children 
*/

///defsult vslues for empty element
	const std::string DEFAULT_ID = "def";
	const std::string DEFAULT_TEXT_CONTENT = "";
	const std::string DEFAULT_TYPE = "type";
	
class Element
{
public:
    ///конструктор
    Element(const std::string type = DEFAULT_TYPE, const std::string id = DEFAULT_ID, const std::string textContent = DEFAULT_TEXT_CONTENT, Element* parent = nullptr);
    ///добавя нов елемент 
    bool addChild(const Element& el);
    ///добавя текст
    bool setTextContent(std::string textContent);
    ///променя ид-то
    bool setId(std::string id);
    ///променя типа
    bool setType(std::string type);
    ///премахва елемент
    bool removeChild(std::string id);
    ///премахва наследник
    static bool removeDescendant(std::string id, Element*);
    ///приема атрибут
    bool setAttribute(std::string key, std::string value);
    ///проверява дали е зададен атрибут
    bool hasAttribute(std::string key, std::string value = "") const;
    ///проверява дали има наследник
    bool hasChild(std::string id) const;
    ///връща наследника според типа
    std::vector<const Element*> getChildrenByType(std::string type) const;
    ///връща наследника според атрибута
    std::vector<const Element*> getChildrenByAttribute(std::string key, std::string value = "") const;
    ///връща наследника според индекста
    std::vector<const Element*> getChildrenByIndex(int index) const;
    ///връща всички наследници
    std::vector<const Element*> getDescendants(const Element* el) const;
    ///премахва атрибута
    bool removeAttribute(std::string key);
    ///връща наследник
    const Element* getChild(int index) const;
    std::vector<Element*> getChildren();
    std::vector<const Element*> getChildren() const;
    ///връща последния наследник
    const Element* getLastChild() const;
    ///връща текста
    const std::string getText() const;
    ///връша ид-то
    const std::string getId() const;
    ///връща атрибутите
    const Dictionary<std::string, std::string>& getAttributes() const;
    ///връща типа
    const std::string getType() const;
    ///записва във файл
    void saveInFile(std::ostream& os, int k = 0) const;
    ///принтира във файл или на конзолата
    void print(std::ostream& os, int k = 0) const;
    ///изчиства паметта
    friend void freeElement(Element*);
private:
	std::string type;
	std::string id;
	std::string textContent;
	std::vector<Element*> children;
	Dictionary<std::string, std::string> attributes;
};

