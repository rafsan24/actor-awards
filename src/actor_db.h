#include "actor.h"
#include "bst.h"
#include "heap.h"

class ActorDB {
  public:  // Made more things public for testing 
    BST<string> actorsByLastName;
    BST<int> actorsByID;
    PraiseHeap actorsByPraise;
  
    int registerActor(Actor* actor);  // O(N)
    int removeActor(ActorID id);  // Bonus, O(N)
    int praiseActor(string lastName, int points);  // O(log N)
    Actor* awardActor();  // Disqualify from receiving any more praise. O(log N)
    void showPraise();  // Shows every actor and their praise. O(N)
};
