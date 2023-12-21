#pragma once

#include <string>

using namespace std;
using ActorID = int;

class Actor {   
  public: 
    ActorID id;
    string first;
    string last;
    int points = 0;
    bool hasAward = false;

    Actor(ActorID id, string first, string last);
    string toString();
};
