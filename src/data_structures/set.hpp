template <typename T> struct Set {
private:
  LinkedList<T> list;

public:
  bool contains(const T &value, typename LinkedList<T>::Node *head) const {
    typename LinkedList<T>::Iterator element(head);
    for (; element != list.end(); ++element) {
      if (*element == value) {
        return true;
      }
    }
    return false;
  }

  void insert(const T &value, typename LinkedList<T>::Node *&head) {
    if (contains(value, head)) {
      return;
    }

    list.insert_back(head, value);
  }

  void remove(const T &value, typename LinkedList<T>::Node *&head) {
    typename LinkedList<T>::Iterator it = list.begin(head);
    while (it != list.end()) {
      if (*it == value) {
        if (it.current->prev != nullptr) {
          it.current->prev->next = it.current->next;
        } else {
          head = it.current->next;
        }

        if (it.current->next != nullptr) {
          it.current->next->prev = it.current->prev;
        }
        std::free(it.current);
        break;
      }
      ++it;
    }
  }

  size_t size(typename LinkedList<T>::Node *head) const {
    size_t count = 0;
    typename LinkedList<T>::Iterator element(head);
    while (element != list.end()) {
      ++element;
      ++count;
    }
    return count;
  }
};