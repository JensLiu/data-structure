#include <iostream>
#include <fstream>

template<typename T>
class LinkedList;

/**
 * Iterator for linked list
 */

template <typename LinkedListType>
class LinkedListIterator {
public:
    using ValueType = typename LinkedListType::ValueType;
    using NodeType = typename LinkedListType::NodeType;
    friend class LinkedList<ValueType>;

private:
    NodeType* m_Ptr;

public:
    LinkedListIterator() {
        m_Ptr = nullptr;
    }

    LinkedListIterator(NodeType* ptr) {
        m_Ptr = ptr;
    }

    LinkedListIterator(const LinkedListIterator& copy) {
        m_Ptr = copy.m_Ptr;
    }

    LinkedListIterator& operator++() {
        m_Ptr = m_Ptr->next;
        return *this;
    }

    LinkedListIterator operator++(int) {
        NodeType*  tmp = m_Ptr;
        m_Ptr = m_Ptr->next;
        return LinkedListIterator(tmp);
    }

    LinkedListIterator& operator--() {
        m_Ptr = m_Ptr->prev;
        return *this;
    }

    ValueType& operator*() {
        return m_Ptr->data;
    }

    NodeType* operator->() {
        return m_Ptr;
    }

    bool operator==(LinkedListIterator other) {
        return other.m_Ptr == this->m_Ptr;
    }

    bool operator!=(LinkedListIterator other) {
        return other.m_Ptr != this->m_Ptr;
    }

    LinkedListIterator operator+(int num) {
        NodeType* t = m_Ptr;
        for (int i = 1; i <= num; i++) {
            if (t != nullptr) {
                t++;
            }
        }
        return LinkedListIterator(t);
    }

    LinkedListIterator operator-(int num) {
        NodeType* t = m_Ptr;
        for (int i = 1; i <= num; i++) {
            if (t != nullptr) {
                t--;
            }
        }
        return LinkedListIterator(t);
    }

    bool isNull() {
        return m_Ptr == nullptr;
    }

};


/*
 * Node type for doubly linked list
 */

template <typename T>
class DllistNode {
public:
    T data;
    DllistNode* next;
    DllistNode* prev;
    DllistNode() {
        next = nullptr;
        prev = nullptr;
    }
    DllistNode(const T& data)
        : data(data) {
        DllistNode();
    }
};

/*
 * Doubly circular linked list class
 */

template <typename T>
class LinkedList {
public:
    using ValueType = T;
    using NodeType = DllistNode<T>;
    using Iterator = LinkedListIterator<LinkedList<T>>;

private:
    DllistNode<T> *head;
    int elementCount;

public:
    LinkedList() {
        head = new DllistNode<T>;
        // set both pointers to point to head to make circular link
        head->next = head;
        head->prev = head;
        // currently no element
        this->elementCount = 0;
    }

    ~LinkedList() {
        DllistNode<T>* p = head->next;
        erase();
        delete head;
    }


    // manipulations using pointers (internal)
private:

    // insert after the given position
    DllistNode<T>* _insertAfter(DllistNode<T>* where, T elem) {
        DllistNode<T>* newNode = new DllistNode<T>(elem);
        newNode->next = where->next;
        newNode->prev = where;
        where->next->prev = newNode;
        where->next = newNode;
        elementCount++;

        return newNode;
    }

    DllistNode<T>* _insertBefore(DllistNode<T>* where, T elem) { return _insertAfter(where->prev, elem); }


    DllistNode<T>* _pushFront(T elem) {
        // to insert at the front is to insert after the head node
        return _insertAfter(this->head, elem);
    }


    DllistNode<T>* _pushBack(T elem) {
        /*
         *   proposition 1: to insert at the end is to insert after the tail
         *   proposition 2: the tail is the previous node of the head
         *   => pushback = insert_after(tail) = insert_after(head->prev)
         */
         return _insertAfter(this->head->prev, elem);
    }


    DllistNode<T>* _find(T elem) {
        DllistNode<T>* p = head->next;
        /*  (1) if there is no element in the list:
         *          p = head->next = head
         *          the p == head, will not enter the loop
         *          return false
         *
         *  (2) if the element is in the list: (p = head->next != head)
         *          (i) if the element is the first element of the list:
         *              when p = head->next, the element is found
         *
         *          (ii) if the element is in the middle of the list:
         *              the element is found
         *
         *          (iii) if the element is the last element of the list:
         *              when p = tail = head->prev, the element is found
         */
        while (p != head) {
            if (p->data == elem) {
                return p;
            }
            p = p->next;
        }
        return nullptr;
    }

    DllistNode<T>* _breakFree(DllistNode<T>* p) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        p->prev = nullptr;
        p->next = nullptr;
        return p;
    }

    // quick sort implementation using pointers
