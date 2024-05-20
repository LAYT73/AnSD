#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>

class LinearProbingHashTable {
public:
    LinearProbingHashTable(int size) : table(size, -1), currentSize(0) {}

    bool insert(int key) {
        if (currentSize >= table.size()) return false; // Таблица полная

        int hash = key % table.size();

        while (table[hash] != -1) {
            hash = (hash + 1) % table.size();
        }

        table[hash] = key;
        currentSize++;
        return true;
    }

    bool search(int key) {
        int hash = key % table.size();
        int initialHash = hash;

        while (table[hash] != key) {
            hash = (hash + 1) % table.size();
            if (hash == initialHash || table[hash] == -1) {
                return false; // Элемент не найден
            }
        }

        return true;
    }

private:
    std::vector<int> table;
    int currentSize;
};

int main() {
    const int tableSize = 1000;
    const int numTests = 10;
    LinearProbingHashTable hashTable(tableSize);

    std::vector<int> keys;
    for (int i = 0; i < tableSize / 2; ++i) {
        keys.push_back(i);
    }

    std::ofstream outFile("hash_table_timing.csv");
    outFile << "Test,InsertionTime,SearchTime\n";

    for (int test = 0; test < numTests; ++test) {
        auto startInsertion = std::chrono::high_resolution_clock::now();
        for (int key : keys) {
            hashTable.insert(key);
        }
        auto endInsertion = std::chrono::high_resolution_clock::now();

        auto insertionDuration = std::chrono::duration_cast<std::chrono::microseconds>(endInsertion - startInsertion).count();

        auto startSearch = std::chrono::high_resolution_clock::now();
        for (int key : keys) {
            hashTable.search(key);
        }
        auto endSearch = std::chrono::high_resolution_clock::now();

        auto searchDuration = std::chrono::duration_cast<std::chrono::microseconds>(endSearch - startSearch).count();

        outFile << test + 1 << "," << insertionDuration << "," << searchDuration << "\n";
    }

    outFile.close();
    std::cout << "Timing data saved to hash_table_timing.csv" << std::endl;

    return 0;
}
