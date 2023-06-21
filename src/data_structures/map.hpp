template <typename K, typename V> struct Map {
  struct Entry {
    K key;
    V value;
  };
  LinkedList<Entry> list;

  void insert(const K &key, const V &value,
              typename LinkedList<Entry>::Node *&head) {
    typename LinkedList<Entry>::Iterator entry(head);
    for (; entry != list.end(); ++entry) {
      if (entry->key == key) {
        entry->value = value;
        return;
      }
    }

    Entry newEntry;
    newEntry.key = key;
    newEntry.value = value;
    list.insert_back(head, newEntry);
  }

  bool contains(const K &key, typename LinkedList<Entry>::Node *&head) {
    typename LinkedList<Entry>::Iterator entry(head);
    for (; entry != list.end(); ++entry) {
      if (entry->key == key) {
        return true;
      }
    }
    return false;
  }

  V &at(const K &key, typename LinkedList<Entry>::Node *&head) {

    typename LinkedList<Entry>::Iterator current(head);
    for (; current != list.end(); ++current) {
      if (current->key == key) {
        return current->value;
      }
    }
    // Key not found in the map.
    exit(1);
  }
};