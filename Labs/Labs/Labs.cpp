#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>

using namespace std;

const int MAX_SIZE = 100;
const int MAX_VERTICES = 100;

struct BinaryHeap {
    int heap[MAX_SIZE];
    int size;

    BinaryHeap() : size(0) {}

    void insert(int value) {
        if (size == MAX_SIZE) {
            cout << "Heap is full!" << endl;
            return;
        }
        int index = size;
        heap[index] = value;
        size++;
        siftUp(index);
    }

    int extractMin() {
        if (size == 0) {
            cout << "Heap is empty!" << endl;
            return -1; // или бросить исключение
        }
        int min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        siftDown(0);
        return min;
    }

    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[parent] <= heap[index]) {
                break;
            }
            swap(heap[parent], heap[index]);
            index = parent;
        }
    }

    void siftDown(int index) {
        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < size && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < size && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else {
                break;
            }
        }
    }
};

// Функция для вывода матрицы
void printMatrix(int dist[][MAX_VERTICES], int V) {
    cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INT_MAX)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

void floydWarshall(int graph[][MAX_VERTICES], int V) {
    int dist[MAX_VERTICES][MAX_VERTICES];

    // Инициализация матрицы кратчайших расстояний
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            dist[i][j] = graph[i][j];
        }
    }

    // Шаг алгоритма Уоршелла
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printMatrix(dist, V);
}

const int INF = numeric_limits<int>::max(); // Значение "бесконечности"

// Структура для представления ребра графа
struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

// Функция для поиска кратчайших расстояний от начальной вершины до всех остальных
void dijkstra(vector<vector<Edge>>& graph, int start, vector<int>& distances) {
    int n = graph.size();
    distances.assign(n, INF); // Изначально все расстояния бесконечными
    distances[start] = 0; // Расстояние до самой себя равно 0

    // Создаем очередь с приоритетом, чтобы всегда извлекать вершину с минимальным расстоянием
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int cur_dist = pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        // Если мы нашли более короткое расстояние до этой вершины, игнорируем ее
        if (cur_dist > distances[cur_node])
            continue;

        // Обходим всех соседей текущей вершины
        for (const Edge& edge : graph[cur_node]) {
            int new_dist = distances[cur_node] + edge.weight;
            // Если нашли более короткий путь до соседа, обновляем расстояние
            if (new_dist < distances[edge.to]) {
                distances[edge.to] = new_dist;
                pq.push({ new_dist, edge.to });
            }
        }
    }
}

int main() {
    BinaryHeap heap;

    heap.insert(5);
    heap.insert(10);
    heap.insert(3);
    heap.insert(7);
    heap.insert(1);

    cout << "Extracted min: " << heap.extractMin() << endl;
    cout << "Extracted min: " << heap.extractMin() << endl;

    int graph[MAX_VERTICES][MAX_VERTICES];
    int V; // количество вершин

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the adjacency matrix (INF for infinity):\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cin >> graph[i][j];
            if (graph[i][j] == -1)
                graph[i][j] = INT_MAX;
        }
    }

    floydWarshall(graph, V);

    int n, m; // n - количество вершин, m - количество ребер
    cin >> n >> m;

    vector<vector<Edge>> graph2(n); // Инициализация списка смежности

    // Считываем ребра графа и их веса
    for (int i = 0; i < m; ++i) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph2[from].push_back(Edge(to, weight));
    }

    int start_vertex;
    cin >> start_vertex; // Вершина, от которой начинаем поиск кратчайших путей

    vector<int> distances; // Массив для хранения кратчайших расстояний
    dijkstra(graph2, start_vertex, distances);

    // Выводим кратчайшие расстояния до всех вершин
    for (int i = 0; i < n; ++i) {
        if (distances[i] == INF)
            cout << "INF ";
        else
            cout << distances[i] << " ";
    }
    cout << endl;

    return 0;
    return 0;
}
