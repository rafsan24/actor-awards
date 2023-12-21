#include "actor.h"

Actor::Actor(ActorID id, string first, string last) : 
  id(id),
  first(first),
  last(last)
  { }

string Actor::toString() {
  return first + " " + last;
}
