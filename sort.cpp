#include <iostream>
#include <vector>
#include <algorithm>

void bubbleSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // Оптимизация
    }
}

void selectionSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < arr.size(); ++j)
            if (arr[j] < arr[min_idx]) min_idx = j;
        std::swap(arr[i], arr[min_idx]);
    }
}

void insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void printVec(const std::vector<int>& v) {
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";
}

int main() {
    std::vector<int> a1 = {5, 2, 9, 1, 5, 6};
    std::vector<int> a2 = a1, a3 = a1;

    bubbleSort(a1);
    selectionSort(a2);
    insertionSort(a3);

    std::cout << "Bubble: "; printVec(a1);
    std::cout << "Select: "; printVec(a2);
    std::cout << "Insert: "; printVec(a3);
    return 0;
}