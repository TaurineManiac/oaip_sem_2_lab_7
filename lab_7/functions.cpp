#include <cmath>

#include "header.h"
#include "inputCheck.h"
#include "generate.h"
#include <iostream>
#include <math.h>

using namespace std;
using namespace generate;

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

bool HashTable::isFool() {
    for (int i = 0; i < SIZE; i++) {
        if (table[i] == nullptr) {
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
    int randomSolution = generateRandomNumber(1, 3);
    int index=0;
    if (randomSolution==1) {
        for (int i = 0; i < key.length(); ++i) {
            index += key[i];
        }
        index %= SIZE;
    }else if (randomSolution==2) {
        int k;
        // Полиномиальное хеширование с другим множителем
        for (int i = 0; i < key.length(); ++i) {
            k = k * 33 + static_cast<unsigned char>(key[i]);
        }
        index = k % SIZE;
    }
    else if (randomSolution==3) {
        double A = (sqrt(5)- 1)/2;// золотое сечение
        int k=0;
        for (int i = 0; i < key.length(); ++i) {
            k = k*31 + key[i];
        }
        double product = A*k;
        int fractionalPart = product - floor(product );
        index = fractionalPart*SIZE;
    }

    Node* newNode = new Node(key);
    if (table[index] == nullptr) {
        table[index] = newNode;
        cout << "Вставлен ключ '" << key << "' в ячейку " << index << " (без коллизии)" << endl;
    } else {
        // Пытаемся найти свободную ячейку через линейное опробование
        int originalIndex = index;
        int i = 0;
        bool inserted = false;

        while (i < SIZE) {
            if (table[index] == nullptr) {
                table[index] = newNode;
                cout << "Коллизия! Вставлен ключ '" << key << "' в ячейку " << index << " (линейное опробование)" << endl;
                inserted = true;
                break;
            }
            i++;
            index = (originalIndex + i) % SIZE;
        }

        // Если свободная ячейка не найдена, добавляем в цепочку
        if (!inserted) {
            newNode->next = table[originalIndex];
            table[originalIndex] = newNode;
            cout << "Коллизия! Вставлен ключ '" << key << "' в ячейку " << originalIndex << " (добавлен в список)" << endl;
        }
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