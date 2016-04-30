#ifndef ANIMALS_H //and a few plants
#define ANIMALS_H //and a few plants

#include <string>
#include <vector>
#include <map>

#include "intermediate.h"

class Trout : public Fish {
    public:
        Trout(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return true;}
        bool isHerbivore() const {return false;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return false;}
        bool livesOnLand()  const {return false;}
        bool livesInWater() const {return true;}
};

class Tortoise : public Reptile {
    public:
        Tortoise(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return false;}
        bool isHerbivore() const {return true;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return false;}
        bool livesOnLand()  const {return true;}
        bool livesInWater() const {return false;}
};

class Platypus : public Mammal, public LaysEggs {
    public:
        Platypus(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return true;}
        bool isHerbivore() const {return false;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return false;}
        bool livesOnLand()  const {return true;}
        bool livesInWater() const {return true;}
};

class Cardinal : public Bird {
    public:
        Cardinal(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return false;}
        bool isHerbivore() const {return true;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return true;}
        bool livesOnLand()  const {return false;}
        bool livesInWater() const {return false;}
};

class Penguin : public Bird {
    public:
        Penguin(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return true;}
        bool isHerbivore() const {return false;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return false;}
        bool livesOnLand()  const {return true;}
        bool livesInWater() const {return true;}
};

class Bat : public Mammal {
    public:
        Bat(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return true;}
        bool isHerbivore() const {return false;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return true;}
        bool livesOnLand()  const {return true;}
        bool livesInWater() const {return false;}
};


class Tiger : public Mammal {
    public:
        Tiger(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return true;}
        bool isHerbivore() const {return false;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return false;}
        bool livesOnLand()  const {return true;}
        bool livesInWater() const {return false;}
};

class Rhinoceros : public Mammal {
    public:
        Rhinoceros(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return false;}
        bool isHerbivore() const {return true;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return false;}
        bool livesOnLand()  const {return true;}
        bool livesInWater() const {return false;}
};

class Bear : public Mammal {
    public:
        Bear(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return false;}
        bool isHerbivore() const {return false;}
        bool isOmnivore()  const {return true;}
        
        bool livesInAir()   const {return false;}
        bool livesOnLand()  const {return true;}
        bool livesInWater() const {return false;}
};

class VenusFlyTrap : public Plant{
    public:
        VenusFlyTrap(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return true;}
        bool isHerbivore() const {return false;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return false;}
        bool livesOnLand()  const {return true;}
        bool livesInWater() const {return false;}
};

class Redwood : public Plant {
    public:
        Redwood(const std::map<std::string, std::vector<std::string> >& data) throw (int);

        bool isCarnivore() const {return false;}
        bool isHerbivore() const {return false;}
        bool isOmnivore()  const {return false;}
        
        bool livesInAir()   const {return false;}
        bool livesOnLand()  const {return true;}
        bool livesInWater() const {return false;}
};

#endif
