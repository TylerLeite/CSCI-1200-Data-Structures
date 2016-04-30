#include "intermediate.h"

LaysEggs::LaysEggs(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
    Organism(data)
{
    if (data.count("lays_eggs:") != 0 && data.at("lays_eggs:").size() != 0 &&
        data.at("lays_eggs:")[0] != "true"){
        throw -1;
    }
}


Plant::Plant(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
    Organism(data)
{
    for (int i = 0; i < has.size(); i++){
        //plants only have roots leaves and branches
        if (has[i] != "roots" && has[0] != "leaves" && has[i] != "branches"){
            throw -1;
        }
    }
}

Animal::Animal(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
    Organism(data)
{
    for (int i = 0; i < has.size(); i++){
        //animals don't have roots or leaves
        if (has[i] == "roots" || has[i] == "leaves"){
            throw -1;
        }
    }
}

Ectothermic::Ectothermic(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
    Organism(data), Animal(data)
{
    if (data.count("warm_blooded:") != 0 && data.at("warm_blooded:").size() != 0 && 
        data.at("warm_blooded:")[0] == "true"){
        throw -1;
    }

     if (data.count("cold_blooded:") != 0 && data.at("cold_blooded:").size() != 0 && 
        data.at("cold_blooded:")[0] == "false"){
        throw -1;
    }
}

Endothermic::Endothermic(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
    Organism(data), Animal(data)
{
    if (data.count("cold_blooded:") != 0 && data.at("cold_blooded:").size() != 0 && 
        data.at("cold_blooded:")[0] == "true"){
        throw -1;
    }

    if (data.count("warm_blooded:") != 0 && data.at("warm_blooded:").size() != 0 && 
        data.at("warm_blooded:")[0] == "false"){
        throw -1;
    }
}

Bird::Bird(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), LaysEggs(data), Endothermic(data)
{}

Reptile::Reptile(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), LaysEggs(data), Ectothermic(data)
{}

Fish::Fish(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), LaysEggs(data), Ectothermic(data)
{}

Mammal::Mammal(const std::map<std::string, std::vector<std::string> >& data) throw (int) :
     Organism(data), Endothermic(data)
{}
