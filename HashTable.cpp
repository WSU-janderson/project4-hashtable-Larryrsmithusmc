/*
 * Larry Smith
 * Project#4
 * CS 3100
 * Map ADT:HashTable
 * 11/3/2025
 */

#include <iostream>
#include <vector>
#include <optional>
#include <string>
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
