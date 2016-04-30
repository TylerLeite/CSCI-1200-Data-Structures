#ifndef ORGANISM_H
#define ORGANISM_H

#include <string>
#include <map>
#include <vector>

#include <iostream>

//checks if data is a subset of testAgainst
bool containsOtherThan(const std::vector<std::string>& data, 
                       const std::vector<std::string>& testAgainst);

class Organism {
    public:
        Organism(const std::map<std::string, std::vector<std::string> >& data);
        virtual ~Organism(){}

        std::string getName() const {return name;}
        
        virtual bool isCarnivore() const;
        virtual bool isHerbivore() const;
        virtual bool isOmnivore() const;
        
        virtual bool livesInAir() const;
        virtual bool livesOnLand() const;
        virtual bool livesInWater() const;

    protected:
        std::string name, type, lifespan, adult_weight;
        std::vector<std::string> has, lives_in, eats;
};

#endif
