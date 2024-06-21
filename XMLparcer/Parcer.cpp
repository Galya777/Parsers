#include "Parcer.h"


const int EXCEPTION_PLACE_WIDTH = 20;

Parser::Parser(std::string filePath) {
    this->filePath = filePath;
    loadFileContent();
}

void Parser::setFilePath(std::string filePath) {
    this->filePath = filePath;
}

bool Parser::fileIsOpened() const {
    return filePath != "";
}

void Parser::loadFileContent() {
    if (filePath == "") {
        fileContent = "";
        return;
    }
    std::ifstream file(filePath);
    if (!file.is_open()) {
        fileContent = "";
        return;
    }
    while (!file.eof()) {
        if (file.peek() != '\t' && file.peek() != '\n') {
            char buffer[2];
            buffer[0] = file.get();
            buffer[1] = '\0';
            fileContent += buffer;
        }
        else file.get();
    }

    minify();
}

std::string Parser::getFilePath() const {
    return filePath;
}

bool isLetter(char c) {
    return (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z');
}

void Parser::minify() {
    std::string minifiedContent;
    int iter = 0;
    while (iter < fileContent.length()) {
        if (fileContent.substr(iter).find("  ")) {
            bool startsWithSpecialSymbol = fileContent.at(iter - 1) == '<'
                || fileContent.at(iter - 1) == '/'
                || fileContent.at(iter - 1) == '=';
            while (fileContent.at(iter) == ' ') {
                iter++;
            }
            bool endsWithSpecialSymbol = fileContent.at(iter) == '<'
                || fileContent.at(iter) == '/'
                || fileContent.at(iter) == '>'
                || fileContent.at(iter) == '=';
            if (!startsWithSpecialSymbol && !endsWithSpecialSymbol) minifiedContent += " ";
        }
        else if (fileContent.at(iter) == ' ') {
            bool startsWithSpecialSymbol = fileContent.at(iter - 1) == '<'
                || fileContent.at(iter - 1) == '/'
                || fileContent.at(iter - 1) == '=';

            bool endWithSpecialSymbol =
                (fileContent.at(iter + 1) == '<'
                    || fileContent.at(iter + 1) == '/'
                    || fileContent.at(iter + 1) == '=');
            if (startsWithSpecialSymbol || endWithSpecialSymbol)
                iter++;
            else minifiedContent += fileContent.at(iter++);
        }
        else {
            minifiedContent += fileContent.at(iter++);
        }
    }
    minifiedContent = minifiedContent.erase();
    fileContent = minifiedContent.substr(0, minifiedContent.length() - 1);
}

void Parser::parseNodeByTagInfo(std::string tagInfo, Element& node) const {
    int startIndex = tagInfo.find(" ");
    std::string type = tagInfo.substr(0, startIndex);
    node.setType(type);
    bool isInParenthesis = false;
    for (int i = (startIndex++) + 1; i < tagInfo.length(); i++) {
        if (!isInParenthesis && tagInfo.at(i) == '\"') {
            isInParenthesis = true;
        }
        else if (isInParenthesis && tagInfo.at(i) == '\"') {
            std::string attributeStr = tagInfo.substr(startIndex, i);
            std::vector<std::string> attributeData= split(attributeStr, '=');
            node.setAttribute(attributeData[0], attributeData[1]);
            if (attributeData[0] == "id") node.setId(attributeData[1]);
            startIndex = i + 2;
            isInParenthesis = false;
        }
    }
}

void Parser::parse(std::string elementTextContent, Tree& tree, const Element* parent, int& iter) const {
    std::string tagInfo;
    int searchingStartingIndex = iter;
    while (elementTextContent.at(iter) != '>') {
        tagInfo += elementTextContent.at(iter);
        iter++;
        if (iter >= elementTextContent.length() || elementTextContent.at(iter) == '<')
            throw "Parsing error! \n... "+elementTextContent.substr(searchingStartingIndex - EXCEPTION_PLACE_WIDTH, searchingStartingIndex + EXCEPTION_PLACE_WIDTH)
            +("... \nThere is a missing '>'");
    }
    Element node;
    parseNodeByTagInfo(tagInfo, node);
    iter++;
    std::string textContent;
    searchingStartingIndex = iter;
    while (elementTextContent.at(iter) != '<') {
        textContent += elementTextContent.at(iter);
        iter++;
        if (iter >= elementTextContent.length() || elementTextContent.at(iter) == '>')
            throw "Parsing error! \n... " + elementTextContent.substr(iter - EXCEPTION_PLACE_WIDTH, iter + EXCEPTION_PLACE_WIDTH)
            +("... \nThere is a missing '<'");
    }
    node.setTextContent(textContent);
    tree.addChild(parent->getId(), node);
    iter++;
    if (elementTextContent.at(iter) != '/')
        parse(elementTextContent, tree, tree.getLastChild(parent->getId()), iter);
    searchingStartingIndex = iter;
    while (elementTextContent.at(iter) != '>') {
        iter++;
        if (iter >= elementTextContent.length() || elementTextContent.at(iter) == '<')
            throw "Parsing error! \n... "+elementTextContent.substr(searchingStartingIndex - EXCEPTION_PLACE_WIDTH, searchingStartingIndex + EXCEPTION_PLACE_WIDTH)
            +("... \nThere is a missing '>'");
    }
    iter++;
    iter++;
    if (elementTextContent.at(iter) != 0 && elementTextContent.at(iter) != '/')
        parse(elementTextContent, tree, parent, iter);
}

void Parser::parseTree(Tree& tree) const {
    if (fileContent.length() <= 1) return;
    int iter = 0;
    parse(fileContent.substr(1), tree, tree.getRoot(), iter);
}
