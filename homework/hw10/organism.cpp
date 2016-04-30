#include "organism.h"

Organism::Organism(const std::map<std::string, std::vector<std::string> >& data){

    //have to check if a field is provided since you can't use operator[]
    if (data.count("name:") != 0 && data.at("name:").size() != 0){
        name = data.at("name:")[0];
    }
    
    if (data.count("type:") != 0 && data.at("type:").size() != 0){
        type = data.at("type:")[0];
    }

    if (data.count("lifespan:") != 0 &&data.at("lifespan:").size() != 0){
        lifespan = data.at("lifespan:")[0];
    }

    if (data.count("adult_weight:") != 0 && data.at("adult_weight:").size() != 0){
        adult_weight = data.at("adult_weight:")[0];
    }

    if (data.count("lives_in:") != 0){
        lives_in = data.at("lives_in:");
    }

    if (data.count("has:") != 0){
        has = data.at("has:");
    }

    if (data.count("eats:") != 0){
        eats = data.at("eats:");
    }
}

//figure out facts about the animal if they are not provided explicitly
bool Organism::isCarnivore() const {
    if (eats.size() == 0){
        return false;
    }

    std::vector<std::string> meat_foods;
    meat_foods.push_back("deer");
    meat_foods.push_back("fish");
    meat_foods.push_back("bugs");
    meat_foods.push_back("animals");
    
    return !containsOtherThan(eats, meat_foods);
}

bool Organism::isHerbivore() const {
    if (eats.size() == 0){
        return false;
    }
    
    std::vector<std::string> vegetarian_choices;
    vegetarian_choices.push_back("leaves");
    vegetarian_choices.push_back("plants");
    vegetarian_choices.push_back("seeds");
    vegetarian_choices.push_back("grass");
    
    return !containsOtherThan(eats, vegetarian_choices);
}

bool Organism::isOmnivore() const {
    if (eats.size() == 0){
        return false;
    } else {
        return !isCarnivore() && !isHerbivore();
    }
}

bool Organism::livesInAir() const {
    for (int i = 0; i < lives_in.size(); i++){
        if (lives_in[i] == "air"){
            return true;
        }
    }

    return false;
}

bool Organism::livesOnLand() const {
    for (int i = 0; i < lives_in.size(); i++){
        if (lives_in[i] == "land"){
            return true;
        }
    }

    return false;
}

bool Organism::livesInWater() const {
    for (int i = 0; i < lives_in.size(); i++){
        if (lives_in[i] == "water"){
            return true;
        }
    }

    return false;
}

/**************************/

//checks if data is a subset of testAgainst
bool containsOtherThan(const std::vector<std::string>& data, 
                       const std::vector<std::string>& testAgainst){
    for (int i = 0; i < data.size(); i++){
        bool checks_out = false;

        //check each element of data. as long as it matches at least one element
        // in testAgainst, that element in data is fine and the loop moves on
        for (int j = 0; j < testAgainst.size(); j++){
            if (data[i] == testAgainst[j]){
                checks_out = true;
                break;
            }
        }   

        if (checks_out){
            continue;
        } else {
            return true;
        }
    }

    return false;
}
