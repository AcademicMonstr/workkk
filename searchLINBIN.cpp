#include <iostream>
#include <vector>

int linearSearch(const std::vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i)
        if (arr[i] == target) return i;
    return -1;
}

int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2; // Защита от переполнения
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    std::vector<int> data = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91}; // УЖЕ отсортирован!
    int target = 23;

    std::cout << "Linear search index: " << linearSearch(data, target) << "\n";
    std::cout << "Binary search index: " << binarySearch(data, target) << "\n";
    std::cout << "Binary search (not found): " << binarySearch(data, 100) << "\n";
    return 0;
}