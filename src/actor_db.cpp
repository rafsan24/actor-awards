#include "actor_db.h"
#include <iostream>

using namespace std;

/// O(N)
int ActorDB::registerActor(Actor* actor) {
	// Insert the actor into the BSTs
	Actor* inDB = actorsByID.find(actor->id);
	if (inDB != nullptr) return 1;
	actorsByLastName.add(actor, actor->last); 
	actorsByID.add(actor, actor->id);
	actorsByPraise.add(actor);
	return 0;
} 

/// Bonus, O(N)
int ActorDB::removeActor(ActorID id) {
	// Remove the actor from the BSTs
	Actor* actor = actorsByID.find(id);
	if (actor == nullptr) return 1;
	actorsByLastName.remove(actor->last); 
	actorsByID.remove(actor->id);
	actorsByPraise.remove(actor);
	delete actor;
	return 0;
} 

/// O(log N)
int ActorDB::praiseActor(string lastName, int points) {
	Actor* actor = actorsByLastName.find(lastName);
	if (actor == nullptr) return 1;
	else if (actor->hasAward) return 2;
	actorsByPraise.remove(actor);
	actor->points += points;
	actorsByPraise.add(actor);
	return 0;
}

/// Disqualify from receiving any more praise. O(log N)
Actor* ActorDB::awardActor() {
	Actor* actor = actorsByPraise.pop();
	if (actor == nullptr) return nullptr;
	actor->hasAward = true;
	return actor;
}

/// Shows every actor and their praise. O(N)
void ActorDB::showPraise() {
	// Use the getAll method from BST class to display all actors and their praise points
	actorsByID.getAll(); // Assuming actorsByID BST holds all actors sorted by their ID
} 
