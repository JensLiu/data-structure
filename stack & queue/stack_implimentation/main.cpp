#include <iostream>

template <typename T>
class SllistNode {
public:
    T data;
    SllistNode* next;
    SllistNode(T data) {
        this->data = data;
        this->next = nullptr;
    }
    SllistNode(T data) {
        this->
    }
};


template <typename T>
class Stack {
private:
    SllistNode<T>* head;
public:
    Stack() {
        head = new SllistNode<T>();
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
