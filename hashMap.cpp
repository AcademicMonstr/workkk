#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

template <class Key, class Value>
class HashMap
{
private:
    static constexpr size_t minbucksize{};

    class Node
    {
        Key k;
        Value v;
        size_t h;
        Node* next;
        Node(Key k_, Value v_, Node* next_ = nullptr) : k(k_), v(v_), next(next_){};
    };

    std::vector<Node*> buckeds;
    size_t cur_cap;
    size_t size_;
    double max_load_factor = 0.75;
    HashMap(size_t init_size = 0)
    {
        if (init_size < minbucksize)
        {
            cur_cap = minbucksize;
            buckeds = std::vector<Node*>(minbucksize);
        }
        else
        {
            cur_cap = init_size;
            buckeds = std::vector<Node*>(init_size);
        }
    }
    ~HashMap() 
    {
        for (size_t i{}; i < this->cur_cap; ++i) 
        {
            Node* current = this->buckeds[i];
            while (current != nullptr) 
            {
                Node* next = current->next;
                delete current;
                current = next;
            }
        }
    }
    void insert(const Key& key, const Value& value)
    {
        size_t hash_val = std::hash<Key>{}(key);
        size_t index = hash_val % cur_cap;
        
        Node* current = buckeds[index];

        if((cur_cap + 1) / static_cast<float>(size_))
        {
            resize(cur_cap * 1.5);   
        }

        while (current != nullptr)
        {
            if (current->k == key)
            {
                current->v = value;
                return;
            }
            current = current->next;
        }
        Node* new_first_node = new Node(key, value, buckeds[index]);
        if (buckeds[index] != nullptr) { new_first_node->next = buckeds[index]; }
        buckeds[index] = new_first_node;

    }

    Value* find(const Key& key)
    {
        size_t hash_val = std::hash<Key>{}(key);
        size_t index = hash_val % cur_cap;

        Node* current = buckeds[index];

        while (current != nullptr)
        {
            if (current->k == key)
            {
                return current->v;
            }
            current = current->next;
        }
    }

    void resize(size_t new_cap)
    {
        if (new_cap < minbucksize) 
        {   
            new_cap = minbucksize;
        }

        std::vector<Node*> new_buckets(new_cap, nullptr);

        for (Node* head : buckeds)
        {
            Node* current = head;
            while (current != nullptr)
            {
                Node* next_node = current->next;
                size_t new_index = std::hash<Key>{}(current->k) % new_cap;

                current->next = new_buckets[new_index];
                new_buckets[new_index] = current;

                current = next_node;
                
            }
        }
        buckeds = std::move(new_buckets);
        cur_cap = new_cap;
    }

    bool remove(const Key& k) 
    {
        size_t hash_val = std::hash<Key>{}(k);
        size_t ind = hash_val % cur_cap;

        Node* current = this->buckeds[ind];
        Node* prev = nullptr;

        while (current != nullptr) 
        {
            if (current->k == k) 
            {
                if (prev == nullptr)
                {
                    this->buckeds[ind] = current->next;
                }
                else 
                {
                    prev->next = current->next;
                }
                delete current;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }



    
    
    
};
int main() 
{

}
