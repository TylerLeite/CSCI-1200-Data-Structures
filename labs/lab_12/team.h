#ifndef _TEAM_H_
#define _TEAM_H_

#include <string>
#include <iostream>
#include <list>

#include "superhero.h"

class Team {

public:

  // accessor function
  std::string getName() const;

  // adding and removing a single superhero
  void operator+=(const Superhero &a) {superheroes.push_back(a);}
  void operator-=(const Superhero &a) {superheroes.remove(a);}

  // adding two teams together or a team and a superhero together
  // makes a team.  these functions must be member functions to allow
  // access to the list of superheroes.
  friend Team operator+(const Team &a, const Team &b){
    Team out;
    std::list<Superhero>::const_iterator it;
    for (it = a.superheroes.begin(); it != a.superheroes.end(); it++){
        out += *it;
    }

    for (it = b.superheroes.begin(); it != b.superheroes.end(); it++){
        out += *it;
    }

    return out;
  }
  
  friend Team operator+(const Team &a, const Superhero &b){
    Team out;
    std::list<Superhero>::const_iterator it;
    for (it = a.superheroes.begin(); it != a.superheroes.end(); it++){
        out += *it;
    }

    out += b;

    return out;
  }
  
private:
  // REPRESENATION
  std::list<Superhero> superheroes;
};

Team operator+(const Superhero &a, const Superhero &b);

#endif
