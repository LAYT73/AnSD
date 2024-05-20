#include <iostream>
#include <list>
#include <vector>

class ChainingHashTable {
public:
    ChainingHashTable(int size) : table(size) {}

    void insert(int key) {
        int hash = key % table.size();
        table[hash].push_back(key);
    }

    void printTable() const {
        for (int i = 0; i < table.size(); ++i) {
            std::cout << i << ": ";
            for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    std::vector<std::list<int>> table;
};

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

    void printTable() const {
        for (int i = 0; i < table.size(); ++i) {
            std::cout << i << ": " << table[i] << std::endl;
        }
    }

private:
    std::vector<int> table;
    int currentSize;
};

class BloomFilter {
public:
    BloomFilter(int size) : bits(size), numHashes(2) {}

    void insert(int key) {
        for (int i = 0; i < numHashes; ++i) {
            bits[hash(key, i) % bits.size()] = true;
        }
    }

    bool contains(int key) const {
        for (int i = 0; i < numHashes; ++i) {
            if (!bits[hash(key, i) % bits.size()]) {
                return false;
            }
        }
        return true;
    }

private:
    std::vector<bool> bits;
    int numHashes;

    int hash(int key, int seed) const {
        std::hash<int> hasher;
        return hasher(key + seed);
    }
};

int main() {
    LinearProbingHashTable hashTable(10);

    hashTable.insert(5);
    hashTable.insert(15);
    hashTable.insert(25);
    hashTable.insert(35);

    hashTable.printTable();

    ChainingHashTable hashTable2(10);

    hashTable2.insert(5);
    hashTable2.insert(15);
    hashTable2.insert(25);
    hashTable2.insert(35);

    hashTable2.printTable();

    BloomFilter filter(100);

    filter.insert(5);
    filter.insert(15);

    std::cout << "Contains 5: " << filter.contains(5) << std::endl;
    std::cout << "Contains 15: " << filter.contains(15) << std::endl;
    std::cout << "Contains 25: " << filter.contains(25) << std::endl;

    return 0;
}