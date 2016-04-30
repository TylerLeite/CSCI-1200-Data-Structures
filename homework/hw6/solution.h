#ifndef SOLUTION_H
#define SOLUTION_H

#include <algorithm>
#include <string>
#include <list>

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

bool fits_with(const Tile* t1, const Tile* t2, int side){
    if (t1 == NULL || t2 == NULL) return true;

    //std::cout << " rots " << t1->loc.rotation << " " << t2->loc.rotation << std::endl;
    
    /*
    if (side == NORTH)
        std::cout << t1->getNorth() << ":" << t2->getSouth() << std::endl;
    else if (side == EAST)
        std::cout << t1->getEast() << ":" << t2->getWest() << std::endl;
    else if (side == SOUTH)
        std::cout << t1->getSouth() << ":" << t2->getNorth() << std::endl;
    else if (side == WEST)
        std::cout << t1->getWest() << ":" << t2->getEast() << std::endl;
    else
        std::cout << "oh, no! something has gone horribly wrong!" << std::endl;
    //*/
    
    if (side == NORTH) return t1->getNorth() == t2->getSouth();
    if (side == EAST)  return t1->getEast() == t2->getWest();
    if (side == SOUTH) return t1->getSouth() == t2->getNorth();
    if (side == WEST)  return t1->getWest() == t2->getEast();
}

Location get_loc_neighbor(int direction, const Location& loc){
    int yOff = 0, xOff = 0; //offsets based on direction

    if      (direction == NORTH) yOff = -1;
    else if (direction == EAST)  xOff =  1;
    else if (direction == SOUTH) yOff =  1;
    else if (direction == WEST)  xOff = -1;

    Location newLoc(loc.row+yOff, loc.column+xOff, 0); //todo: fix for rotations
    return newLoc;
}

Tile* get_neighbor(int direction, const Location& loc, const std::list<Tile*>& possibleNeighbors){
    Location test_loc = get_loc_neighbor(direction, loc);
    
    for (std::list<Tile*>::const_iterator it = possibleNeighbors.begin(); it != possibleNeighbors.end(); it++){
        if ((*it)->loc == test_loc){ //operator== ignores rotations
            return *it;
        }
    }

    return NULL; //no neighbor to that side
}


//check if a piece works
bool piece_fits (Tile* toPlace, const std::list<Tile*>& possibleNeighbors){
    bool works = true;
    for (int i = 0; i < 4; i++){//check if that location is a legal placement
        Tile* surrounding = get_neighbor(i, toPlace->loc, possibleNeighbors);
        if (!fits_with(toPlace, surrounding, i)){
            /*
            std::cout << i << " doesn't work: "
                      << toPlace->getNorth() << toPlace->getEast() << toPlace->getSouth() << toPlace->getWest() << toPlace->loc.rotation
                      << " "
                      << surrounding->getNorth() << surrounding->getEast() << surrounding->getSouth() << surrounding->getWest() << surrounding->loc.rotation
                      << std::endl;
            //*/
            works = false;
            break;
        }
    }

    return works;
}


bool solution_viable(std::list<Tile*>& toOut, int boardWdt, int boardHgt){
    //check if pieces go out of bounds
    int minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;
    for (std::list<Tile*>::iterator it = toOut.begin(); it != toOut.end(); it++){
        if ((*it)->loc.column < minX){
            minX = (*it)->loc.column;
        }

        if ((*it)->loc.column > maxX){
            maxX = (*it)->loc.column;
        }

        if ((*it)->loc.row < minY){
            minY = (*it)->loc.row;
        }

        if ((*it)->loc.row > maxY){
            maxY = (*it)->loc.row;
        }
    }

    if (maxX-minX < boardWdt && maxY-minY < boardHgt){
        return true;
    } else {
        return false;
    }
}

bool tile_has_loose_ends(const Tile* tile, const std::list<Tile*>& possibleNeighbors){
return false;
    for (int i = 0; i < 4; i++){
        std::string side;
        
        if      (i == NORTH) side = tile->getNorth();
        else if (i == EAST)  side = tile->getEast();
        else if (i == SOUTH) side = tile->getSouth();
        else if (i == WEST)  side = tile->getWest();
        
        if (side == "pasture") continue;
        
        if (get_neighbor(i, tile->loc, possibleNeighbors) == NULL){
            return true;
        }
    }
    
    return false;
}

//TODO: fix allowing rotations and all solutions

