#include <iostream>
#include <string>
#include <locale>

// Структура, представляющая блюдо
struct Dish {
    std::string name; // Название блюда
    std::string type; // Тип блюда (например, завтрак, обед, ужин)
    double calories;  // Количество калорий в блюде
};

// Структура для предмета заказа (ПрО)
struct OrderItem {
    Dish dish;    // Блюдо
    int quantity; // Количество порций
};

// Реализация стека на основе массива
class ArrayStack {
private:
    static const int MAX_SIZE = 100; // Максимальный размер стека
    OrderItem stack[MAX_SIZE];        // Массив для хранения элементов стека
    int top;                          // Индекс вершины стека

public:
    ArrayStack() : top(-1) {}         // Конструктор: инициализация вершины стека

    // Проверка на пустоту
    bool isEmpty() {
        return top == -1;
    }

    // Проверка на переполнение
    bool isFull() {
        return top == MAX_SIZE - 1;
    }

    // Добавление элемента в стек
    void push(OrderItem item) {
        if (isFull()) {
            std::cerr << "Стек переполнен\n";
            return;
        }
        stack[++top] = item;
    }

    // Удаление элемента из стека
    OrderItem pop() {
        if (isEmpty()) {
            std::cerr << "Стек пуст\n";
            return OrderItem();
        }
        return stack[top--];
    }

    // Получение элемента с вершины стека (без удаления)
    OrderItem peek() {
        if (isEmpty()) {
            std::cerr << "Стек пуст\n";
            return OrderItem();
        }
        return stack[top];
    }
};

void cocktailSort(int arr[], int n) {
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        // Сдвигаем большие элементы вправо
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;

        swapped = false;
        --end;

        // Сдвигаем меньшие элементы влево
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}

void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[middle + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    delete[] L;
    delete[] R;
}


void mergeSort(int arr[], int left, int right) {
    if (left >= right) return;
    int middle = left + (right - left) / 2;
    mergeSort(arr, left, middle);
    mergeSort(arr, middle + 1, right);
    merge(arr, left, middle, right);
}

int main() {
    setlocale(LC_CTYPE, "Russian");
    ArrayStack stack;

    // Пример использования
    Dish breakfast = { "Омлет", "Завтрак", 350 };
    OrderItem order1 = { breakfast, 2 }; // Заказываем 2 порции омлета на завтрак
    stack.push(order1);

    Dish lunch = { "Салат Цезарь", "Обед", 250 };
    OrderItem order2 = { lunch, 1 }; // Заказываем 1 порцию салата на обед
    stack.push(order2);

    // Получаем и выводим информацию о заказе с вершины стека
    OrderItem currentOrder = stack.pop();
    std::cout << "Блюдо: " << currentOrder.dish.name << std::endl;
    std::cout << "Тип: " << currentOrder.dish.type << std::endl;
    std::cout << "Количество порций: " << currentOrder.quantity << std::endl;
    std::cout << "Калории на порцию: " << currentOrder.dish.calories << std::endl;

    int arr[] = { 12, 11, 13, 5, 6, 7 };
    int n = 6;

    mergeSort(arr, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    int arr2[] = { 5, 2, 9, 1, 5, 6 };
    int n2 = 6;

    cocktailSort(arr2, n2);

    for (int i = 0; i < n2; ++i) {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
