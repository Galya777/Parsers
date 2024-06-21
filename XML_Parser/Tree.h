#pragma once
#include "Dictionary.h"
#include "Element.h"
#include <vector>
class Tree: public Element
{
public:
    ///����������
    Tree();
    ///��������� �� ����������
    Tree(const Tree&) = delete;
    ///�������� =
    Tree& operator=(const Tree&) = delete;
    ///����������
    ~Tree();
    ///����� ������ �� �������
    const Element* getRoot() const;
    ///��������� ���� ���������� ������� ��� ������� �����
    bool hasElementWithId(std::string id) const;
    ///������� ��� ����
    void saveInFile(std::string filePath) const;
    ///�������� �� ������
    void print() const;
    ///������� ����������
    bool printAttribute(std::string id, std::string key) const;
    ///������ ��������
    void setAttribute(std::string id, std::string key, std::string value);
    ///������ �����
    void setText(std::string id, std::string textContent);
    ///������ ������� �����
    void setId(std::string oldId, std::string newId);
    ///�������� ��������� �� ����� �����
    void printChildren(std::string id) const;
    ///����� ��������� �� ������
    const Element* getChildByIndex(std::string id, int index) const;
    ///����� ��������� ���������
    const Element* getLastChild(std::string id) const;
    ///����� ��������
    const Element* getParent(std::string id) const;
    ///������� ����������
    bool deleteAttribute(std::string id, std::string key);
    ///������ ���������
    void addChild(std::string id, const Element& el);
    ///����� ������� �� ����� ������
    const Element* getElement(std::string id) const;
    ///�������� ������� �� ����� ������
    bool remove(std::string id);
    ///����� ������� �� ���
    std::vector<const Element*> getElementsByTagName(std::string tagName) const;
    ///����� ������� �� ��������
    std::vector<const Element*> getElementsByAttribute(std::string attribute, const std::string value = "") const;
    ///����� ������������ �� ����� ������
    std::vector<const Element*> getDescendants(std::string id) const;
    void clear();
private:
    Element* root;
    unsigned countOfElements = 0;
    Dictionary<std::string, const Element*> ids;
    Element* getElementById(std::string id, Element*);
    const Element* getElementById(std::string id, const Element*) const;
};