private:
    DllistNode<T>* _quicksort_partition(DllistNode<T>* begin, DllistNode<T>* end, bool(*compare)(T t1, T t2) = nullptr) {

        /* begin_ptr: the pointer to the first position to sort
         * end_ptr: the pointer to the end position to sort (still count as the sublist to sort)
         */

        DllistNode<T>* p = begin;
        DllistNode<T>* q = end;

        T key = begin->data;

        while (p != q) {
            while (p != q && (compare == nullptr && q->data > key
                              || compare != nullptr && !compare(q->data, key)) ) {
                q = q->prev;
            }
            p->data = q->data;
            while (p != q && (compare == nullptr && p->data <= key
                              || compare != nullptr && compare(p->data, key)) ) {
                p = p->next;
            }
            q->data = p->data;
        }
        p-> data = key;
        return p;

        /*
         * TO ENTER THIS FUNCTION: begin_ptr != end_ptr
         *
         *
         * Initialisation: Prior to the first iteration,  p = begin and q = end, the first condition of the loop is satisfied.
         *                 begin.value is extracted from the list, which leaves p points to a blank position.
         *
         * Maintenance: we consider:
         *              (1) when p points to the start, q points to the end, conditions in both interval [start, p] and (q, end] are trivially satisfied.
         *                  => q starts to move
         *
         *              (1) when q stop moving: [start, p] (q, end] satisfy the condition,
         *                  meaning: q does not satisfy the condition => q->data <= key
         *                  do: p->data = q->data, because q->data <= key, then p->data <= key
         *                  => partitioned interval: [start, p], [q, end]
         *                  => p starts to move
         *
         *              (2) when p stop moving: [start, p) [q, end] satisfy the condition,
         *                  meaning: p does not satisfy the condition => q->data > key
         *                  do: q->data = p->data, because p->data > key, then q->data > key
         *                  => q->data now satisfies the condition
         *                  => partitioned interval: [start, p], [q, end]
         *                  => q starts to move
         *
         *  Termination:
         *      If there exists a scenario where p stops moving and p is exactly one node before q:
         *           after the value change, starts another iteration.
         *
         *          we consider the scenarios of the last iteration:
         *              when q stops moving and q is exactly one node after p:
         *                  (1-1) after value change, the partitioned interval is [start, p] [q, end], because p, q are integer and p = q - 1,
         *                        the interval becomes [start, end] BUT value at p and q are THE SAME
         *
         *                  (1-2) q moves one node to the front:
         *                        q meets p (p == q), does not enter the next loop.
         *                        do another trivial value change (since p = q, do self value change), end of the current iteration
         *                        outer loop condition not satisfies, loop terminates.
         *
         *          after the loop terminates, p->data = key, so that the value of p->data and p->prev->data are not the same,
         *          and p is the separation position.
         *
         *
         *
         */


    }

    void _quicksort(DllistNode<T>* begin, DllistNode<T>* end, bool(*compare)(T t1, T t2) = nullptr) {

        if (end == begin->prev || begin == end->next) {
            return;
        }

        if (begin != end) {
            DllistNode<T>* mid = _quicksort_partition(begin, end, compare);
            _quicksort(begin, mid->prev, compare);
            _quicksort(mid->next, end, compare);
        }

        /*
         *  Each recursion returns two lists where:
         *      left[start, mid) <= mid <= right[mid, end)
         *
         *  When begin = end, recursion terminates: single element is sorted.
         *
         *  The before second return statement:
         *      left <= mid <= right is a sorted list with three elements.
         *
         *  Defined recursively, the element on the right is always less than the middle,
         *                  and the middle element is always less than elements on the right.
         *
         *   list[0] <= list[1] <= ... <= list[n-1] <= list[n]
         *
         */


    }

    // interface using Iterator as parameters and return types
public:

    /**
     * Insert an element after the position given
     * @param where: the Iterator to the position to insert after
     * @param elem: the element to insert
     * @return the Iterator to the inserted position
     */
    Iterator insertAfter(Iterator where, T elem) { return Iterator(_insertAfter(where.m_Ptr, elem)); }

    /**
     * Insert an element before the position given
     * @param where: the Iterator to the position to insert before
     * @param elem: the element to insert
     * @return the Iterator to the inserted position
     */
    Iterator insertBefore(Iterator where, T elem) { return Iterator(_insertBefore(where.m_Ptr, elem)); }

    /**
     * Insert to the front of the list
     * @param elem: the element to insert to the front of the list
     * @return the Iterator to the inserted position
     */
    Iterator pushFront(T elem) { return Iterator(_pushFront(elem)); }

    /**
     * Insert to the end of the list
     * @param elem: the element to insert to the front of the list
     * @return the Iterator to the inserted position
     */
    Iterator pushBack(T elem) { return Iterator(_pushBack(elem)); }

    /**
     * Find the Iterator to the first repetitive element given
     * @param elem: the element to find
     * @return the Iterator to the first repetitive element given
     */
    Iterator find(T elem) { return Iterator(_find(elem)); }

    /**
     * The beginning of the list
     * @return Iterator to be beginning of the list
     */
    Iterator begin() { return Iterator(head->next); }

    /**
     * The end of the list
     * @return Iterator to the end of the list
     */
    Iterator end() { return Iterator(head); }

    /**
     * Separate a node from the list
     * @param p: the Iterator to the position to be separated
     * @return the Iterator to the separated position
     */
    Iterator breakFree(Iterator p) { return Iterator(_breakFree(p.m_Ptr)); }

    /**
     * Traverse the list with the given format
     * @param displayFormat: the format to print a certain element
     */
    void showList(void (*displayFormat)(T data) = nullptr) {
        DllistNode<T> *p = head->next;
        while (p != head) {
            if (displayFormat == nullptr) {
                std::cout << p->data << " ";
            } else {
                displayFormat(p->data);
            }
            p = p->next;
        }
    }

    void erase() {
        DllistNode<T>* p = head->next;
        DllistNode<T>* q;
        while (p != head) {
            q = p;
            p = p->next;
            delete q;
        }
        head->next = head;
        head->prev = head;
    }

    // quick sort interface using Iterator as parameters
