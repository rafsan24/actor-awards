#include <iostream>
#include "actor.h"

using namespace std;

template <class T>
class BstNode {
  public: 
    Actor* actor;
    T key;
    BstNode* parent;
    BstNode** parentPtr;
    BstNode* left;
    BstNode* right;
    BstNode(Actor* actor, T key, BstNode<T>* parent, BstNode<T>** parentPtr, BstNode<T>* left, BstNode<T>* right);

    bool isLeaf();
    void remove();
    BstNode* findMax();
};

template <class T>
class BST {
  private: 
    void inorderTraversal(BstNode<T>* node);
  
  public: 
    int length = 0;
    BstNode<T>* root = nullptr;
    void add(Actor* actor, T key); 
    Actor* remove(T key);
    Actor* find(T key);
    Actor* findMax();
    void getAll();
};
