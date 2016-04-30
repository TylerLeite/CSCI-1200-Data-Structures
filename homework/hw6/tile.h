#ifndef  __TILE_H__
#define __TILE_H__

#include <iostream>
#include <string>
#include <vector>

#include "location.h"
// This class represents a single Carcassonne tile and includes code
// to produce a human-readable ASCII art representation of the tile.

class Tile {
public:

  // Constructor takes in 4 strings, representing what is on the edge
  // of each tile.  Each edge string is "pasture", "road", or "city".
  Tile(const std::string &north, const std::string &east, const std::string &south, const std::string &west);

  // ACCESSORS
  const std::string& getNorth() const { 
    if      (loc.rotation == 0)   return north_;
    else if (loc.rotation == 90)  return west_;
    else if (loc.rotation == 180) return south_;
    else if (loc.rotation == 270) return east_;
  }

  const std::string& getSouth() const { 
    if      (loc.rotation == 0)   return south_;
    else if (loc.rotation == 90)  return east_;
    else if (loc.rotation == 180) return north_;
    else if (loc.rotation == 270) return west_;
  }
  const std::string& getEast() const { 
    if      (loc.rotation == 0)   return east_;
    else if (loc.rotation == 90)  return north_;
    else if (loc.rotation == 180) return west_;
    else if (loc.rotation == 270) return south_;
  }
  const std::string& getWest() const { 
    if      (loc.rotation == 0)   return west_;
    else if (loc.rotation == 90)  return south_;
    else if (loc.rotation == 180) return east_;
    else if (loc.rotation == 270) return north_;
  }
  
  int numCities() const { return num_cities; }
  int numRoads() const { return num_roads; }
  int hasAbbey() const { return (num_cities == 0 && num_roads <= 1); }

  // for ASCII art printing
  void printRow(std::ostream &ostr, int i) const;

  Location loc;

private:

  // helper function called by the constructor for printing
  void prepare_ascii_art();

  // REPRESENTATION
  std::string north_;
  std::string east_;
  std::string south_;
  std::string west_;
  int num_roads;
  int num_cities;
  std::vector<std::string> ascii_art;
};


#endif
