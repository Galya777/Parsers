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
    ///�����������
    Element(const std::string type = DEFAULT_TYPE, const std::string id = DEFAULT_ID, const std::string textContent = DEFAULT_TEXT_CONTENT, Element* parent = nullptr);
    ///������ ��� ������� 
    bool addChild(const Element& el);
    ///������ �����
    bool setTextContent(std::string textContent);
    ///������� ��-��
    bool setId(std::string id);
    ///������� ����
    bool setType(std::string type);
    ///�������� �������
    bool removeChild(std::string id);
    ///�������� ���������
    static bool removeDescendant(std::string id, Element*);
    ///������ �������
    bool setAttribute(std::string key, std::string value);
    ///��������� ���� � ������� �������
    bool hasAttribute(std::string key, std::string value = "") const;
    ///��������� ���� ��� ���������
    bool hasChild(std::string id) const;
    ///����� ���������� ������ ����
    std::vector<const Element*> getChildrenByType(std::string type) const;
    ///����� ���������� ������ ��������
    std::vector<const Element*> getChildrenByAttribute(std::string key, std::string value = "") const;
    ///����� ���������� ������ ��������
    std::vector<const Element*> getChildrenByIndex(int index) const;
    ///����� ������ ����������
    std::vector<const Element*> getDescendants(const Element* el) const;
    ///�������� ��������
    bool removeAttribute(std::string key);
    ///����� ���������
    const Element* getChild(int index) const;
    std::vector<Element*> getChildren();
    std::vector<const Element*> getChildren() const;
    ///����� ��������� ���������
    const Element* getLastChild() const;
    ///����� ������
    const std::string getText() const;
    ///����� ��-��
    const std::string getId() const;
    ///����� ����������
    const Dictionary<std::string, std::string>& getAttributes() const;
    ///����� ����
    const std::string getType() const;
    ///������� ��� ����
    void saveInFile(std::ostream& os, int k = 0) const;
    ///�������� ��� ���� ��� �� ���������
    void print(std::ostream& os, int k = 0) const;
    ///�������� �������
    friend void freeElement(Element*);
private:
	std::string type;
	std::string id;
	std::string textContent;
	std::vector<Element*> children;
	Dictionary<std::string, std::string> attributes;
};

