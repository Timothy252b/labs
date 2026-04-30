#pragma once
#include <iostream>
#include <stdexcept>

template <class Data>
class List {
    template<typename> friend class List;
    struct Node {
        Data data;
        Node* prev;
        Node* next;
        Node(Data val = 0) : data(val), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size;
public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    template <class OtherType>
    List(const List<OtherType>& other) : head(nullptr), tail(nullptr), size(0) {
        for (int i = 0; i < other.getSize(); i++) {
            pushBack(static_cast<Data>(other[i]));
        }
    }

    List(int n) : head(nullptr), tail(nullptr), size(0) {
        for (int i = 0; i < n; i++) {
            pushBack(0);
        }
    }
    
    List(const List& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current != nullptr) {
            pushBack(current->data);
            current = current->next;
        }
    }
    
    ~List() {
        while (head != nullptr) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        size = 0;
    }
    
    List& operator=(const List& other) {
        if (this != &other) {
            while (head != nullptr) {
                Node* tmp = head;
                head = head->next;
                delete tmp;
            }
            head = tail = nullptr;
            size = 0;
            
            Node* current = other.head;
            while (current != nullptr) {
                pushBack(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    void pushFront(Data a) {
        Node* newNode = new Node(a);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    
    void pushBack(Data a) {
        Node* newNode = new Node(a);
        
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }
    
    void popFront() {
        if (head == nullptr) {
            std::cout << "List is empty!" << std::endl;
            return;
        }
        
        Node* tmp = head;
        head = head->next;
        
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        
        delete tmp;
        size--;
    }
    
    void popBack() {
        if (tail == nullptr) {
            std::cout << "List is empty!" << std::endl;
            return;
        }
        
        Node* tmp = tail;
        tail = tail->prev;
        
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        
        delete tmp;
        size--;
    }
    
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    
    void print() const {
        Node* current = head;
        std::cout << "List (size=" << size << "): ";
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
    
    Data front() const {
        if (head == nullptr) throw std::runtime_error("List is empty");
        return head->data;
    }
    
    Data back() const {
        if (tail == nullptr) throw std::runtime_error("List is empty");
        return tail->data;
    }
    Node* begin() const { return head; }
    Node* end() const { return nullptr; }
    
    Data& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
        return tmp->data;
    }
    
    const Data& operator[](int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
        return tmp->data;
    }
    
    int operator()() const {
        return size;
    }
};
template<typename T1, typename T2>
inline auto operator*(const List<T1>& l1, const List<T2>& l2) {
    using ResultType = decltype(std::declval<T1>() * std::declval<T2>());
    List<ResultType> result;
    
    auto it1 = l1.begin();
    auto it2 = l2.begin();
    while (it1 != l1.end() && it2 != l2.end()) {
        result.pushBack(it1->data * it2->data);
        it1 = it1->next;
        it2 = it2->next;
    }
    
    return result;
}
