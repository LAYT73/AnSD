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

// Определение размера массива для ArrayStack
const int ARRAY_SIZE = 50; // Примерный размер, может быть любым положительным числом

template<typename T>
class ArrayStack : public IStack<T> {
private:
    T data[ARRAY_SIZE]; // Теперь размер массива определен
    int top = -1; // Индекс вершины стека

public:
    ArrayStack() = default;

    ~ArrayStack() override = default;

    void push(const T& item) override {
        if (isFull()) {
            throw std::out_of_range("Stack is full");
        }
        data[++top] = item;
    }

    T pop() override {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data[top--];
    }

    T peek() const override {
        if (isEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data[top];
    }

    bool isEmpty() const override {
        return top == -1;
    }

    bool isFull() {
        return top == ARRAY_SIZE - 1;
    }
};

int main() {
    try {
        LinkedListStack<int> stack; // Создаем стек с максимальной вместимостью 10 элементов

        // Добавляем несколько элементов в стек
        stack.push(1);
        stack.push(2);
        stack.push(3);

        // Проверяем, что стек не пуст
        if (!stack.isEmpty()) {
            std::cout << "Top element: " << stack.peek() << std::endl;
            std::cout << "Popped element: " << stack.pop() << std::endl;
        }

        // Добавляем еще один элемент
        stack.push(4);
        std::cout << "Added element: 4" << std::endl;

    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

