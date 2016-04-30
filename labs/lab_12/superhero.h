#ifndef SUPERHERO_H
#define SUPERHERO_H

#include <iostream>
#include <map>
#include <string>

static std::map<std::string, int> powers;

class Team;   
class Superhero {
    public:
        Superhero(std::string name, std::string identity, std::string power) :
            name(name), identity(identity), power(power), good(true)
        {
            if (powers.count(power) == 0){
                powers.insert(std::pair<std::string, int>(power, powers.size()));
            }
        }

        bool operator==(const std::string& guess) const {
            return identity == guess;
        }

        bool operator==(const Superhero& rhs) const {
            return name == rhs.name && identity == rhs.identity && power == rhs.power;
        }

        bool operator!=(const std::string& guess) const {
            return identity != guess;
        }

        bool operator>(const Superhero& rhs) const {
            if (power == "Fire"){
                if (rhs.power == "Wood"){
                    return true;
                } else if (rhs.power == "Water"){
                    return false;
                }
            } else if (power == "Water"){
                if (rhs.power == "Fire"){
                    return true;
                } else if (rhs.power == "Wood"){
                    return false;
                }
            } else if (power == "Wood"){
                if (rhs.power == "Water"){
                    return true;
                } else if (rhs.power == "Fire"){
                    return false;
                }
            }
            
            return powers[power] > powers[rhs.power];
        }

        Superhero operator-(){
            good = !good;
            return *this;
        }

        std::string getName()  const {return name;}
        std::string getPower() const {return power;}
        bool isGood() const {return good;}

        friend std::ostream& operator<<(std::ostream& out, const Superhero& hero){
            out << "Superhero " << hero.getName() 
                << " has power " << hero.getPower() << std::endl;
            return out;
        }

        friend class Team;

    private:
        std::string getTrueIdentity() const {return identity;}
        
        std::string name, identity, power;
        bool good;
};

#endif
