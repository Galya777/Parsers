#include "JSONtYPE.h"

ObjectJSON* JSONtYPE::CreateFromFile(std::string filname)
{
    std::fstream file(filname);

    if (!file.is_open())
        throw std::invalid_argument("File err");

    ObjectJSON* obj;
    cur = 0;

    init(file);
    file.close();

    if (jsFile[cur] != '{')
        throw std::invalid_argument("invalid file content >> { exp");

    size = jsFile.size();

    obj = CreateJSONObject();

    return obj;
}

Base* JSONtYPE::CreateFromString(std::string string)
{
    Base* obj;
    initString(string);

    cur = 0;
    size = jsFile.size();

    obj = CreateNewItemValue();

    return obj;

}

ObjectJSON* JSONtYPE::CreateJSONObject()
{
    ObjectJSON* obj = new ObjectJSON;

    while (jsFile[cur] != '}')
    {
        if (cur >= size)
            throw std::invalid_argument("Broken object");

        if (jsFile[cur] != ',' && jsFile[cur] != '{')
            throw std::invalid_argument("Broken object ... missing ,");

        if (jsFile[cur + 1] == '}') {
            ++cur;
            break;
        }

        ++cur;
        std::string key = ItemKey();
        ++cur;
        Base* value = CreateNewItemValue();

        Item item(key, value);
        delete value;

        try {
            obj->addItem(item);
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }
    ++cur;
    return obj;
}

Base* JSONtYPE::CreateNewItemValue()
{
    Base* newValue;

    char ch = jsFile[cur];

    if (ch == '\"' || ch == '\'')
        newValue = CreateString();
    else if ((ch >= '0' && ch <= '9') || ch == '.' || ch == '+' || ch == '-')
        newValue = CreateNumber();
    else if (ch == '{')
        newValue = CreateJSONObject();
    else if (ch >= 'a' && ch <= 'z')
        newValue = CreateWordType();
    else if (ch >= 'A' && ch <= 'Z')
        newValue = CreateWordType();
    else if (ch == '[')
        newValue = CreateArray();
    else
        throw std::invalid_argument("no match");

    return newValue;

}

std::string JSONtYPE::ItemKey()
{
    std::string key;
    while (cur < size && jsFile[cur] != ':') {
        key += jsFile[cur];
        ++cur;
    }

    if (cur >= size)
        throw std::invalid_argument("Broken json missing separator");

    return key;

}

void JSONtYPE::init(std::istream& in)
{
    jsFile = "";
    char ch;
    bool instr = 0;
    while (!in.eof() && in.good()) {
        in.get(ch);

        if (ch == '\"' && jsFile[jsFile.size() - 1] != '\\')
            instr ^= 1;

        if (!in.eof())
            if (ch != '\n' && (ch != ' ' || instr))
                jsFile += ch;
    }
}

StringJSON* JSONtYPE::CreateString()
{
    std::string string;
    ++cur;
    // цикли докато не намери "
    // ако " участва в специален си то пред него ще има
    // само 1 '\'
    // Ако не намери " ще върти до края на json-а
    while (cur < size) {
        char ch = jsFile[cur];

        if (ch == '\"' || ch == '\'') {
            int br = 0;
            int i = cur - 1;
            while (jsFile[i] == '\\' && i > 0) {
                --i; ++br;
            }

            if (!br & 0x1)
                break;
        }

        string += ch;
        ++cur;
    }

    ++cur;
    string += '\0';

    if (cur == size)
        throw std::invalid_argument("\" not found! ");

    StringJSON* str = new StringJSON(string);

    return str;

}

NumberJSON* JSONtYPE::CreateNumber()
{
    std::string number;

    char ch = jsFile[cur];

    int dot_br = 0;
    do {
        number += ch;
        ++cur;
        ch = jsFile[cur];
    } while (cur < size && ch != ',' && ch != '}' && ch != ']');

    if (cur == size)
        std::invalid_argument("no end");
    int i = 0;
    if (number[0] == '+' || number[0] == '-') ++i;
    int num_size = number.size();
    for (; i < num_size; ++i) {
        if (number[i] == '.') ++dot_br;
        if (dot_br > 1 || ((number[i] < '0' || number[i]>'9') && number[i] != '.')) {
            throw std::invalid_argument(number + " is not numer");
        }
    }
    number.push_back('\0');
    double num = std::stod((char*)number.c_str());
    NumberJSON* numitem = new  NumberJSON(num);
    return numitem;
}

Base* JSONtYPE::CreateWordType()
{
    std::string word;
    char ch = jsFile[cur];
    do {
        word += ch;
        cur++;
        ch = jsFile[cur];
    } while (cur < size && ch != ',' && ch != '}' && ch != ']');

    int word_size = word.size();
    for (int i = 0; i < word_size; i++) {
        char& ch = word[i];

        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
    }

    if (word == "null")
        return new NULL_JSON;
    if (word == "true")
        return new BoolJSON(true);
    if (word == "false")
        return new BoolJSON(false);

    throw std::invalid_argument(word + " is not a vallid js type");

    return nullptr;
}

ArrayJSON* JSONtYPE::CreateArray()
{

    ArrayJSON* arr = new ArrayJSON;

    while (jsFile[cur] != ']')
    {
        if (cur >= size)
            throw std::invalid_argument("Broken object");

        if (jsFile[cur] != ',' && jsFile[cur] != '[')
            throw std::invalid_argument("Broken array");

        if (jsFile[cur + 1] == ']') {
            ++cur;
            break;
        }

        ++cur;
        Base* value = CreateNewItemValue();

        arr->addItem(value);
        delete value;
    }
    ++cur;
    return arr;

}

void JSONtYPE::initString(const std::string str)
{

    jsFile = "";
    char ch;
    bool instr = 0;
    int size = str.size();
    for (int i = 0; i < size; i++) {
        ch = str[i];

        if (ch == '\"' && jsFile[jsFile.size() - 1] != '\\')
            instr ^= 1;

        if (ch != '\n' && (ch != ' ' || instr))
            jsFile += ch;
    }

}
