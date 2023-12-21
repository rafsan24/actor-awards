#include <iostream>
#include <fstream>
#include <getopt.h>
#include <assert.h>

#include "actor_db.h"
#include "Parser.h"

using namespace std;

static const char *UNEXPECTED_ARGS = "unexpected arguments";
static const char *MISSING_ARGS = "missing arguments";

ActorDB database;

void award_actor() {
  Actor* actor = database.awardActor();
  if (actor == nullptr) {
		cout << "No actor to award." << endl;
  } else {
  	cout << "Actor " << actor->first << " " << actor->last 
		<< " presented with a Lifetime Achievement Award (" 
		<< actor->points << " praise points)" << endl;
  }
}

void register_actor(Actor* actor) {
  int result = database.registerActor(actor);
  if (result == 0) {
    cout << "Registered actor " << actor->first << " " << actor->last << endl;
  } else if (result == 1) {
    cout << "Error actor id " << actor->id << " already in use" << endl;
    delete actor;
  }
}

void remove_actor(ActorID id) {
  int result = database.removeActor(id);
  if (result == 0) {
    cout << "Removed actor id " << id << endl;
  } else if (result == 1) {
    cout << "Error actor id " << id << " does not exist" << endl;
  }
}

void praise_actor(string lastName, int praisePoints) {
  int result = database.praiseActor(lastName, praisePoints);
  if (result == 1) {
    cout << "Could not find an actor with the last name " << lastName;
    return;
  }
  Actor* actor = database.actorsByLastName.find(lastName);
  if (result == 0) {
    cout << "Awarding actor " << actor->toString() << " " << praisePoints << " praise points." << endl;
  } else if (result == 2) {
    cout << "That's nice but actor " << actor->toString() << " has already received the award." << endl;
  }
}

bool accept_commands(istream &is, bool silent=false, bool echo=false) {
  string command;  
  string line;

  while (1) {
    if (!silent) {
      cout << endl << "Enter a command: " << endl;
      cout << "Choose from " << endl;
      cout << "   register_actor <actorid> <last> <first>" << endl; 
      cout << "   remove_actor <actorid>" << endl; 
      cout << "   praise_actor <last-name> <praise-points>" << endl; 
      cout << "   award_actor" << endl; 
      cout << "   show_praise" << endl; 
      cout << "   quit" << endl; 
      cout << ": ";
    }

    getline(is, line);
    if (echo) {
      cout << endl;
      cout << "======================================================" << endl;
      cout << line << endl;
      cout << "======================================================" << endl;
    }

    Parser p(line);
    if (p.getOperation().empty()) {
      if (is.fail()) return false;
      continue;
    }

    if (p.getOperation() == "quit") {
      if (p.numArgs() > 0) cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
      return true;
    } else if (p.getOperation() == "register_actor") {
      if (p.numArgs() < 3) {
        cout << endl; 
        cout << "Can't operate with " << MISSING_ARGS << endl;
        continue;
      } else if (p.numArgs() > 3) {
        cout << endl;
        cout << "Ignoring " << UNEXPECTED_ARGS << endl;
      }
      ActorID id = stoi(p.getArg(1));
      string last = p.getArg(2);
      string first = p.getArg(3);
      Actor* actor = new Actor(id, first, last);
      register_actor(actor);
    } else if (p.getOperation() == "remove_actor") {
      if (p.numArgs() < 1) {
        cout << endl; 
        cout << "Can't operate with " << MISSING_ARGS << endl;
        continue;
      } else if (p.numArgs() > 1) {
        cout << endl;
        cout << "Ignoring " << UNEXPECTED_ARGS << endl;
      }
      ActorID id = stoi(p.getArg(1));
      remove_actor(id);
    } else if (p.getOperation() == "praise_actor") {
      if (p.numArgs() < 2) {
        cout << endl; 
        cout << "Can't operate with " << MISSING_ARGS << endl;
        continue;
      } else if (p.numArgs() > 2) {
        cout << endl;
        cout << "Ignoring " << UNEXPECTED_ARGS << endl;
      }
      string last = p.getArg(1);
      int points = stoi(p.getArg(2));
      praise_actor(last, points);
    } else if (p.getOperation() == "award_actor") {
      if (p.numArgs() > 0) cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
      award_actor();
    } else if (p.getOperation() == "show_praise") {
      if (p.numArgs() > 0) cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl; 
      database.showPraise();
    } else {
      cout << std::endl << "Command not recognized. Please try again." << endl; 
    }
    cout << endl;
  }
  return true;
}

int main() {
  accept_commands(cin, false, false);
  return 0;
}
