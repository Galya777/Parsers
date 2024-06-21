#include "Tree.h"
#include <iostream>
#include <fstream>
using namespace std;
Tree::Tree()
{
	this->root = new Element("wrapper", "rootId");
}

Tree::~Tree() {
    freeElement(root);
}
const Element* Tree::getRoot() const {
    return root;
}

bool Tree::hasElementWithId(std::string id) const {
    return ids.hasKey(id);
}

void Tree::saveInFile(std::string filePath) const {
    ofstream file(filePath);
    for (int i = 0; i < root->getChildren().size(); i++) {
        root->getChildren()[i]->saveInFile(file);
    }
}

void Tree::print() const {
    for (int i = 0; i < root->getChildren().size(); i++) {
        root->getChildren()[i]->print(cout);
    }
}
const Element* Tree::getElementById(std::string id, const Element* el) const {
    if (el->getId() == id) return el;
    for (int i = 0; i < el->getChildren().size(); i++) {
        const Element* res = getElementById(id, el->getChildren()[i]);
        if (res != nullptr) {
            return res;
        }
    }
    return nullptr;
}
Element* Tree::getElementById(std::string id, Element* el) {
    if (el->getId() == id) return el;
    for (int i = 0; i < el->getChildren().size(); i++) {
        Element* res = getElementById(id, el->getChildren()[i]);
        if (res != nullptr) {
            return res;
        }
    }
    return nullptr;
}
bool Tree::printAttribute(std::string id, std::string key) const {
    const Element* el = getElementById(id, root);
    if (el == nullptr) return false;
    cout << el->getAttributes().find(key);
    return true;
}
void Tree::setAttribute(std::string id, std::string key, std::string value) {
    Element* el = getElementById(id, root);
    if (el == nullptr)
        throw ("There is no such element");
    el->setAttribute(key, value);
}
void Tree::setText(std::string id, std::string textContent) {
    Element* el = getElementById(id, root);
    if (el == nullptr)
        throw ("There is no such element");
    el->setTextContent(textContent);
}
void Tree::setId(std::string oldId, std::string newId) {
    Element* el = getElementById(oldId, root);
    if (el == nullptr)
        throw ("There is no such element");
    el->setId(newId);
    ids.add(newId, ids.find(oldId));
    ids.remove(oldId);
}
void Tree::printChildren(std::string id) const {
    const Element* el = getElementById(id, root);
    if (el == nullptr) return;
    if (el->getChildren().size() == 0) {
        cout << "There are no children of node with id " << id << endl;
    }
    for (int i = 0; i < el->getChildren().size(); i++) {
        el->getChildren()[i]->print(cout);
    }
}
const Element* Tree::getChildByIndex(std::string id, int index) const {
    const Element* el = getElementById(id, root);
    if (el == nullptr)
        throw std::string("There is no such element");
    return getElementById(id, root)->getChildren()[index];
}
const Element* Tree::getLastChild(std::string id) const {
    const Element* el = getElementById(id, root);
    if (el == nullptr)
        throw ("There is no such element");
    const Element* res = el->getLastChild();
    if (res == nullptr)
        throw ("Element has no children");
    return el->getLastChild();
}
bool Tree::deleteAttribute(std::string id, std::string key) {
    Element* el = getElementById(id, root);
    if (el == nullptr)
        throw ("There is no such element");
    return el->removeAttribute(key);
}
void Tree::addChild(std::string id, const Element& el) {
    Element* parent = getElementById(id, root);
    if (parent == nullptr)
        throw ("There is no such element");
    std::string idToBeAdded = el.getId();
    Element elToBeAdded = el;
    std::string s = std::to_string(countOfElements);
    if (idToBeAdded == "def") idToBeAdded = el.getId()+'_' + s;
    countOfElements++;
    elToBeAdded.setId(idToBeAdded);
    parent->addChild(elToBeAdded);
    ids.add(idToBeAdded, parent->getChildren()[parent->getChildren().size() - 1]);
}
const Element* Tree::getParent(std::string id) const {
    for (int i = 0; i < ids.getSize(); i++) {
        if (ids.getPairs()[i].second->hasChild(id)) return ids.getPairs()[i].second;
    }
    throw ("There is no such element");
}

const Element* Tree::getElement(std::string id) const {
    return getElementById(id, root);
}
void Tree::clear() {
    freeElement(root);
    root = new Element("wrapper", "rootId");
    ids.clear();
    countOfElements = 0;
}
bool Tree::remove(std::string id) {
    return Element::removeDescendant(id, root);
}

std::vector<const Element*> Tree::getElementsByTagName(std::string tagName) const {
    std::vector<const Element*> list;
    for (int i = 0; i < ids.getSize(); i++) {
        if (ids.getPairs()[i].second->getType() == tagName)
            list.push_back(ids.getPairs()[i].second);
    }
    return list;
}

std::vector<const Element*> Tree::getElementsByAttribute(std::string attribute, std::string value) const {
    std::vector<const Element*> list;
    for (int i = 0; i < ids.getSize(); i++) {
        if (value == "")
            if (ids.getPairs()[i].second->getAttributes().hasKey(attribute))
                list.push_back(ids.getPairs()[i].second);
            else if (ids.getPairs()[i].second->getAttributes().hasKey(attribute)
                && ids.getPairs()[i].second->getAttributes().find(attribute) == value)
                list.push_back(ids.getPairs()[i].second);
    }
    return list;
}

std::vector<const Element*> Tree::getDescendants(std::string id) const {
    const Element* el = getElementById(id, root);
    if (el == nullptr)
        throw ("There is no such element");
    return el->getDescendants(el);
}
