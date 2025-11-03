/*
 * Larry Smith
 * Project#4
 * CS 3100
 * Map ADT:HashTable
 * 11/3/2025
 */

#include <iostream>
#include <string>
#include <vector>
#include "HashTable.h"

using namespace std;

HashTableBucket::HashTableBucket() : key(""), value(0), type(bucketType::ESS) {
}

HashTableBucket::HashTableBucket(const string &key, const size_t &value) : key(key), value(value),
                                                                           type(bucketType::Normal) {
}

void HashTableBucket::load(const string &key, const size_t &value) {
    this->key = key;
    this->value = value;
    makeNormal();
}

bool HashTableBucket::isEmpty() const {
    return type == bucketType::ESS || type == bucketType::EAR;
}

bool HashTableBucket::isEmptySinceStart() const {
    return type == bucketType::ESS;
}

bool HashTableBucket::isEmptyAfterRemove() const {
    return type == bucketType::EAR;
}

void HashTableBucket::makeNormal() {
    type = bucketType::Normal;
}

void HashTableBucket::makeESS() {
    key.clear();
    value = 0;
    type = bucketType::ESS;
}

void HashTableBucket::makeEAR() {
    key.clear();
    value = 0;
    type = bucketType::EAR;
}

ostream &operator<<(ostream &os, const HashTableBucket &bucket) {
    switch (bucket.type) {
        case HashTableBucket::bucketType::Normal:
            os << "Normal";
            break;
        case HashTableBucket::bucketType::ESS:
            os << "ESS";
            break;
        case HashTableBucket::bucketType::EAR:
            os << "EAR";
            break;
    }
    return os;
}

size_t HashTable::hash(const string &key) const {
    size_t sum = 0;
    for (char ch : key) {
        sum += static_cast<size_t>(ch);
    }
    return sum % table.size();
}
void HashTable::generateOffsets() {
    offsets.clear();
    size_t size = table.size();
    for (size_t i = 0; i < size; i++) {
        offsets.push_back(i);
    }
    for (size_t i = 1; i < table.size(); i++) {
        size_t j = rand() % offsets.size();
        size_t temp = offsets[i];
        offsets[i] = offsets[j];
        offsets[j] = temp;
    }
}
size_t HashTable::probeIndex(size_t home, size_t i) const {
    return (home + offsets[i % offsets.size()]) % table.size();
}

HashTable::HashTable(size_t initCapacity) : table(initCapacity), currentSize(0) {}

void HashTable::resize() {
    vector<HashTableBucket> oldTable = table;
    table.clear();
    table.resize(oldTable.size() * 2);
    currentSize = 0;
    for(size_t i = 0; i < oldTable.size(); i++) {
        if (oldTable[i].type == HashTableBucket::bucketType::Normal) {
            insert(oldTable[i].key, oldTable[i].value);
        }
    }
}
bool HashTable::insert(const string &key, const size_t &value) {
    if (alpha() >= 0.5) {
        resize();
    }
    srand(static_cast<unsigned int>(key.length()));
    generateOffsets();
    size_t home = hash(key);

    for (size_t i = 0; i < table.size(); i++) {
        size_t index = probeIndex(home, i);
        if (table[index].type == HashTableBucket::bucketType::Normal && table[index].key == key) {
            return false; // Duplicate key
        }
    }
    for (size_t i = 0; i < table.size(); i++) {
        size_t index = probeIndex(home, i);
        if (table[index].type == HashTableBucket::bucketType::ESS ||
            table[index].type == HashTableBucket::bucketType::EAR) {
            table[index].load(key, value);
            currentSize++;
            return true; // Successful insertion
        }
    }
    return false; // Table is full should not happen due to resizing
}
bool HashTable::remove(const string &key) {
    srand(static_cast<unsigned int>(key.length()));
    generateOffsets();
    size_t home = hash(key);

    for (size_t i = 0; i < table.size(); i++) {
        size_t index = probeIndex(home, i);
        if (table[index].type == HashTableBucket::bucketType::ESS) {
            return false; // Key not found
        }
        if (table[index].type == HashTableBucket::bucketType::Normal && table[index].key == key) {
            table[index].makeEAR();
            currentSize--;
            return true; // Successful removal
        }
    }
    return false; // Key not found
}
bool HashTable::contains(const string &key) {
    srand(static_cast<unsigned int>(key.length()));
    generateOffsets();
    size_t home = hash(key);

    for (size_t i = 0; i < table.size(); i++) {
        size_t index = probeIndex(home, i);
        if (table[index].type == HashTableBucket::bucketType::ESS) {
            return false; // Key not found
        }
        if (table[index].type == HashTableBucket::bucketType::Normal && table[index].key == key) {
            return true; // Key found
        }
    }
    return false; // Key not found
}
optional<size_t> HashTable::get(const string &key) const {
    srand(static_cast<unsigned int>(key.length()));
    size_t home = hash(key);

    for (size_t i = 0; i < table.size(); i++) {
        size_t index = (home + offsets[i % offsets.size()]) % table.size();
        if (table[index].type == HashTableBucket::bucketType::ESS) {
            return nullopt; // Key not found
        }
        if (table[index].type == HashTableBucket::bucketType::Normal && table[index].key == key) {
            return table[index].value; // Key found
        }
    }
    return nullopt; // Key not found
}
size_t &HashTable::operator[](const string &key) {
    srand(static_cast<unsigned int>(key.length()));
    generateOffsets();
    size_t home = hash(key);

    for (size_t i = 0; i < table.size(); i++) {
        size_t index = probeIndex(home, i);
        if (table[index].type == HashTableBucket::bucketType::Normal && table[index].key == key) {
            return table[index].value; // Key found
        }
    }
    throw runtime_error("Key not found");
}
vector<string> HashTable::keys() const {
    vector<string> result;
    for (size_t i = 0; i < table.size(); i++) {
        if (table[i].type == HashTableBucket::bucketType::Normal) {
            result.push_back(table[i].key);
        }
    }
    return result;
}
double HashTable::alpha() const {
    return static_cast<double>(currentSize) / static_cast<double>(table.size());
}
size_t HashTable::capacity() const {
    return table.capacity();
}
size_t HashTable::size() const {
    return currentSize;
}