#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <unordered_map>
#include <chrono>

using namespace std;
using namespace std::chrono;

const int NUM_ELEMENTS = 100000;

void test_vector() {
    vector<int> v;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        v.push_back(i);
    }
    auto end = high_resolution_clock::now();
    cout << "Vector push_back: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

void test_list() {
    list<int> l;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        l.push_back(i);
    }
    auto end = high_resolution_clock::now();
    cout << "List push_back: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

void test_stack() {
    stack<int> s;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        s.push(i);
    }
    auto end = high_resolution_clock::now();
    cout << "Stack push: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

void test_queue() {
    queue<int> q;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        q.push(i);
    }
    auto end = high_resolution_clock::now();
    cout << "Queue push: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

void test_unordered_map() {
    unordered_map<int, int> m;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        m[i] = i;
    }
    auto end = high_resolution_clock::now();
    cout << "Unordered_map insert: " << duration_cast<milliseconds>(end - start).count() << " ms\n";
}

int main() {
    test_vector();
    test_list();
    test_stack();
    test_queue();
    test_unordered_map();
    return 0;
}
