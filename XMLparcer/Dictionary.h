#pragma once
#include <iostream>
#include <string.h>
/*
* This class represents a helper template class.
* It is a dictionary for XML language 
*/
template<typename K, typename V>
///Struct that represents a pair
struct Pair {
    K first;
    V second;
};
template<typename K, typename V>
class Dictionary
{
public:
    ///конструктор със стойности по подразбиране
    Dictionary();
    ///копиращ конструктор
    Dictionary(const Dictionary<K, V>& other);
    ///оператор =
    Dictionary<K, V>& operator=(const Dictionary<K, V>& other);
    ///функция за добавяне на нова двойка
    void add(const K& key, const V& value);
    ///премахване на двойка по даден ключ-----------------------------------------------------------------
    bool remove(const K& key);
    ///намира двойка по даден ключ
    const V& find(const K& key) const;
    ///връща масива от двойките
    const Pair<K, V>* getPairs() const;
    ///проверява за наличието на ключ
    bool hasKey(const K& key) const;
    ///задава стойност на двойката
    bool setValue(const K& key, const V& value);
    ///принтира наличните двойки
    void print() const;
    ///връща размера
    int getSize() const;
    ///изчиства паметта
    void clear();
    ///деструктор
    ~Dictionary();
private:
    ///Pair that collects the data
    Pair<K, V>* data;
    ///size of the pairs
    int size;
    ///капацитет на двойките
    int capacity;
    ///get more space for more data
    void resize();
    ///clears the data
    void free() {
        delete[] data;
    }
    ///копиращ конструктор
    void copyFrom(const Dictionary<K, V>& other);
};

template<typename K, typename V>
inline Dictionary<K, V>::Dictionary()
{
    capacity = 4;
    size = 0;
    data = new Pair<K, V>[capacity];
}

template<typename K, typename V>
inline Dictionary<K, V>::Dictionary(const Dictionary<K, V>& other)
{
    copyFrom(other);
}

template<typename K, typename V>
inline Dictionary<K, V>& Dictionary<K, V>::operator=(const Dictionary<K, V>& other)
{
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
    // TODO: insert return statement here
}

template<typename K, typename V>
inline void Dictionary<K, V>::add(const K& key, const V& value)
{
    if (hasKey(key))
        throw "Key is already added in collection!";
    if (size == capacity)
        resize();
    int insertIndex = size;
    for (int i = 0; i < size; i++) {
        if (key < data[i].first) {
            insertIndex = i;
            break;
        }
    }
    for (int i = size; i > insertIndex; i--) {
        data[i] = data[i - 1];
    }
    data[insertIndex] = { key, value };
    size++;
}

template<typename K, typename V>
inline bool Dictionary<K, V>::remove(const K& key)
{
    int removeIndex = -1;
    for (int i = 0; i < size; i++)
        if (key == data[i].first) {
            removeIndex = i;
            break;
        }
    if (removeIndex == -1) return false;
    for (int i = removeIndex; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
    return true;
}

template<typename K, typename V>
inline const V& Dictionary<K, V>::find(const K& key) const
{
    for (int i = 0; i < size; i++)
        if (data[i].first == key)
            return data[i].second;
    throw "No such key in dictionary!";
    // TODO: insert return statement here
}

template<typename K, typename V>
inline const Pair<K, V>* Dictionary<K, V>::getPairs() const
{
    return data;
}

template<typename K, typename V>
inline bool Dictionary<K, V>::hasKey(const K& key) const
{
    for (int i = 0; i < size; i++) {
        if (key == data[i].first)
            return true;
    }
    return false;
}

template<typename K, typename V>
inline bool Dictionary<K, V>::setValue(const K& key, const V& value)
{
    for (int i = 0; i < size; i++) {
        if (key == data[i].first) {
            data[i].second = value;
            return true;
        }
    }
    add(key, value);
    return true;
}

template<typename K, typename V>
inline void Dictionary<K, V>::print() const
{
    for (int i = 0; i < size; i++) {
        std::cout << data[i].first << " " << data[i].second
            << std::endl;
    }
}

template<typename K, typename V>
inline int Dictionary<K, V>::getSize() const
{
    return size;
}

template<typename K, typename V>
inline void Dictionary<K, V>::clear()
{
    free();
    capacity = 4;
    data = new Pair<K, V>[capacity];
    size = 0;
}

template<typename K, typename V>
inline Dictionary<K, V>::~Dictionary()
{
    free();
}

template<typename K, typename V>
inline void Dictionary<K, V>::resize()
{
    capacity *= 2;
    Pair<K, V>* ptr = new Pair<K, V>[capacity];
    for (int i = 0; i < size; i++)
        ptr[i] = data[i];
    free();
    data = ptr;
}

template<typename K, typename V>
inline void Dictionary<K, V>::copyFrom(const Dictionary<K, V>& other)
{
    size = other.size;
    capacity = other.capacity;
    data = new Pair<K, V>[capacity];
    for (int i = 0; i < size; i++)
        data[i] = other.data[i];
}
