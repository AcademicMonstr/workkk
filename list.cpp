#include <iostream>
#include <stdexcept>

class ListItem {
public:
    int Info;        // Данные узла
    ListItem* Next;  // Указатель на следующий узел

    ListItem(int value) : Info(value), Next(nullptr) {}
};

class List {
private:
    ListItem* First; // Указатель на первый узел
    std::size_t size; // Текущий размер списка

public:
    List() : First(nullptr), size(0) {}

    ~List() {
        clear();
    }

    // Вставка элемента в начало списка
    void InsertFirst(int Alnfo) {
        ListItem* P = new ListItem(Alnfo);
        P->Next = First; // Новый узел указывает на текущий первый узел
        First = P;       // Обновляем указатель на первый узел
        ++size;          // Увеличиваем размер списка
    }

    void Insert( const int& elem ){
        if ( First == nullptr || elem < First -> Info ) {
            this -> InsertFirst(elem);
        }
        else{

            ListItem* Flag = First;
            ListItem* inserted = new ListItem(elem);
            
            while ( Flag -> Next != nullptr && Flag -> Next -> Info < elem )
            {
                Flag = Flag -> Next;
            }

            inserted -> Next = Flag -> Next;
            Flag -> Next = inserted;
            ++size;
        }

    }

    // Удаление первого элемента списка
    void RemoveFirst() {
        if (empty()) {
            throw std::out_of_range("RemoveFirst on empty list");
        }
        ListItem* temp = First;
        First = First->Next; // Обновляем указатель на первый узел
        delete temp;         // Удаляем старый первый узел
        --size;              // Уменьшаем размер списка
    }

    // Получение первого элемента
    int Front() const {
        if (empty()) {
            throw std::out_of_range("Front on empty list");
        }
        return First->Info;
    }

    // Проверка на пустоту
    bool empty() const noexcept {
        return size == 0;
    }

    // Получение размера списка
    std::size_t getSize() const noexcept {
        return size;
    }

    // Очистка списка
    void clear() {
        while (!empty()) {
            RemoveFirst();
        }
    }

    void Print() const {
        ListItem* cur = First;
            while ( cur != nullptr ){
                std::cout << cur -> Info << std::endl;
                cur = cur -> Next;
            }
    }
};

// Пример использования
int main() {
    List myList;

    myList.InsertFirst(30);
    myList.Insert(11);
    myList.InsertFirst(20);
    myList.InsertFirst(10);
    
    

    std::cout << "Первый элемент: " << myList.Front() << std::endl; // 30
    std::cout << "Размер списка: " << myList.getSize() << std::endl; // 3

    myList.Print();

    myList.RemoveFirst();
    std::cout << "Первый элемент после удаления: " << myList.Front() << std::endl; // 20
    std::cout << "Размер списка после удаления: " << myList.getSize() << std::endl; // 2

    myList.clear();
    std::cout << "Размер после очистки: " << myList.getSize() << std::endl; // 0

    return 0;
}


// OK проверка пустой ли список, если пустой - вставляем первым узлом
//если не первый, то создаем новый узел P сравниваем с каждым эллементом
//еcли появился элемент больше, то 