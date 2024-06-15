#include <iostream>
#include <vector>
#include <algorithm>
#include <locale>
#include <chrono>

void coinChangeGreedy(std::vector<int>& coins, int amount) {
    std::sort(coins.begin(), coins.end(), std::greater<int>());

    int n = coins.size();
    int i = 0;
    while (amount > 0 && i < n) {
        if (coins[i] <= amount) {
            std::cout << coins[i] << " ";
            amount -= coins[i];
        }
        else {
            i++;
        }
    }
    std::cout << std::endl;
}

int knapsackDP(int W, std::vector<int>& wt, std::vector<int>& val) {
    int n = wt.size();
    std::vector<std::vector<int>> K(n + 1, std::vector<int>(W + 1));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0) {
                K[i][w] = 0;
            }
            else if (wt[i - 1] <= w) {
                K[i][w] = std::max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
            }
            else {
                K[i][w] = K[i - 1][w];
            }
        }
    }
    return K[n][W];
}

int binarySearch(int arr[], int left, int right, int x) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        // Если элемент найден посередине
        if (arr[mid] == x)
            return mid;

        // Если элемент меньше, чем середина, ищем в левой половине
        if (arr[mid] > x)
            return binarySearch(arr, left, mid - 1, x);

        // В противном случае ищем в правой половине
        return binarySearch(arr, mid + 1, right, x);
    }

    // Если элемент не найден вообще
    return -1;
}

void quadraticAlgorithm(const std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << arr[i] << " " << arr[j] << std::endl;
        }
    }
}

void linearAlgorithm(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
}

int main() {
    setlocale(LC_CTYPE, "Russian");

    std::vector<int> coins = { 1, 5, 10, 25, 50 };
    int amount = 17;
    coinChangeGreedy(coins, amount);

    std::vector<int> val = { 60, 100, 120 };
    std::vector<int> wt = { 10, 20, 30 };
    int W = 50;
    std::cout << "Maximum value: " << knapsackDP(W, wt, val) << std::endl;

    std::vector<int> arr = { 1, 2, 3, 4, 5 };
    linearAlgorithm(arr);
    quadraticAlgorithm(arr);
    // Временные замеры бинарного поиска
    for (int size = 1000; size <= 10000; size += 1000) {
        std::vector<int> testArray(size);
        for (int i = 0; i < size; ++i) {
            testArray[i] = i + 1;
        }

        int x = size - 2;  // Элемент, который мы будем искать
        auto start = std::chrono::high_resolution_clock::now();
        int result = binarySearch(testArray.data(), 0, size - 1, x);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Размер массива: " << size << ", Время выполнения: " << duration.count() << " мс" << std::endl;
    }
    // Временные замеры бинарного поиска
    for (int size = 10000; size <= 100000; size += 10000) {
        std::vector<int> testArray(size);
        for (int i = 0; i < size; ++i) {
            testArray[i] = i + 1;
        }

        int x = size - 2;  // Элемент, который мы будем искать
        auto start = std::chrono::high_resolution_clock::now();
        int result = binarySearch(testArray.data(), 0, size - 1, x);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Размер массива: " << size << ", Время выполнения: " << duration.count() << " мс" << std::endl;
    }
    // Временные замеры бинарного поиска
    for (int size = 100000; size <= 1000000; size += 100000) {
        std::vector<int> testArray(size);
        for (int i = 0; i < size; ++i) {
            testArray[i] = i + 1;
        }

        int x = size-2;  // Элемент, который мы будем искать
        auto start = std::chrono::high_resolution_clock::now();
        int result = binarySearch(testArray.data(), 0, size - 1, x);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Размер массива: " << size << ", Время выполнения: " << duration.count() << " мс" << std::endl;
    }

    return 0;
}
