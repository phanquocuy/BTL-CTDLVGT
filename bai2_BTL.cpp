#include <iostream>
#include <climits>
#include <utility>
#include <queue>
using namespace std;

typedef pair<int, int> Edge;

class Vector {
private:
    int* data;
    int capacity;
    int size;
 // Hàm mở rộng dung lượng của vector khi đầy
    void resize() {
        int new_capacity = capacity == 0 ? 1 : capacity * 2;
        int* new_data = new int[new_capacity];

        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }

        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Vector() : size(0), capacity(0), data(nullptr) {}

    ~Vector() {
        delete[] data;
    }
// Thêm phần tử vào cuối vector
    void push_back(int value) {
        if (size == capacity) {
            resize();
        }
        data[size] = value;
        size++;
    }
// Lấy kích thước của vector
    int getSize() const {
        return size;
    }
// Lấy phần tử theo chỉ số (tương tự operator[])
    int& at(int index) {
        if (index >= 0 && index < size) {
            return data[index];
        } else {
            cout << "Index out of range!" << endl;
            static int invalid_value = INT_MIN;
            return invalid_value;
        }
    }
 // In tất cả các phần tử của vector
    void print() const {
        if (size == 0) {
            cout << "Vector is empty!" << endl;
            return;
        }
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

class Graph {
private:
    int V;
    Vector* adj;

public:
    Graph(int V) : V(V) {
        adj = new Vector[V];
    }

    ~Graph() {
        delete[] adj;
    }
// Thêm cạnh (u, v) với trọng số weight vào đồ thị
    void addEdge(int u, int v, int weight) {
        adj[u].push_back(v);
        adj[u].push_back(weight);

        adj[v].push_back(u);
        adj[v].push_back(weight);
    }

    void primMST() {
        Vector key;
        Vector parent;
        Vector inMST;
        priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

        for (int i = 0; i < V; i++) {
            key.push_back(INT_MAX);
            parent.push_back(-1);
            inMST.push_back(false);
        }

        key.at(0) = 0;
        pq.push({0, 0});

        int totalWeight = 0;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST.at(u) = true;
            totalWeight += key.at(u);

            for (int i = 0; i < adj[u].getSize(); i += 2) {
                int v = adj[u].at(i);
                int weight = adj[u].at(i + 1);

                if (!inMST.at(v) && weight < key.at(v)) {
                    key.at(v) = weight;
                    parent.at(v) = u;
                    pq.push({key.at(v), v});
                }
            }
        }

        cout << "Cây khung nhỏ nhất (MST):" << endl;
        for (int i = 1; i < V; i++) {
            cout << "Cạnh: " << parent.at(i) << " - " << i << " trọng số: " << key.at(i) << endl;
        }

        cout << "Tổng trọng số của cây khung nhỏ nhất: " << totalWeight << endl;
    }
};

int main() {
    Graph g(5);
// Thêm các cạnh với trọng số vào đồ thị
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    cout << "Thuật toán Prim's MST:" << endl;
    g.primMST();

    return 0;
}
