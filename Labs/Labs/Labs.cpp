#include <stdexcept>
#include <iostream>

// Интерфейс для стека
template<typename T>
class IStack {
public:
    virtual ~IStack() = default;
    virtual void push(const T& item) = 0;
    virtual T pop() = 0;
    virtual T peek() const = 0;
    virtual bool isEmpty() const = 0;
};

// Реализация стека на двусвязном списке
template<typename T>
class LinkedListStack : public IStack<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* top;

public:
    LinkedListStack() : top(nullptr) {}

    ~LinkedListStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& item) override {
        Node* newNode = new Node(item);
        if (isEmpty()) {
            top = newNode;
        }
        else {
            newNode->next = top;
            top->prev = newNode;
            top = newNode;
        }
    }

    T pop() override {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        T data = top->data;
        Node* temp = top;
        top = top->next;
        if (top != nullptr) {
            top->prev = nullptr;
        }
        delete temp;
        return data;
    }

    T peek() const override {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return top->data;
    }

    bool isEmpty() const override {
        return top == nullptr;
    }
};

// Пример использования стека
int main() {
    IStack<int>* stack = new LinkedListStack<int>();
    stack->push(1);
    stack->push(2);
    stack->push(3);
    std::cout << stack->pop() << std::endl; // Выведет: 3
    std::cout << stack->peek() << std::endl; // Выведет: 2
    delete stack;
    return 0;
}