public:
    /**
     * Sort list
     * @param begin: Iterator to the position to begin sorting
     * @param end: Iterator one node after the position to end sorting
     * @param compare: the function to compare two elements(return true to sort, false to skip)
     */
    void quicksort(Iterator begin, Iterator end, bool(*compare)(T t1, T t2) = nullptr) {
        _quicksort(begin.m_Ptr, end.m_Ptr->prev, compare);
    }


    bool saveToFile(const char* fileName = "data") {
        std::ofstream target;
        target.open(fileName, std::ios::binary | std::ios::out);
        if (!target) return false;
        DllistNode<T>* p = head->next;
        while (p != head) {
            T tmp = p->data;
            target.write((char*)&tmp, sizeof(T));
            p = p->next;
        }
        target.close();
        return true;
    }

    bool readFromFile(const char* fileName = "data") {
        std::ifstream target;
        target.open(fileName, std::ios::binary | std::ios::in);
        if (!target) return false;
        while (true) {
            T tmp;
            target.read((char*)&tmp, sizeof(T));
            if (target.eof()) break;
            pushBack(tmp);
        }
        target.close();
        return true;
    }


};


// custom data type test
class Integer{
    int data;
public:
    Integer() {
        data = 0;
    }
    Integer(int i) {
        data = i;
    }
    int getData() {
        return data;
    }
    void setData(int i) {
        data = i;
    }
    bool operator<(Integer integer) const {
        return data < integer.getData();
    }
    bool operator<=(Integer integer) const {
        return data <= integer.getData();
    }
    bool operator>(Integer integer) const {
        return data > integer.getData();
    }
    bool operator>=(Integer integer) const {
        return data >= integer.getData();
    }
};

std::ostream& operator<<(std::ostream& os, Integer integer) {
    os << integer.getData();
    return os;
}

int main() {

    // test: Initialise list
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(1);
    list.pushBack(6);
    list.pushBack(5);

    // test: traverse list (with operator<< overload)
    list.showList();
    std::cout << std::endl;

    // test: traverse list (with lambda function as format)
    list.showList([](int i) { std::cout << i << "--"; });
    std::cout << std::endl;

    // test: quick sort ascending (with lambda function as compare)
    list.quicksort(list.begin(), list.end(), [](int i, int j) { return i < j; } );
    list.showList();
    std::cout << std::endl;

    // test: quick sort descending (with lambda function as compare)
    list.quicksort(list.begin(), list.end(), [](int i, int j) { return i > j; } );
    list.showList();
    std::cout << std::endl;

    // test: quick sort ascending (with operator< overload)
    list.quicksort(list.begin(), list.end());
    list.showList();
    std::cout << std::endl;


    LinkedList<Integer> intList;
    Integer integer(1);
    intList.pushFront(integer);
    integer.setData(2);
    intList.pushFront(integer);
    integer.setData(1);
    intList.pushFront(integer);
    integer.setData(6);
    intList.pushFront(integer);

    intList.showList();
    std::cout << std::endl;

    intList.quicksort(intList.begin(), intList.end(), [](Integer integer1, Integer integer2) {
       return integer1.getData() < integer2.getData();
    });
    intList.showList();
    std::cout << std::endl;

    intList.quicksort(intList.begin(), intList.end(), [](Integer integer1, Integer integer2) {
        return integer1.getData() > integer2.getData();
    });
    intList.showList();
    std::cout << std::endl;

    intList.quicksort(intList.begin(), intList.end());
    intList.showList();
    std::cout << std::endl;

    intList.showList([](Integer integer) {
       std::cout << integer.getData() << "**";
    });
    std::cout << std::endl;

    intList.saveToFile();
    intList.erase();

    std::cout << "list:";
    intList.showList();
    std::cout << std::endl;

    intList.readFromFile();
    intList.showList();
    std::cout << std::endl;

    return 0;
}
