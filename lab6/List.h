#pragma once
#include <iostream>
#include <stdexcept>

class List {
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val = 0) : data(val), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int size;
    friend class ListIter;
public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    
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
            // Очищаем текущий список
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
    
    void pushFront(int a) {
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
    
    void pushBack(int a) {
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
    
    int front() const {
        if (head == nullptr) throw std::runtime_error("List is empty");
        return head->data;
    }
    
    int back() const {
        if (tail == nullptr) throw std::runtime_error("List is empty");
        return tail->data;
    }
    Node* begin() { return head; }
    Node* end() { return nullptr; }
    // Не-const версия operator[]
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }
        return tmp->data;
    }
    
    const int& operator[](int index) const {
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

inline List operator*(const List& l1, const List& l2) {
    if (l1.getSize() != l2.getSize()) {
        std::cout << "Wrong! Sizes differ: " << l1.getSize() << " vs " << l2.getSize() << std::endl;
        return List();  // возвращаем пустой список
    }
    
    List res(l1.getSize());
    for (int i = 0; i < l1.getSize(); i++) {
        res[i] = l1[i] * l2[i];
    }
    return res;
}
