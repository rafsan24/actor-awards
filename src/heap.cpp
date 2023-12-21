#include <iostream>
using namespace std;

#include "heap.h"

PraiseHeap::PraiseHeap() {
  heap[0] = nullptr;
}

void PraiseHeap::resize() {
  capacity *= 2;
  Actor** newHeap = new Actor*[capacity];
  for (int index = 0; index < length; index++) {
    newHeap[index] = heap[index];
  }
  delete[] heap;
  heap = newHeap;
}

int PraiseHeap::getParent(int index) {
  return index / 2;
}

int PraiseHeap::getLeft(int index) {
  return 2 * index;
}

int PraiseHeap::getRight(int index) {
  return (2 * index) + 1;
}

// bool PraiseHeap::isLeaf(int index) {
//   return (index >= (length / 2)) && (index <= length);
// }

void PraiseHeap::swap(int index1, int index2) {
  Actor* temp = heap[index1];
  heap[index1] = heap[index2];
  heap[index2] = temp;
}

void PraiseHeap::heapifyDown(int index) {
  Actor* node = heap[index];
  Actor* left = heap[getLeft(index)];
  Actor* right = heap[getRight(index)];
  if (node == nullptr) return;
  if (left == nullptr && right != nullptr && node->points < right->points) {
    // Node only has right child and is smaller than it -- swap with right
    swap(index, getRight(index));
    heapifyDown(getRight(index));
  } else if (left != nullptr && right == nullptr && node->points < left->points) {
    // Node only has left child and is smaller than it -- swap with left
    swap(index, getLeft(index));
    heapifyDown(getLeft(index));
  } else if (left != nullptr && right != nullptr && (node->points < left->points || node->points < right->points)) {
    // Node has both children and is smaller than one of them
    if (left->points > right->points) {
      // Left node is the largest child -- swap with left
      swap(index, getLeft(index));
      heapifyDown(getLeft(index));
    } else {
      // Right node is the largest child -- swap with right
      swap(index, getRight(index));
      heapifyDown(getRight(index));
    }
  }
}

void PraiseHeap::heapifyUp(int index) {
  Actor* node = heap[index];
  while (index > 0) {
    Actor* parent = heap[getParent(index)];
    if (parent == nullptr) break;
    if (node->points <= parent->points) break;
    heap[index] = parent;
    index = getParent(index);
  }
  heap[index] = node;
}

void PraiseHeap::add(Actor* actor) {
  if (length == capacity) resize();
  heap[++length] = actor;
  heapifyUp(length);
}

Actor* PraiseHeap::pop() {
  // The heap starts at index 1
  if (length == 0) return nullptr;
  Actor* result = heap[1];
  heap[1] = heap[length];
  heap[length] = nullptr;
  length--;
  heapifyDown(1);
  return result;
}

bool PraiseHeap::remove(Actor* actor) {
  Actor* stack[length];
  Actor* result = nullptr;
  int index = -1;
  while (length != 0) {
    result = pop();
    if (result->id == actor->id) break;
    stack[++index] = result;
  }
  for (int index2 = index; index2 >= 0; index2--) {
    add(stack[index2]);
  }
  return result == actor;
}

void PraiseHeap::debugPrint() {
  cout << "[";
  for (int index = 1; index <= length; index++) {
    Actor* actor = heap[index];
    cout << "Actor(ID=" << actor->id << ", Points=" << actor->points << ")";
    if (index != (length)) cout << ", ";
  }
  cout << "]" << endl;
}
