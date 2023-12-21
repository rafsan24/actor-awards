#include "actor.h"

class PraiseHeap {
  private:
    int capacity = 100;
    Actor** heap = new Actor*[100];
    void resize();

    int getParent(int index);
    int getLeft(int index);
    int getRight(int index);

    void swap(int index1, int index2);
    void heapifyDown(int index);
    void heapifyUp(int index);
    
  public: 
    int length = 0;
    PraiseHeap();
    void add(Actor* actor);
    Actor* pop();
    bool remove(Actor* actor);
    void debugPrint();
};