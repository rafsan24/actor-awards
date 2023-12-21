#include "bst.h"

template <class T>
BstNode<T>::BstNode(Actor* actor, T key, BstNode<T>* parent, BstNode<T>** parentPtr, BstNode<T>* left, BstNode<T>* right) : 
  actor(actor),
  key(key),
  parent(parent),
  parentPtr(parentPtr),
  left(left),
  right(right)
  { }

template <class T>
bool BstNode<T>::isLeaf() { 
  return left == nullptr && right == nullptr; 
}

template <class T>
void BstNode<T>::remove() {
  if (isLeaf()) {
    // Case 1. No child -- Simply delete
    *parentPtr = nullptr;
  } else if ((left == nullptr) != (right == nullptr)) {
    // Case 2. Single child -- Swap with child
    BstNode* child = (left != nullptr) ? left : right;
    if (parentPtr != nullptr) *parentPtr = child;
    child->parent = parent;
    child->parentPtr = parentPtr;
  } else {
    // Case 3. Both children -- Swap with inorder predecessor
    BstNode* predecessor = left->findMax();
    if (parentPtr != nullptr) *parentPtr = predecessor;
    predecessor->parent = parent;
    predecessor->parentPtr = parentPtr;
    predecessor->right = right;
  }
}

template <class T>
BstNode<T>* BstNode<T>::findMax() {
  BstNode* current = this;
  while (current->right != nullptr) {
    current = current->right;
  }
  return current;
}

template <class T>
void BST<T>::add(Actor* actor, T key) {
  BstNode<T>* node = new BstNode<T>(actor, key, nullptr, nullptr, nullptr, nullptr);
  if (root == nullptr) {
    root = node;
    node->parentPtr = &root;
    length = 1;
    return;
  }
  BstNode<T>* current = root;
  while (true) {
    BstNode<T>** childPtr = (key < current->key) ? &(current->left) : &(current->right);
    if (*childPtr == nullptr) {
      *childPtr = node;
      node->parent = current;
      node->parentPtr = childPtr;
      length++;
      return;
    } else {
      current = *childPtr;
    }
  } 
}

template <class T>
Actor* BST<T>::remove(T key) {
  BstNode<T>* current = root;
  while (current != nullptr) {
    if (key == current->key) {
      Actor* result = current->actor;
      current->remove();
      delete current;
      length--;
      return result;
    } else if (key < current->key) {
      current = current->left;
    } else if (key > current->key) {
      current = current->right;
    }
  }
  return nullptr;
}

// Helper function to perform in-order traversal and collect actors.
template <class T>
void BST<T>::inorderTraversal(BstNode<T>* node) {
  if (node != nullptr) {
    inorderTraversal(node->left); // Traverse left subtree
    if (!node->actor->hasAward) {
      cout << node->actor->id << " " << node->actor->first << " " << node->actor->last << " has " << node->actor->points << " praise points" << endl;
    }
    inorderTraversal(node->right);// Traverse right subtree
  }
}

template <class T>
void BST<T>::getAll() {
  inorderTraversal(root);
}

// Finds an actor by their key.
template <class T>
Actor* BST<T>::find(T key) {
  BstNode<T>* current = root;
  while (current != nullptr) {
    if (key == current->key) {
      return current->actor;
    } else if (key < current->key) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return nullptr; // Return null if the key is not found
}

// Finds the actor with the maximum key.
template <class T>
Actor* BST<T>::findMax() {
  if (root == nullptr) {
    return nullptr;
  }
  BstNode<T>* current = root;
  while (current->right != nullptr) {
    current = current->right;
  }
  return current->actor; // The node on the right holds the max key
}

template class BST<int>;
template class BST<string>;
