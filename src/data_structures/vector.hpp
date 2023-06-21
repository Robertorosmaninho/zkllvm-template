#include <cassert>

template<typename T> struct Vector {
private:
    LinkedList<T> list;
    size_t size_;

public:
    Vector() : size_(0) {}

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void push_front(const T& value, typename LinkedList<T>::Node*& head) {
        list.insert_front(head, value);
        ++size_;
    }

    void push_back(const T& value, typename LinkedList<T>::Node*& head) {
        list.insert_back(head, value);
        ++size_;
    }

    T& at(size_t index, typename LinkedList<T>::Node* head) {
        assert(index < size_);

        typename LinkedList<T>::Iterator it(head);
        for (size_t i = 0; i < index; ++i) {
            ++it;
        }
        return *it;
    }

    const T& at(size_t index, typename LinkedList<T>::Node* head) const {
        assert(index < size_);

        typename LinkedList<T>::Iterator it(head);
        for (size_t i = 0; i < index; ++i) {
            ++it;
        }
        return *it;
    }

    typename LinkedList<T>::Iterator begin(typename LinkedList<T>::Node* head) {
        return list.begin(head);
    }

    typename LinkedList<T>::Iterator end() {
        return list.end();
    }
};