//NOTE: unplacedTiles must be reversed before being passed to this function for the first time
//do locations relatively, start at 0,0 and dont mind when it goes negative
// then shift everything until it is all positive. if a placement woudld go out
// of bounds, leave it in and test them later to get rid of them.
std::list<std::list<Tile*> > place_tiles(std::list<Tile*> unplacedTiles, int boardWdt, int boardHgt, bool allowRotations){//dont want to pass by reference
    std::list<std::list<Tile*> > out;
    if (unplacedTiles.size() == 0){
        std::cout << "0" << std::endl;
        return out;
    } else if (unplacedTiles.size() == 1){
        int rotations = 1; if (allowRotations) rotations = 4;
        
        for (int i = 0; i < rotations; i++){
            Tile* tile = unplacedTiles.front();
            Tile* new_tile = new Tile(tile->getNorth(), tile->getEast(), tile->getSouth(), tile->getWest());
            new_tile->loc.rotation = 90*i;
            
            std::list<Tile*> toOut;
            toOut.push_back(new_tile);
            out.push_back(toOut);
        }
        
        return out;
    } else {
        Tile* toPlace = unplacedTiles.front();
        unplacedTiles.erase(unplacedTiles.begin());

        std::list<std::list<Tile*> > soFar = place_tiles(unplacedTiles, boardWdt, boardHgt, allowRotations);

      //why can't i hold all these for loops?
      //todo: replace all for loops with recursion because why not
        for (std::list<std::list<Tile*> >::iterator p = soFar.begin(); p != soFar.end(); p++){ //loop through all placement options so far
            std::vector<Location> locationsTried; //avoid redundancy in the case of placing a tile between two tiles
            //std::cerr << "size:" << p->size() << std::endl;
            for (std::list<Tile*>::iterator t = p->begin(); t != p->end(); t++){ //loop through tiles in that placement
                for (int s = 0; s < 4; s++){ //loop through each side the tile could be placed on
                    if (get_neighbor(s, (*t)->loc, *p) != NULL){continue;} //check if there is already a tile there
                    Location newLoc = get_loc_neighbor(s, (*t)->loc); //get location the tile would be placed at

                    bool already = false; //was this location already tried
                    for (int i = 0; i < locationsTried.size(); i++){//check if that location was tried yet
                        if (locationsTried[i] == newLoc){
                            already = true;
                        }
                    }
                    if (already) continue;
                    
                    locationsTried.push_back(newLoc);
                    //std::cout << "p: " << p << ", t: " << t << ", loc: " << newLoc << std::endl;

                    int rotations = 1; if (allowRotations) rotations = 4;

                    for (int d = 0; d < rotations; d++){//loop through all rotation
                        //std::cout << "Moving to rotation: " << d << std::endl;
                        //Location new_newLoc = Location(newLoc.row, newLoc.column, d*90);
                        //newLoc.rotation = d*90;
                        Tile* realToPlace = new Tile(toPlace->getNorth(), toPlace->getEast(), toPlace->getSouth(), toPlace->getWest());
                        realToPlace->loc.row = newLoc.row; realToPlace->loc.column = newLoc.column; realToPlace->loc.rotation = d*90;

                        if (!piece_fits(realToPlace, *p)){delete realToPlace; continue;}
                        
                        //add path to output that is current path plus toPlace
                        std::list<Tile*> toOut;
                        for (std::list<Tile*>::iterator tile = p->begin(); tile != p->end(); tile++){
                            Tile* new_tile = new Tile((*tile)->getNorth(), (*tile)->getEast(), (*tile)->getSouth(), (*tile)->getWest());
                            new_tile->loc = (*tile)->loc;
                            toOut.push_back(new_tile);
                        }
                        
                        toOut.push_back(realToPlace);

                        if (solution_viable(toOut, boardWdt, boardHgt)){//check if pieces go out of bounds
                            //std::cout << newLoc << std::endl;
                            out.push_back(toOut);
                        } else {
                            for (std::list<Tile*>::iterator it = toOut.begin(); it != toOut.end(); it++){
                                delete (*it);
                            }
                        }
                    }
                }
            }
        }

        std::cout << "got to end: " << out.size() << std::endl;
        return out;
    }
}

std::list<std::list<Tile*> > solve(std::list<Tile*>& unplacedTiles, int boardWdt, int boardHgt, bool allowRotations){
    std::reverse(unplacedTiles.begin(), unplacedTiles.end());

    std::list<std::list<Tile*> > solutions;
    solutions = place_tiles(unplacedTiles, boardWdt, boardHgt, allowRotations);

    //make everything positive
    for (std::list<std::list<Tile*> >::iterator it = solutions.begin(); it != solutions.end(); it++){
        bool valid = true;
        int minX = 1000, minY = 1000;
        std::list<Tile*>::iterator tile;
        for (tile = it->begin(); tile != it->end(); tile++){
            if (tile_has_loose_ends(*tile, *it)){ //scrap solutions with incomplete roads or cities
                it = solutions.erase(it);
                it--;
                valid = false;
                break;
            }
            
            if ((*tile)->loc.column < minX){
                minX = (*tile)->loc.column;
            }

            if ((*tile)->loc.row < minY){
                minY = (*tile)->loc.row;
            }
        }
        
        if (!valid) continue;

        if (minX >= 0 && minY >= 0) continue;
        
        for (tile = it->begin(); tile != it->end(); tile++){
            if (minX < 0){
                (*tile)->loc.column -= minX;
            }

            if (minY < 0){
                (*tile)->loc.row -= minY;
            }
        }
    }

    return solutions;
}

#endif
