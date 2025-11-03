[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/7RAFczHS)
# Project 4 - HashTable

Project description can be found [in the repo](Project4_HashTable.pdf)

Place your complexity analysis below.

Time Complexity

- Hashing a key: O(k), where k is the length of the key string.
- Insert: Average O(1), Worst O(n) when table is nearly full or during a resize.
- Remove: Average O(1), Worst O(n) when resolving collisions.
- Search / Contains: Average O(1), Worst O(n) for collisions.
- Resize: O(n) when table grows, but occurs rarely.
- Pseudo-random probing ensures keys are distributed unpredictably across the table, which helps reduce clustering but can still produce a longer probe sequence in rare worst-case scenarios.
- Overall, the hash table performs efficiently for typical use, keeping average operations fast while resizing ensures load factor stays below 0.5.

---
