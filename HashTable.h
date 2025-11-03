/*
* Larry Smith
 * Project #4
 * CS 3100
 * Map ADT:HashTable
 * 11/3/2025
 */

#include <iostream>
#include <vector>
#include <optional>
#include <string>

using namespace std;

class HashTableBucket {
    // Represents a single bucket in the hash table
public:
    enum class bucketType { Normal, ESS, EAR }; // Bucket types: Normal, Empty Since Start, Empty After Remove

    string key; // the key of the bucket
    size_t value; // the value associated with the key
    bucketType type; // the type of the bucket

    HashTableBucket(); // Default constructor

    HashTableBucket(const string &key, const size_t &value); // Parameterized constructor

    void load(const string &key, const size_t &value); // Load key and value into the bucket

    bool isEmpty() const; // Check if the bucket is empty

    bool isEmptySinceStart() const; // Check if the bucket is empty since the start

    bool isEmptyAfterRemove() const; // Check if the bucket is empty after removal

    void makeNormal(); // Make the bucket normal

    void makeESS(); // Make the bucket empty since start

    void makeEAR(); // Make the bucket empty after remove

    friend ostream &operator<<(ostream &os, const HashTableBucket &bucket); // Output operator
};

class HashTable {
    // Hash table implementation
public:
    HashTable(size_t initCapacity = 8); // Constructor with initial capacity

    bool insert(const string &key, const size_t &value); // Insert key-value pair return false if key exists

    bool remove(const string &key); // remove key from the table return false if key not found

    bool contains(const string &key); // check if key exists in the table

    optional<size_t> get(const string &key) const; // get value associated with key return nullopt if not found

    size_t &operator[](const string &key); // access or insert value associated with key

    vector<string> keys() const; // return all keys in the table

    double alpha() const; // return load factor

    size_t capacity() const; // return current capacity of the table

    size_t size() const; // return current size of the table

    friend ostream &operator<<(ostream &os, const HashTable &table); // Output operator

private:
    vector<HashTableBucket> table; // the hash table
    vector<size_t> offsets; // offsets for probing
    size_t currentSize; // current number of elements in the table

    size_t hash(const string &key) const; // hash function for keys

    size_t probeIndex(size_t home, size_t i) const; // calculate probe index

    void generateOffsets(); // generate random offsets for probing

    void resize(); // resize the hash table when load factor exceeds threshold
};
