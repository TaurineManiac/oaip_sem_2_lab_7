#ifndef LAB_7_HEADER_H
#define LAB_7_HEADER_H

#include <iostream>
#include <string>

using namespace std;

class Node {
private:
    string key;
    Node* next;
public:
    Node();
    Node(const string& key);  // Добавляем const
    friend class HashTable;
};

class HashTable {
private:
    static const int SIZE = 100;
    Node* table[SIZE];
public:
    HashTable();
    ~HashTable();
    void insert(const string& key);
    string findShortestKey();
    bool isEmpty();
    void print();
};

#endif //LAB_7_HEADER_H
