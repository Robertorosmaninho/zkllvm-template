template <typename T> struct Queue {
private:
  LinkedList<T> list;

public:
  bool empty(typename LinkedList<T>::Node *head) const {
    return head == nullptr;
  }
  void enqueue(const T &value, typename LinkedList<T>::Node *&head) {
    list.insert_back(head, value);
  }

  T dequeue(typename LinkedList<T>::Node *&head) {
    assert(!empty(head));
    return list.remove_front(head);
  }
};