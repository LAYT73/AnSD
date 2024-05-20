#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <unordered_map>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int NUM_ELEMENTS = 200000;

template <typename T>
class CustomVector {
private:
    T* data;
    size_t capacity;
    size_t size;

    void resize(size_t new_capacity) {
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    CustomVector() : data(nullptr), capacity(0), size(0) {}

    ~CustomVector() {
        delete[] data;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    size_t getSize() const {
        return size;
    }
};

template <typename T>
class CustomList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    CustomList() : head(nullptr), tail(nullptr), size(0) {}

    ~CustomList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(const T& value) {
        Node* new_node = new Node(value);
        if (!tail) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        size++;
    }

    size_t getSize() const {
        return size;
    }
};

template <typename T>
class CustomStack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* top;
    size_t size;

public:
    CustomStack() : top(nullptr), size(0) {}

    ~CustomStack() {
        while (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(const T& value) {
        Node* new_node = new Node(value);
        new_node->next = top;
        top = new_node;
        size++;
    }

    void pop() {
        if (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
            size--;
        }
    }

    T& peek() {
        return top->data;
    }

    size_t getSize() const {
        return size;
    }
};

template <typename T>
class CustomQueue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    CustomQueue() : head(nullptr), tail(nullptr), size(0) {}

    ~CustomQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const T& value) {
        Node* new_node = new Node(value);
        if (!tail) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }

    void pop() {
        if (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
        }
    }

    T& front() {
        return head->data;
    }

    size_t getSize() const {
        return size;
    }
};

template <typename K, typename V>
class CustomUnorderedMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };

    std::vector<Node*> table;
    size_t capacity;
    size_t size;

    size_t hash(const K& key) const {
        return std::hash<K>()(key) % capacity;
    }

    void rehash() {
        size_t new_capacity = capacity * 2;
        std::vector<Node*> new_table(new_capacity, nullptr);
        for (size_t i = 0; i < capacity; ++i) {
            Node* node = table[i];
            while (node) {
                size_t new_index = std::hash<K>()(node->key) % new_capacity;
                Node* next = node->next;
                node->next = new_table[new_index];
                new_table[new_index] = node;
                node = next;
            }
        }
        table = std::move(new_table);
        capacity = new_capacity;
    }

public:
    CustomUnorderedMap() : capacity(16), size(0) {
        table.resize(capacity, nullptr);
    }

    ~CustomUnorderedMap() {
        for (size_t i = 0; i < capacity; ++i) {
            Node* node = table[i];
            while (node) {
                Node* temp = node;
                node = node->next;
                delete temp;
            }
        }
    }

    void insert(const K& key, const V& value) {
        if (size >= capacity * 0.75) {
            rehash();
        }
        size_t index = hash(key);
        Node* node = new Node(key, value);
        node->next = table[index];
        table[index] = node;
        size++;
    }

    V* find(const K& key) {
        size_t index = hash(key);
        Node* node = table[index];
        while (node) {
            if (node->key == key) {
                return &node->value;
            }
            node = node->next;
        }
        return nullptr;
    }

    size_t getSize() const {
        return size;
    }
};


// Шаблонная функция для измерения времени выполнения
template <typename Func>
void benchmark(Func func, const string& name) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    cout << name << ": " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

// Тестирование кастомных и встроенных структур данных

void test_custom_vector() {
    CustomVector<int> v;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        v.push_back(i);
    }
}

void test_std_vector() {
    vector<int> v;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        v.push_back(i);
    }
}

void test_custom_list() {
    CustomList<int> l;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        l.push_back(i);
    }
}

void test_std_list() {
    list<int> l;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        l.push_back(i);
    }
}

void test_custom_stack() {
    CustomStack<int> s;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        s.push(i);
    }
}

void test_std_stack() {
    stack<int> s;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        s.push(i);
    }
}

void test_custom_queue() {
    CustomQueue<int> q;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        q.push(i);
    }
}

void test_std_queue() {
    queue<int> q;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        q.push(i);
    }
}

void test_custom_unordered_map() {
    CustomUnorderedMap<int, int> m;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        m.insert(i, i);
    }
}

void test_std_unordered_map() {
    unordered_map<int, int> m;
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        m[i] = i;
    }
}

int main() {
    cout << "Testing Custom Structures vs Standard Library Structures\n";

    // Вектор
    benchmark(test_custom_vector, "Custom Vector push_back");
    benchmark(test_std_vector, "std::vector push_back");

    // Связанный список
    benchmark(test_custom_list, "Custom List push_back");
    benchmark(test_std_list, "std::list push_back");

    // Стек
    benchmark(test_custom_stack, "Custom Stack push");
    benchmark(test_std_stack, "std::stack push");

    // Очередь
    benchmark(test_custom_queue, "Custom Queue push");
    benchmark(test_std_queue, "std::queue push");

    // Хеш-таблица
    benchmark(test_custom_unordered_map, "Custom UnorderedMap insert");
    benchmark(test_std_unordered_map, "std::unordered_map insert");

    return 0;
}
