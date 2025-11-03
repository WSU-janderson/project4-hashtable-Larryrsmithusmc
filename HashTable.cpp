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
// HashTableBucket Implementation
HashTableBucket::HashTableBucket() : key(""), value(0), type(bucketType::ESS) {
}

// Parameterized constructor
HashTableBucket::HashTableBucket(const string &key, const size_t &value) : key(key), value(value),
                                                                           type(bucketType::Normal) {
}

// Load key and value into the bucket
void HashTableBucket::load(const string &key, const size_t &value) {
    this->key = key;
    this->value = value;
    makeNormal();
}

// Check if the bucket is empty
bool HashTableBucket::isEmpty() const {
    return type == bucketType::ESS || type == bucketType::EAR;
}

// Check if the bucket is empty since the start
bool HashTableBucket::isEmptySinceStart() const {
    return type == bucketType::ESS;
}

// Check if the bucket is empty after removal
bool HashTableBucket::isEmptyAfterRemove() const {
    return type == bucketType::EAR;
}

// Make the bucket normal
void HashTableBucket::makeNormal() {
    type = bucketType::Normal;
}

// Make the bucket empty since start
void HashTableBucket::makeESS() {
    key.clear();
    value = 0;
    type = bucketType::ESS;
}

// Make the bucket empty after remove
void HashTableBucket::makeEAR() {
    key.clear();
    value = 0;
    type = bucketType::EAR;
}

// Output operator for HashTableBucket
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

// HashTable Implementation
HashTable::HashTable(size_t initCapacity) : table(initCapacity), currentSize(0) {
}

// Simple hash function for sum of ASCII values mod table size. Pretty much turning string name into a number value
// Like Bob into 66+111+98=275 then mod table size used in my probing
size_t HashTable::hash(const string &key) const {
    size_t sum = 0;
    for (char ch: key) {
        sum += static_cast<size_t>(ch);
    }
    return sum % table.size();
}

// Generate random offsets for probing based on the key length as seed
void HashTable::generateOffsets() {
    offsets.clear();
    size_t size = table.size();
    for (size_t i = 0; i < size; i++) {
        offsets.push_back(i);
    }
    for (size_t i = 0; i < table.size(); i++) {
        size_t j = rand() % offsets.size();
        size_t temp = offsets[i];
        offsets[i] = offsets[j];
        offsets[j] = temp;
    }
}

// Calculate probe index using home index and offset
size_t HashTable::probeIndex(size_t home, size_t i) const {
    return (home + offsets[i % offsets.size()]) % table.size();
}

// Resize the hash table when load factor exceeds 0.5
void HashTable::resize() {
    vector<HashTableBucket> oldTable = table;
    table.clear();
    table.resize(oldTable.size() * 2);
    currentSize = 0;
    for (size_t i = 0; i < oldTable.size(); i++) {
        if (oldTable[i].type == HashTableBucket::bucketType::Normal) {
            insert(oldTable[i].key, oldTable[i].value);
        }
    }
}

// Insert key-value pair return false if key exists
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

// remove key from the table return false if key not found
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

// remove key from the table return false if key not found
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

// get value associated with key return nullopt if not found
optional<size_t> HashTable::get(const string &key) const {
    for (const auto &bucket: table) {
        if (bucket.type == HashTableBucket::bucketType::Normal && bucket.key == key) {
            return bucket.value;
        }
    }
    return nullopt;
}

// access or insert value associated with key
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

// return all keys in the table
vector<string> HashTable::keys() const {
    vector<string> result;
    for (size_t i = 0; i < table.size(); i++) {
        if (table[i].type == HashTableBucket::bucketType::Normal) {
            result.push_back(table[i].key);
        }
    }
    return result;
}

// return load factor
double HashTable::alpha() const {
    return static_cast<double>(currentSize) / static_cast<double>(table.size());
}

// return current capacity of the table
size_t HashTable::capacity() const {
    return table.size();
}

// return current size of the table
size_t HashTable::size() const {
    return currentSize;
}

// Output operator
ostream &operator<<(ostream &os, const HashTable &table) {
    for (size_t i = 0; i < table.table.size(); i++) {
        if (table.table[i].type == HashTableBucket::bucketType::Normal) {
            os << "Bucket: " << i
                    << ", Key: " << table.table[i].key
                    << ", Value: " << table.table[i].value << endl;
        }
    }
    return os;
}
