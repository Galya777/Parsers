#include "Path.h"

std::vector<const Element*> Path::getElements(std::string path, const Tree& tree)
{
    std::vector<std::string> parts = split(path, '/');
    std::vector<const Element*> elementsToFind;
    for (int i = 0; i < parts.size(); i++) {
        int attributeIndexStart = parts[i]==("(");
        int childIndexStart = parts[i]==("[");
        std::string tagName;
        if (parts.at(i).at(parts.at(i).size())==')')
            tagName = parts[i].substr(0, attributeIndexStart);
        else if (parts.at(i).at(parts.at(i).size()) == ']')
            tagName = parts[i].substr(0, childIndexStart);
        else tagName = parts[i];
        if (i == 0) {
            if (!tagName.at(0)=='~') elementsToFind = tree.getElementsByTagName(tagName);
            else elementsToFind =tree.getRoot()->getChildren()[0]->getChildrenByType(tagName.substr(1));
        }
        else {
            std::vector<const Element*> updatedElementsToFind;
            for (int j = 0; j < elementsToFind.size(); j++) {
                if (tagName == "*") {
                    updatedElementsToFind.push_back(elementsToFind[j]);
                }
                else updatedElementsToFind.push_back(elementsToFind[j]);
            }
            elementsToFind = updatedElementsToFind;
        }
        if (parts.at(i).at(parts.at(i).size()) == ')') {
            std::string attributeData = parts[i].substr(attributeIndexStart + 1, parts[i].length() - 1);
            if (attributeData.find("&")) {
                std::string attributeType = attributeData.substr(1);
                std::vector<const Element*> updatedElementsToFind;
                for (int j = 0; j < elementsToFind.size(); j++) {
                    if (elementsToFind[j]->hasAttribute(attributeType))
                        updatedElementsToFind.push_back(elementsToFind[j]);
                }
                elementsToFind = updatedElementsToFind;
            }
            else {
                std::vector<std::string> pair = split(attributeData,'=');
                std::vector<const Element*> updatedElementsToFind;
                for (int j = 0; j < elementsToFind.size(); j++) {
                    if (elementsToFind[j]->hasAttribute(pair[0], pair[1]))
                        updatedElementsToFind.push_back(elementsToFind[j]);
                }
                elementsToFind = updatedElementsToFind;
            }
        }
        else if (parts.at(i).at(parts.at(i).size()) == ']') {
            std::string index = parts[i].substr(childIndexStart + 1, parts[i].length() - 1);
            int n = atoi(index.c_str());
            std::vector<const Element*> updatedElementsToFind;
            for (int j = 0; j < elementsToFind.size(); j++) {
                updatedElementsToFind.push_back(elementsToFind[j]);
            }
            elementsToFind = updatedElementsToFind;
        }
    }
    return elementsToFind;
}
