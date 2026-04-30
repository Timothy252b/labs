#include "List.h"

class ListIter {
    List::Node* iter;
    friend class List;
public:
    ListIter() : iter(0) {}
    ListIter(List::Node* pN) : iter(pN) {}
    ListIter(List::Node& n) : iter(&n) {}
    ListIter(List& l) : iter(l.begin()) {}
    ~ListIter() {}
    ListIter operator+(int step) {
        List::Node* tmp = iter;
        for (int i = 0; i < step&&tmp!=nullptr; i++) {
            tmp = tmp->next;
        }
        return ListIter(tmp);
    }
    int& operator*() {
        return iter->data;
    }
};
