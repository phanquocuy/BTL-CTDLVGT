#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class hangdoi {
private:
    vector<int> heap; 

    // Tính chỉ số cha của phần tử
    int parent(int i) { return (i - 1) / 2; }

    // Tính chỉ số con trái
    int leftChild(int i) { return 2 * i + 1; }

    // Tính chỉ số con phải
    int rightChild(int i) { return 2 * i + 2; }

    // Duy trì tính chất Min-Heap khi heapify xuống (xử lý khi xóa phần tử)
    void heapify(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i;
        if (left < heap.size() && heap[left] < heap[smallest])
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

    // Duy trì tính chất Min-Heap khi thêm phần tử mới (heapify-up)
    void heapifyUp(int i) {
        while (i > 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

public:
    // Thêm phần tử vào hàng đợi ưu tiên
    void push(int val) {
        heap.push_back(val);  
        heapifyUp(heap.size() - 1);  
    }

    // Lấy phần tử có giá trị nhỏ nhất (phần tử gốc)
    int top() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0]; 
    }

    // Xóa phần tử có giá trị nhỏ nhất (phần tử gốc)
    void pop() {
        if (heap.empty()) throw runtime_error("Heap is empty");

        heap[0] = heap.back();
        heap.pop_back(); 
        heapify(0);  
    }

    // Lấy số lượng phần tử trong heap
    int size() {
        return heap.size();
    }

    // Kiểm tra xem heap có rỗng không
    bool empty() {
        return heap.empty();
    }
};


int main() {
    hangdoi pq;

    // Thêm các phần tử vào hàng đợi ưu tiên
    
    pq.push(10);
    pq.push(20);
    pq.push(5);
    pq.push(30);
    pq.push(15);
    pq.push(25);
    pq.push(76);
    pq.push(43);
    cout << "Ptu có giá trij nhỏ nhất là : " << pq.top() << endl;

    // Lấy phần tử nhỏ nhất và xóa nó khỏi heap
    pq.pop();
    cout << "Sau khi xóa, ptu nhỏ nhất còn lại la: " << pq.top() << endl;

    cout << "Số ptu trong heap là: " << pq.size() << endl;
    
    // Thêm và xóa thêm vài phần tử
    pq.push(3);
    pq.push(50);
    pq.pop();
    cout << "Sau khi xóa thêm một ptu, ptu nhỏ nhất là : " << pq.top() << endl;
    cout << "Số ptu còn lại trong heap là : " << pq.size() << endl;

    return 0;
}
