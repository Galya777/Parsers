#include "Commands.h"
#include <iostream>
#include "Path.h"
using namespace std;
const std::string END_OF_PROGRAM = "END_OF_PROGRAM";

void printDelimiter() {
    std::cout << "----------------------" << endl;
}
bool Commands::fileIsOpened() const {
    if (!parser.fileIsOpened()) {
        cout << "File hasn't been opened!" << endl;
        return false;
    }
    return true;
}
void Commands::openFile(std::string filePath) {
    if (parser.getFilePath() != "") {
        cout << "File has been already opened! Close it and try again!" << endl;
        return;
    }
    if (!hasEnding(filePath, ".xml")) {
        cout << "Wrong file format" << endl;
        return;
    }
    parser = Parser(filePath);
    try {
        parser.parseTree(tree);
        cout << "Successfully opened " << filePath << endl;
    }
    catch (std::string str) {
        parser.setFilePath("");
        cout << str << endl;
    }
}
void Commands::closeFile() {
    if (parser.getFilePath() != "") {
        parser.setFilePath("");
        tree.clear();
        cout << "Successfully closed file!" << endl;
        return;
    }
    cout << "File hasn't been opened!" << endl;
}
void Commands::saveFile() {
    tree.saveInFile(parser.getFilePath());
    cout << "Successfully saved " << parser.getFilePath() << endl;
    hasChanged = false;
}
void Commands::saveAs(std::string filePath) {
    tree.saveInFile(filePath);
    cout << "Successfully saved file in " << filePath << endl;
    hasChanged = false;
}
void Commands::help() {
    cout << "The following commands are supported: " << endl;
    cout << "  open <fileName>                    \t\t\topens <fileName>" << endl;
    cout << "  close                              \t\t\tcloses currently opened file" << endl;
    cout << "  save                               \t\t\tsaves the currently open file" << endl;
    cout << "  saveas <fileName>                  \t\t\tsaves the currently open file in <fileName>" << endl;
    cout << "  help                               \t\t\tprints this information" << endl;
    cout << "  exit                               \t\t\texits the program" << endl;
    cout << "  print                              \t\t\tprints the opened file" << endl;
    cout << "  select <id> <key>                  \t\t\tprints attribute to an element with <id> by key" << endl;
    cout << "  set <id> <key> <value>             \t\t\tsets attribute to an element with <id> by key and value" << endl;
    cout << "  children <id>                      \t\t\topens file" << endl;
    cout << "  child <id> <n>                     \t\t\tprints the n-th child of an element with <id>" << endl;
    cout << "  text <id>                          \t\t\tprints text of element with <id>" << endl;
    cout << "  settext <id>                       \t\t\tsets textContent of element with <id> to <newText>" << endl;
    cout << "  delete <id> <key>                  \t\t\tremoves attribute <key> from element with <id>" << endl;
    cout << "  newchild <id> <type>               \t\t\tcreates child element if <type> to element <id>\n                               \t\t\t\t\tPS: When adding element to an empty file\n                               \t\t\t\t\tyou should use 'rootId' as parent ID" << endl;
    cout << "  remove <id>                        \t\t\tremoves element with <id>" << endl;
    cout << "  xpath <xmlPath>                    \t\t\tperforms basic XPath requests" << endl;
    cout << "  setid <oldId> <newId>              \t\t\tsets id of <oldId> element to <newId>" << endl;
}
bool Commands::exit() {
    if (parser.getFilePath() != "" && hasChanged) {
        cout << "You have an open file with unsaved changes, please select close or save first." << endl;
        return false;
    }
    return true;
}
void Commands::print() {
    tree.print();
}
void Commands::printAttribute(std::string id,
    std::string key) {
    try {
        bool res = tree.printAttribute(id, key);
        if (!res) cout << "There is no such attribute to element " << id << endl;
        cout << endl;
    }
    catch (std::string str) {
        cout << str << endl;
    }
}
void Commands::setAttribute(std::string id, std::string key,
    std::string value) {
    try {
        tree.setAttribute(id, key, value);
        hasChanged = true;
    }
    catch (std::string str) {
        cout << str << endl;
        return;
    }

    cout << "Successfully set attribute " << key << " to " << value << endl;
}
void Commands::printChildren(std::string id) {
    try {
        tree.printChildren(id);
    }
    catch (std::string str) {
        cout << str << endl;
    }
}
void Commands::printParent(std::string id) {
    try {
        const Element* el = tree.getParent(id);
        el->print(cout);
    }
    catch (std::string str) {
        cout << str << endl;
    }
}
void Commands::printChildByIndex(std::string id, int index) {
    try {
        const Element* el = tree.getChildByIndex(id, index);
        el->print(cout);
    }
    catch (std::string str) {
        cout << str << endl;
    }
}
void Commands::printText(std::string id) {
    const Element* el = tree.getElement(id);
    if (el == nullptr) {
        cout << "There is no such element" << endl;
        return;
    }
    cout << el->getText() << endl;
}
void Commands::setText(std::string id) {
    cout << "> Enter node text content: ";
    std::string text;
    cin >> text;
    try {
        tree.setText(id, text);
        cout << "Successfully set textContent to " << id << endl;
        hasChanged = true;
    }
    catch (std::string str) {
        cout << str << endl;
    }
}
void Commands::setId(std::string oldId) {
    cout << "> Enter new ID: ";
    std::string newId;
    cin >> newId;
    try {
        if (newId.empty() | split(newId,' ').empty())
            throw ("Invalid ID");
        if (tree.hasElementWithId(newId))
            throw ("There is an element with the same ID.");
        tree.setId(oldId, newId);
        cout << "Successfully changed ID of element " << oldId << " to '" << newId << "'" << endl;
    }
    catch (std::string str) {
        cout << str << endl;
    }

}
void Commands::removeAttribute(std::string id, std::string key) {
    try {
        bool res = tree.deleteAttribute(id, key);
        if (res) cout << "Successfully removed attribute to an XML element" << endl;
        else cout << "Attribute removed unsuccessfully" << endl;
        hasChanged = true;
    }
    catch (std::string str) {
        cout << str << endl;
    }
}
void Commands::addChild(std::string id, std::string type) {
    Element el(type, DEFAULT_ID);
    cout << "> Enter node text content (optional): ";
    std::string textContent;
    cin >> textContent;
    el.setTextContent(textContent);
    try {
        tree.addChild(id, el);
    }
    catch (std::string str) {
        cout << str << endl;
        return;
    }
    cout << "Successfully added child." << endl;
    hasChanged = true;
}
void Commands::remove(std::string id) {
    try {
        bool res = tree.remove(id);
        if (res) {
            cout << "Successfully removed element" << endl;
            hasChanged = true;
        }
        else cout << "Element couldn't be found!" << endl;
    }
    catch (std::string str)
    {
        cout << str << endl;
    }

}
void Commands::xmlPath(std::string xmlPath) {
    std::vector<const Element*> elementsToFind = Path::getElements(xmlPath, tree);
    cout << "Elements: " << endl;
    for (int i = 0; i < elementsToFind.size(); i++) {
        elementsToFind[i]->print(cout);
    }
}
void Commands::printDescendants(std::string id) {
    try {
        std::vector<const Element*> res = tree.getDescendants(id);
        cout << "Descendants: " << endl;
        for (int i = 0; i < res.size(); i++) {
            res[i]->print(cout);
        }
    }
    catch (std::string str) {
        cout << str << endl;
    }

}
void Commands::run() {
    cout << "Welcome to XML Parser app. To continue, please enter a command or type \"help\" for more information." << endl;
    std::string input;
    while (input != END_OF_PROGRAM) {
        cout << "> ";
        cin >> input;
        try {
            std::vector<std::string> parts = split(input, ' ');
            std::string command = parts[0];
            if (command=="open") {
                openFile(input.substr(parts[0].length() + 1));
            }
            else if (command=="close") {
                if (fileIsOpened()) closeFile();
            }
            else if (command=="save") {
                if (fileIsOpened()) saveFile();
            }
            else if (command=="saveas") {
                if (fileIsOpened()) saveAs(parts[1]);
            }
            else if (command=="help") {
                help();
            }
            else if (command=="exit") {
                if (exit()) input = END_OF_PROGRAM;
            }
            else if (command=="print") {
                if (fileIsOpened()) print();
            }
            else if (command=="select") {
                if (fileIsOpened()) printAttribute(parts[1], parts[2]);
            }
            else if (command=="set") {
                if (fileIsOpened()) setAttribute(parts[1], parts[2], parts[3]);
            }
            else if (command=="children") {
                if (fileIsOpened()) printChildren(parts[1]);
            }
            else if (command=="child") {
                if (fileIsOpened()) printChildByIndex(parts[1], atoi(parts[2].c_str()));
            }
            else if (command=="text") {
                if (fileIsOpened()) printText(parts[1]);
            }
            else if (command=="delete") {
                if (fileIsOpened()) removeAttribute(parts[1], parts[2]);
            }
            else if (command=="newchild") {
                if (fileIsOpened()) addChild(parts[1], parts[2]);
            }
            else if (command=="parent") {
                if (fileIsOpened()) printParent(parts[1]);
            }
            else if (command=="remove") {
                if (fileIsOpened()) remove(parts[1]);
            }
            else if (command=="clear") {
                system("CLS");
            }
            else if (command=="settext") {
                if (fileIsOpened()) setText(parts[1]);
            }
            else if (command=="xpath") {
                if (fileIsOpened()) xmlPath(parts[1]);
            }

            else if (command=="descendants") {
                if (fileIsOpened()) printDescendants(parts[1]);
            }
            else if (command=="setid") {
                if (fileIsOpened()) setId(parts[1]);
            }
            else {
                cout << "Wrong command. Type 'help' to learn more." << endl;
            }
        }
        catch (int value)
        {
            cout << "Input error!" << endl;
        }

        printDelimiter();
    }
    cout << "Exiting program..." << endl;
}