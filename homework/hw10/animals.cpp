#include "animals.h"

Trout::Trout(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Fish(data)
{
    if (type != "" && type != "trout"){
        throw -1;
    }

    if (lifespan != "" && lifespan != "<100yrs"){
        throw -1;
    }

    if (adult_weight != "" && adult_weight != "<100lbs"){
        throw -1;
    }
    
    //check if the organism described by the data eats things the trout
    // cannot eat, has things the trout cannot have, or lives in things
    // the trout cannot live in
    std::vector<std::string> can_eats;
    can_eats.push_back("bugs");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("scales");
    can_has.push_back("fins");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("water");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

Tortoise::Tortoise(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Reptile(data)
{
    if (type != "" && type != "tortoise"){
        throw -1;
    }
    
    if (lifespan != "" && lifespan != ">100yrs"){
        throw -1;
    }

    if (adult_weight != ""){
        throw -1;
    }
    
    std::vector<std::string> can_eats;
    can_eats.push_back("leaves");
    can_eats.push_back("plants");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("scales");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("land");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

Platypus::Platypus(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Mammal(data), LaysEggs(data)
{
    if (type != "" && type != "platypus"){
        throw -1;
    }
    
    if (lifespan != "" && lifespan != "<100yrs"){
        throw -1;
    }

    if (adult_weight != "" && adult_weight != "<100lbs"){
        throw -1;
    }

    std::vector<std::string> can_eats;
    can_eats.push_back("bugs");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("bill");
    can_has.push_back("fur");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("land");
    can_lives_in.push_back("water");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

Cardinal::Cardinal(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Bird(data)
{
    if (type != "" && type != "cardinal"){
        throw -1;
    }
    
    if (lifespan != "" && lifespan != "<100yrs"){
        throw -1;
    }

    if (adult_weight != "" && adult_weight != "<100lbs"){
        throw -1;
    }

    std::vector<std::string> can_eats;
    can_eats.push_back("seeds");
    can_eats.push_back("plants");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("feathers");
    can_has.push_back("bill");
    can_has.push_back("wings");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("air");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

Penguin::Penguin(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Bird(data)
{
    if (type != "" && type != "penguin"){
        throw -1;
    }

    if (lifespan != "" && lifespan != "<100yrs"){
        throw -1;
    }

    if (adult_weight != "" && adult_weight != "<100lbs"){
        throw -1;
    }
    
    std::vector<std::string> can_eats;
    can_eats.push_back("fish");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("feathers");
    can_has.push_back("bill");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("water");
    can_lives_in.push_back("land");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

Bat::Bat(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Mammal(data)
{
    if (type != "" && type != "bat"){
        throw -1;
    }

    std::vector<std::string> can_eats;
    can_eats.push_back("bugs");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("wings");
    can_has.push_back("teeth");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("land");
    can_lives_in.push_back("air");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

Tiger::Tiger(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Mammal(data)
{
    if (type != "" && type != "tiger"){
        throw -1;
    }

    if (lifespan != "" && lifespan != "<100yrs"){
        throw -1;
    }

    if (adult_weight != "" && adult_weight != ">100lbs"){
        throw -1;
    }
    
    std::vector<std::string> can_eats;
    can_eats.push_back("animals");
    can_eats.push_back("deer");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("stripes");
    can_has.push_back("fur");
    can_has.push_back("teeth");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("land");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

Rhinoceros::Rhinoceros(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Mammal(data)
{
    if (type != "" && type != "rhinoceros"){
        throw -1;
    }

    if (lifespan != "" && lifespan != "<100yrs"){
        throw-1;
    }

    if (adult_weight != "" && adult_weight != ">100lbs"){
        throw -1;
    }
    
    std::vector<std::string> can_eats;
    can_eats.push_back("grass");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("fur");
    can_has.push_back("teeth");
    can_has.push_back("horn");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("land");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

Bear::Bear(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Mammal(data)
{
    if (type != "" && type != "bear"){
        throw -1;
    }
    
    if (lifespan != "" && lifespan != "<100yrs"){
        throw -1;
    }

    if (adult_weight != "" && adult_weight != ">100lbs"){
        throw -1;
    }

    std::vector<std::string> can_eats;
    can_eats.push_back("bugs");
    can_eats.push_back("plants");
    can_eats.push_back("fish");
    can_eats.push_back("deer");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("fur");
    can_has.push_back("teeth");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("land");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

VenusFlyTrap::VenusFlyTrap(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Plant(data)
{
    if (type != "" && type != "venus_fly_trap"){
        throw -1;
    }

    if (lifespan != "" && lifespan != "<100yrs"){
        throw -1;
    }

    if (adult_weight != "" && adult_weight != "<100lbs"){
        throw -1;
    }
    
    std::vector<std::string> can_eats;
    can_eats.push_back("bugs");
    if (containsOtherThan(eats, can_eats)){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("roots");
    can_has.push_back("leaves");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("land");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}

Redwood::Redwood(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Plant(data)
{
    if (type != "" && type != "redwood"){
        throw -1;
    }
    
    if (lifespan != "" && lifespan != ">100yrs"){
        throw -1;
    }

    if (adult_weight != "" && adult_weight != ">100lbs"){
        throw -1;
    }

    if (eats.size() != 0){
        throw -1;
    }
    
    std::vector<std::string> can_has;
    can_has.push_back("roots");
    can_has.push_back("branches");
    can_has.push_back("leaves");
    if (containsOtherThan(has, can_has)){
        throw -1;
    }
    
    std::vector<std::string> can_lives_in;
    can_lives_in.push_back("land");
    if (containsOtherThan(lives_in, can_lives_in)){
        throw -1;
    }
}
