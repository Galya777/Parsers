#include "Element.h"

Element::Element(const std::string type, const std::string id, const std::string textContent, Element* parent)
{
    this->type = type;
    this->id = id;
    this->textContent = textContent;
}

bool Element::addChild(const Element& el)
{
    Element* child = new Element(el);
    this->children.push_back(child);
    return true;
}

bool Element::setTextContent(std::string textContent)
{
    this->textContent = textContent;
    return true;
}

bool Element::setId(std::string id)
{
    this->id = id;
    return true;
}

bool Element::setType(std::string type)
{
    this->type = type;
    return true;
}

bool Element::removeChild(std::string id)
{
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) {
            freeElement(children[i]);
            children.erase(children.begin()+i);
            return true;
        }
    }
    return false;
}

bool Element::removeDescendant(std::string id, Element* el)
{
    for (int i = 0; i < el->children.size(); i++) {
        if (el->children[i]->getId() == id) {
            el->children.erase(el->children.begin() + i);
            return true;
        }
        else if (removeDescendant(id, el->children[i])) {
            return true;
        }
    }
    return false;
}

bool Element::setAttribute(std::string key, std::string value)
{
    return attributes.setValue(key, value);
}

bool Element::hasAttribute(std::string key, std::string value) const
{
    try {
        if (value == "") {
            return attributes.hasKey(key);
        }
        else {
            return attributes.find(key) == value;
        }
    }
    catch (std::string str) {
        return false;
    }
}

bool Element::hasChild(std::string id) const
{
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->id == id) return true;
    }
    return false;
}

std::vector<const Element*> Element::getChildrenByType(std::string type) const
{
    std::vector<const Element*> res;
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->getType() == type) {
            res.push_back(children[i]);
        }
    }
    return res;
}

std::vector<const Element*> Element::getChildrenByAttribute(std::string key, std::string value) const
{
    std::vector<const Element*> res;
    for (int i = 0; i < children.size(); i++) {
        if (children[i]->hasAttribute(key, value)) {
            res.push_back(children[i]);
        }
    }
    return res;
}

std::vector<const Element*> Element::getChildrenByIndex(int index) const
{
    std::vector<const Element*> res;
    if (index < 0 || index >= children.size()) return res;
    res.push_back(children[index]);
    return res;
}

std::vector<const Element*> Element::getDescendants(const Element* current) const
{
    std::vector<const Element*> res;
    for (int i = 0; i < current->getChildren().size(); i++) {
        res.push_back(current->getChildren()[i]);
        res = getDescendants(current->getChildren()[i]);
    }
    return res;
}

bool Element::removeAttribute(std::string key)
{
    return attributes.remove(key);
}

const Element* Element::getChild(int index) const
{
    return children.at(index);
}

std::vector<Element*> Element::getChildren()
{
    return children;
}

std::vector<const Element*> Element::getChildren() const
{
    std::vector<const Element*> res;
    for (int i = 0; i < children.size(); i++) {
        res.push_back(children[i]);
    }
    return res;
}

const Element* Element::getLastChild() const
{
    if (children.size() == 0) return nullptr;
    return children[children.size() - 1];
}

const std::string Element::getText() const
{
    return textContent;
}

const std::string Element::getId() const
{
    return id;
}

const Dictionary<std::string, std::string>& Element::getAttributes() const
{
    return attributes;
    // TODO: insert return statement here
}

const std::string Element::getType() const
{
    return type;
}

void Element::saveInFile(std::ostream& os, int k) const
{
    for (int i = 0; i < k; i++)
        os << "\t";
    os << "<" << type;
    std::string s = "def";
    if (!(id==s)) os << " id=\"" << id << "\"";
    for (int i = 0; i < attributes.getSize(); i++) {
        if (attributes.getPairs()[i].first != "id") os << " " << attributes.getPairs()[i].first << "="
            << "\"" << attributes.getPairs()[i].second << "\"";
    }
    os << ">";
    os << textContent;
    if (!this->children.empty()) os << std::endl;
    for (int i = 0; i < this->children.size(); i++) {
        this->children[i]->saveInFile(os, k + 1);
    }
    if (!this->children.empty()) for (int i = 0; i < k; i++)
        os << "\t";
    os << "</" << type << ">" << std::endl;
}

void Element::print(std::ostream& os, int k) const
{
    for (int i = 0; i < k; i++)
        os << "\t";
    os << "<" << type;
    os << " id=\"" << id << "\"";
    for (int i = 0; i < attributes.getSize(); i++) {
        if (attributes.getPairs()[i].first != "id") os << " " << attributes.getPairs()[i].first << "="
            << "\"" << attributes.getPairs()[i].second << "\"";
    }
    os << ">";
    os << textContent;
    if (!this->children.empty()) os << std::endl;
    for (int i = 0; i < this->children.size(); i++) {
        this->children[i]->print(os, k + 1);
    }
    if (!this->children.empty()) for (int i = 0; i < k; i++)
        os << "\t";
    os << "</" << type << ">" << std::endl;
}

void freeElement(Element* el)
{
    for (int i = 0; i < el->children.size(); i++) {
        freeElement(el->children[i]);
    }
    delete el;
}
