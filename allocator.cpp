#include <iostream>
#include <memory>
#include <cstddef>
#include <new>
#include <cassert>

template <typename T>
class MyAllocator {
public:

    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using pointer         = T*;
    using const_pointer   = const T*;

    
    MyAllocator() noexcept = default;
    MyAllocator(const MyAllocator&) noexcept = default;
    
    template <typename U>
    MyAllocator(const MyAllocator<U>&) noexcept {}

    T* allocate(std::size_t n) {
        if (n == 0) return nullptr;
    
        if (n > std::size_t(-1) / sizeof(T))
            throw std::bad_alloc();
        
        if (auto p = static_cast<T*>(::operator new(n * sizeof(T))))
        {
            std::cout << "Add memory\n";
            return p;
        }
        throw std::bad_alloc();
    }

    void deallocate(T* p, std::size_t /*n*/) noexcept {
        std::cout << "Delete memory\n";
        if (p) ::operator delete(p);
    }


    friend bool operator==(const MyAllocator&, const MyAllocator&) noexcept { return true; }
    friend bool operator!=(const MyAllocator&, const MyAllocator&) noexcept { return false; }
};

void printVector(std::vector<int, MyAllocator<int>> &vec)
{
    std::cout << "\n{ ";
    for( int element : vec )
    {
        std::cout << element << " ,";
    }
    std::cout << "\b}\n";
}

int main(){
    std::vector<int, MyAllocator<int>> vec;

    for( int i = 0; i < 111; ++i     ){
        vec.push_back(1);
        std::cout << vec.size() << "\n";
    }
    
    return 0;
}