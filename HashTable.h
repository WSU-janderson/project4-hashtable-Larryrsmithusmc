/*
* Larry Smith
 * Project#4
 * CS 3100
 * Map ADT:HashTable
 * 11/3/2025
 */

#include <string>
#include <vector>
#include <optional>
#include <iostream>

using namespace std;

class HashTableBucket {
public:
    enum class bucketType {Normal, ESS, EAR};
    string key;
    size_t value;
    bucketType type;

    HashTableBucket();
    HashTableBucket(const string& key, const size_t& value);

    void load(const string& key, const size_t& value);
    bool isEmpty() const;
    bool isEmptySinceStart() const;
    bool isEmptyAfterRemove() const;
    void makeNormal();
    void makeESS();
    void makeEAR();

    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket);
};

class HashTable {
 public:
    HashTable(size_t initCapacity = 8);
    bool insert(const string& key, const size_t& value);
    bool remove(const string& key);
    bool contains(const string& key);
    optional<size_t> get(const string& key) const;
    size_t& operator[](const string& key);
    vector<string> keys() const;
    double alpha() const;
    size_t capacity() const;
    size_t size() const;




};
