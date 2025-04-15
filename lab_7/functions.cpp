#include "header.h"
#include "inputCheck.h"
#include "generate.h"
#include <iostream>

using namespace std;

Node::Node() : key(""), next(nullptr) {}

Node::Node(const std::string& key) : key(key), next(nullptr) {}

bool HashTable::isEmpty() {
    for (int i = 0; i < SIZE; i++) {
        if (table[i] != nullptr) {
            return false;
        }
    }
    return true;
}

HashTable::HashTable() {
    for (int i = 0; i < SIZE; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < SIZE; i++) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
}

void HashTable::insert(const std::string& key) {
    int index = 0;
    for (size_t i = 0; i < key.length(); ++i) {
        index += key[i];
    }
    index %= SIZE;
    Node* newNode = new Node(key);
    if (table[index] == nullptr) {
        table[index] = newNode;
        cout << "Вставлен ключ '" << key << "' в ячейку " << index << " (без коллизии)" << endl;
    } else {
        newNode->next = table[index];
        table[index] = newNode;
        cout << "Коллизия! Вставлен ключ '" << key << "' в ячейку " << index << " (добавлен в список)" << endl;
    }
}

string HashTable::findShortestKey() {
    if (isEmpty()) {
        cout << "Таблица пуста, нет ключей для поиска." << endl;
        return "";
    }

    string shortest = "";
    size_t minLength = string::npos;

    // Первый проход: находим минимальную длину и первый ключ с этой длиной
    for (int i = 0; i < SIZE; i++) {
        Node* current = table[i];
        while (current != nullptr) {
            int len = current->key.length();
            if (len < minLength) {
                minLength = len;
                shortest = current->key;
            }
            current = current->next;
        }
    }

    // Второй проход: выводим все ключи с минимальной длиной
    if (minLength != string::npos) {
        cout << "Самые короткие элементы (длина " << minLength << "): ";
        bool first = true;
        for (int i = 0; i < SIZE; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                if (current->key.length() == minLength) {
                    if (!first) cout << ", ";
                    cout << "'" << current->key << "'";
                    first = false;
                }
                current = current->next;
            }
        }
        cout << endl;
    }

    return shortest;
}

void HashTable::print() {
    if (isEmpty()) {
        cout << "\nХеш-таблица пуста." << endl;
        return;
    }

    cout << "\nХеш-таблица:\n";
    for (int i = 0; i < SIZE; i++) {
        if (table[i] != nullptr) {
            cout << "Ячейка " << i << ": ";
            Node* current = table[i];
            while (current) {
                cout << "'" << current->key << "' ";
                if (current->next) cout << "-> ";
                current = current->next;
            }
            cout << endl;
        }
    }
}