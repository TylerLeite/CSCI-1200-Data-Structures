#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

#include <string>
#include <map>
#include <vector>

#include "organism.h"

class LaysEggs : public virtual Organism {
    public:
        LaysEggs(const std::map<std::string, std::vector<std::string> >& data) throw (int);
        
        bool DoesLayEggs(){return true;}
};

class Plant : public virtual Organism {
    public:
        Plant(const std::map<std::string, std::vector<std::string> >& data) throw (int);
};

class Animal : public virtual Organism {
    public:
        Animal(const std::map<std::string, std::vector<std::string> >& data) throw (int);
};

class Ectothermic : public Animal {
    public:
        Ectothermic(const std::map<std::string, std::vector<std::string> >& data) throw (int);
        
        bool WarmBlooded(){return false;}
        bool ColdBlooded(){return true;}
};

class Endothermic : public Animal {
    public:
        Endothermic(const std::map<std::string, std::vector<std::string> >& data) throw (int);
        
        bool WamBlooded(){return true;}
        bool ColdBlooded(){return false;}
};

class Bird : public LaysEggs, public Endothermic {
    public:
        Bird(const std::map<std::string, std::vector<std::string> >& data) throw (int);
};

class Reptile : public LaysEggs, public Ectothermic {
    public:
        Reptile(const std::map<std::string, std::vector<std::string> >& data) throw (int);
};

class Fish : public LaysEggs, public Ectothermic {
    public:
        Fish(const std::map<std::string, std::vector<std::string> >& data) throw (int);
};

class Mammal : public Endothermic {
    public:
        Mammal(const std::map<std::string, std::vector<std::string> >& data) throw (int);
};

#endif
