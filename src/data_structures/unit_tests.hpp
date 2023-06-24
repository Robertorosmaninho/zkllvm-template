#include "linked_list.hpp"
#include "deque.hpp"
#include "map.hpp"
#include "queue.hpp"
#include "set.hpp"
#include "vector.hpp"

#include <cassert>
#include <cstdlib>

#ifndef ZKLLVM
#include <iostream>
#endif

// Unit tests for LinkedList
int testLinkedList() {
#ifndef ZKLLVM
  std::cout << "Testing LinkedList..." << std::endl;
#endif
  LinkedList<int> myList;

  // Test insert and display
  LinkedList<int>::Node *head = nullptr;
  myList.insert_back(head, 10);
  myList.insert_back(head, 20);
  myList.insert_front(head, 5);

#ifndef ZKLLVM
  // Test iterator begin and end
  auto it = myList.begin(head);
  auto end = myList.end();

  // Test iterator and range-based for loop
  std::cout << "Using iterator to display the list: \n";
  for (; it != end; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
#endif

  // Test empty list
  LinkedList<int>::Node *emptyHead = nullptr;

  // Expected: Begin and end iterators should be equal for empty list
  assert(myList.begin(emptyHead) == myList.end());

  // Expected: Begin and end iterators should not be equal for non-empty list
  assert(myList.begin(head) != myList.end());

  // Test destructor
  {
    LinkedList<int> tempList;

    LinkedList<int>::Node *tempHead = nullptr;
    tempList.insert_front(tempHead, 100);
    tempList.insert_front(tempHead, 200);
    tempList.insert_front(tempHead, 300);

    // tempList is destroyed, memory is freed
  }

#ifndef ZKLLVM
  std::cout << "All tests passed!" << std::endl;
#endif
  return 0;
}

// Unit tests for Vector
int testVector() {
#ifndef ZKLLVM
  std::cout << "Testing Vector..." << std::endl;
#endif
  Vector<int> myVector;

  // Test push_back and display
  LinkedList<int>::Node *head = nullptr;

  myVector.push_back(10, head);
  myVector.push_back(20, head);
  myVector.push_front(5, head);

  // Test iterator begin and end
  auto it = myVector.begin(head);
  auto end = myVector.end();

#ifndef ZKLLVM
  // Test iterator and range-based for loop
  // Expected output: 5 10 20
  std::cout << "Using iterator to display the list: \n";
  for (; it != end; ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
#endif

  while (it != end) {
    ++it;
  }

  // Test empty vector
  Vector<int> emptyVector;
  LinkedList<int>::Node *emptyHead = nullptr;
  assert(emptyVector.begin(emptyHead) == emptyVector.end());
  assert(emptyVector.empty());

  // Test at
  assert(myVector.at(0, head) == 5);

  // Test size
  assert(myVector.size() == 3);
  assert(emptyVector.size() == 0);

  // Test destructor
  {
    Vector<int> tempVector;

    LinkedList<int>::Node *tempHead = nullptr;
    tempVector.push_front(100, tempHead);
    tempVector.push_front(200, tempHead);
    tempVector.push_front(300, tempHead);

    // tempVector is destroyed, memory is freed
  }

#ifndef ZKLLVM
  std::cout << "All tests passed!" << std::endl;
#endif

  return 0;
}

// Unit tests for Map
void testMap() {
#ifndef ZKLLVM
  std::cout << "Testing Map..." << std::endl;
#endif

  Map<int, int> myMap;
  LinkedList<Map<int, int>::Entry>::Node *mapHead = nullptr;

  myMap.insert(1, 10, mapHead);
  myMap.insert(2, 20, mapHead);
  myMap.insert(3, 30, mapHead);

  // Test contains
  assert(myMap.contains(2, mapHead));
  assert(myMap.contains(3, mapHead));
  assert(!myMap.contains(4, mapHead));

  // Test at
  assert(myMap.at(2, mapHead) == 20);
  //assert(myMap.at("four", mapHead) == 4);

#ifndef ZKLLVM
  std::cout << "All tests passed!" << std::endl;
#endif
}

// Unit tests for deque
void testDeque() {
#ifndef ZKLLVM
  std::cout << "Testing Deque..." << std::endl;
#endif
  Deque<int> myDeque;
  LinkedList<int>::Node *dequeHead = nullptr;

  myDeque.push_back(10, dequeHead);
  myDeque.push_back(20, dequeHead);
  myDeque.push_front(5, dequeHead);

#ifndef ZKLLVM
  std::cout << "Front: " << myDeque.front(dequeHead) << std::endl;
  std::cout << "Back: " << myDeque.back(dequeHead) << std::endl;
  std::cout << "Size: " << myDeque.size(dequeHead) << std::endl;
  std::cout << "Empty: " << std::boolalpha << myDeque.empty(dequeHead)
            << std::endl;
#endif

  assert(myDeque.front(dequeHead) == 5);
  assert(myDeque.back(dequeHead) == 20);
  assert(myDeque.size(dequeHead) == 3);
  assert(!myDeque.empty(dequeHead));

#ifndef ZKLLVM
  std::cout << "All tests passed!" << std::endl;
#endif
}

// Unit test for Set
int testSet() {
#ifndef ZKLLVM
  std::cout << "Testing Set..." << std::endl;
#endif
  Set<int> mySet;
  LinkedList<int>::Node *setHead = nullptr;

  mySet.insert(10, setHead);
  mySet.insert(20, setHead);
  mySet.insert(30, setHead);
  mySet.insert(20, setHead); // Duplicate, should be ignored

#ifndef ZKLLVM
  std::cout << "Set size: " << mySet.size(setHead) << std::endl;
  std::cout << "Set contains 10: " << std::boolalpha
            << mySet.contains(10, setHead) << std::endl;
  std::cout << "Set contains 20: " << std::boolalpha
            << mySet.contains(20, setHead) << std::endl;
  std::cout << "Set contains 30: " << std::boolalpha
            << mySet.contains(30, setHead) << std::endl;
  std::cout << "Set contains 40: " << std::boolalpha
            << mySet.contains(40, setHead) << std::endl;
#endif

  assert(mySet.size(setHead) == 3);
  assert(mySet.contains(10, setHead));
  assert(mySet.contains(20, setHead));
  assert(mySet.contains(30, setHead));
  assert(!mySet.contains(40, setHead));
#ifndef ZKLLVM
  std::cout << "All tests passed!" << std::endl;
#endif
  return 0;
}

int testQueue() {
#ifndef ZKLLVM
  std::cout << "Testing Queue..." << std::endl;
#endif
  Queue<int> myQueue;
  LinkedList<int>::Node *queueHead = nullptr;

  myQueue.enqueue(10, queueHead);
  myQueue.enqueue(20, queueHead);
  myQueue.enqueue(30, queueHead); 
  myQueue.enqueue(40, queueHead);

#ifndef ZKLLVM
  std::cout << "Dequeue: " << myQueue.dequeue(queueHead) << std::endl;
  std::cout << "Dequeue: " << myQueue.dequeue(queueHead) << std::endl;
  std::cout << "Is empty? " << std::boolalpha << myQueue.empty(queueHead)
            << std::endl;
#endif

#ifdef ZKLLVM
assert(myQueue.dequeue(queueHead) == 10);
assert(myQueue.dequeue(queueHead) == 20);
assert(!myQueue.empty(queueHead));
#endif

#ifndef ZKLLVM
  std::cout << "All tests passed!" << std::endl;
#endif
  return 0;
}
