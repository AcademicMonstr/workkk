#include <iostream>
#include <algorithm> // для std::copy

class MyVector {
private:
    int* data;
    int _size;
    int _capacity;

    void resize() {
        _capacity *= 2;
        int* newData = new int[_capacity];
        std::copy(data, data + _size, newData); // Копируем элементы
        delete[] data;
        data = newData;
    }

public:
    // 1. Конструктор по умолчанию
    MyVector() : data(new int[2]), _size(0), _capacity(2) {}

    // 2. Деструктор (Правило 1/5)
    ~MyVector() {
        delete[] data;
    }

    // 3. Конструктор копирования (Правило 2/5) - ГЛУБОКОЕ копирование
    MyVector(const MyVector& other) 
        : _size(other._size), _capacity(other._capacity) {
        data = new int[_capacity];
        std::copy(other.data, other.data + _size, data);
    }

    // 4. Оператор присваивания копированием (Правило 3/5)
    MyVector& operator=(const MyVector& other) {
        if (this != &other) { // Защита от самоприсваивания (a = a)
            delete[] data; // Очищаем старую память
            _size = other._size;
            _capacity = other._capacity;
            data = new int[_capacity];
            std::copy(other.data, other.data + _size, data);
        }
        return *this;
    }

    // 5. Конструктор перемещения (Правило 4/5) - C++11
    MyVector(MyVector&& other) noexcept 
        : data(other.data), _size(other._size), _capacity(other._capacity) {
        // "Обнуляем" источник, чтобы его деструктор не удалил нашу память
        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    // 6. Оператор присваивания перемещением (Правило 5/5) - C++11
    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] data; // Очищаем своё
            data = other.data;
            _size = other._size;
            _capacity = other._capacity;
            
            other.data = nullptr; // Обнуляем источник
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    void push_back(int val) {
        if (_size == _capacity) resize();
        data[_size++] = val;
    }

    void pop_back() {
        if (_size > 0) _size--;
    }

    int& operator[](int index) {
        return data[index];
    }

    int size() const { return _size; }
    int capacity() const { return _capacity; }

};

int main() {
    MyVector v1;
    std::cout << "Initial cap: " << v1.capacity() << "\n"; // 2
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);

    std::cout << "After 3 pushes, cap: " << v1.capacity() << "\n"; // 4
    std::cout << "Element at 1: " << v1[1] << "\n"; // 20
    v1[1] = 99;
    std::cout << "Modified element at 1: " << v1[1] << "\n"; // 99

    // Проверка конструктора копирования (Глубокая копия)
    MyVector v2 = v1; 
    v2.push_back(99); // Это не повлияет на v1!

    // Проверка перемещения
    MyVector v3 = std::move(v2); // v2 теперь "пустой", его память перешла к v3

    std::cout << "v1 size: " << v1.size() << "\n"; // 2
    std::cout << "v3 size: " << v3.size() << "\n"; // 3
    return 0;
}