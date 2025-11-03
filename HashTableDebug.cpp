/*
* Larry Smith
 * Project#4
 * CS 3100
 * Map ADT : HashTable
 * 11/3/2025
 */

#include <iostream>
#include "HashTable.h"

using namespace std;

int main() {
    HashTable table;

    table.insert("Alice", 1001);
    table.insert("Bob", 1002);
    table.insert("Charlie", 1003);
    table.insert("David", 1004);

    cout << table << endl;


    // Test get
    if (auto val = table.get("Bob"); val.has_value()) {
        cout << "Value for Bob: " << val.value() << endl;
    }

    // Test contains
    cout << "Contains Charlie? " << (table.contains("Charlie") ? "Yes" : "No") << endl;
    cout << "Contains Eve? " << (table.contains("Eve") ? "Yes" : "No") << endl;

    // Test operator[]
    table["Alice"] = 5000;
    cout << "Updated Alice's value using operator[]:" << endl;
    cout << table << endl;

    // Test remove
    table.remove("Bob");
    cout << "After removing Bob:" << endl;
    cout << table << endl;

    // List all keys
    cout << "Current keys in table:" << endl;
    for (const auto &k: table.keys()) {
        cout << k << " ";
    }
    cout << endl;

    // Check load, capacity, and size
    cout << "Load factor: " << table.alpha() << endl;
    cout << "Capacity: " << table.capacity() << endl;
    cout << "Size: " << table.size() << endl;

    table.insert("Eve", 1005);
    cout << "After inserting Eve:" << endl;
    cout << table << endl;

    cout << "Load factor: " << table.alpha() << endl;
    cout << "Capacity: " << table.capacity() << endl;
    cout << "Size: " << table.size() << endl;

    //testing resize
    table.insert("Frank", 1006);
    cout << "After inserting Frank:" << endl;
    cout << table << endl;

    cout << "Load factor: " << table.alpha() << endl;
    cout << "Capacity: " << table.capacity() << endl;
    cout << "Size: " << table.size() << endl;

    return 0;
}
