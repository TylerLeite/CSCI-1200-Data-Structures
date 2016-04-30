#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include "tile.h"


// Fill in characters for the ASCII art 
#define ROAD_CHAR '#'
#define CITY_CHAR '.'


// ==========================================================================
// this global variable is set in main.cpp and is adjustable from the command line
// (you are not allowed to make your own global variables)
extern int GLOBAL_TILE_SIZE;


// ==========================================================================
// CONSTRUCTOR
// takes in 4 strings, checks the legality of the labeling 
Tile::Tile(const std::string &north, const std::string &east,
           const std::string &south, const std::string &west) :
  north_(north), east_(east), south_(south), west_(west), loc(0,0,0) {

  // check the input strings
  assert (north_ == "city" || north_ == "road" || north_ == "pasture");
  assert (east_  == "city" || east_  == "road" || east_  == "pasture");
  assert (south_ == "city" || south_ == "road" || south_ == "pasture");
  assert (west_  == "city" || west_  == "road" || west_  == "pasture");

  // count the number of cities and roads
  num_cities = 0;
  if (north_ == "city") num_cities++;
  if (south_ == "city") num_cities++;
  if (east_ == "city") num_cities++;
  if (west_ == "city") num_cities++;
  num_roads = 0;
  if (north_ == "road") num_roads++;
  if (south_ == "road") num_roads++;
  if (east_ == "road") num_roads++;
  if (west_ == "road") num_roads++;
  
  // For our version of Carcasonne, we put these restrictions on the
  // tile edge labeling:
  if (num_roads == 1) {
    assert (num_cities == 0 || num_cities == 3);
  }
  if (num_roads == 2 && num_cities == 2) {
    assert (north_ == east_ || north_ == west_);
  }

  // pre-compute the ASCII art center of the tile
  prepare_ascii_art();
}


// ==========================================================================
// print one row of the tile at a time 
// (allows a whole board of tiles to be printed)
void Tile::printRow(std::ostream &ostr, int row) const {
  // must be a legal row for this tile size
  assert (row >= 0 && row < GLOBAL_TILE_SIZE);

  if (row == 0 || row == GLOBAL_TILE_SIZE-1) {
    ostr << '+' << std::string(GLOBAL_TILE_SIZE-2,'-') << '+';
  } else {
    ostr << '|' << ascii_art[row-1] << '|';
  }
}


// ==========================================================================
// long, messy, uninteresting function that
// prepares the inner block of ASCII art for the tile
void Tile::prepare_ascii_art() {

  // tiles have to be odd sized
  assert (GLOBAL_TILE_SIZE % 2 == 1);
  // tiles must be big enough to the ascii art is visible
  assert (GLOBAL_TILE_SIZE >= 11);

  // helper variables
  int inner_size = GLOBAL_TILE_SIZE-2;
  int half = inner_size/2;
  int city_depth = (half+2) / 2;
  assert (city_depth >= 3);
  int road_curve = city_depth-1;
  ascii_art = std::vector<std::string>(inner_size,std::string(inner_size,' '));

  // -------------------------------------------------------------------
  // ROADS

  // Does a road go straight vertically or horizontally through the tile?
  bool center_road = false;
  if ((getNorth()/**/ == "road" && getSouth()/**/ == "road") ||
       (getEast()/**/ == "road" && getWest()/**/ == "road")) {
    center_road = true;
    ascii_art[half][half] = ROAD_CHAR;
  }

  // Construct the road fragments from edge towards the center of the tile
  if (getNorth()/**/ == "road") {
    for (int i = 0; i < half-1; i++) {
      ascii_art[i][half] = ROAD_CHAR;
    }
    if (center_road) {
      ascii_art[half-1][half] = ROAD_CHAR;
    }
  }
  if (getSouth()/**/ == "road") {
    for (int i = half+2; i < inner_size; i++) {
      ascii_art[i][half] = ROAD_CHAR;
    }
    if (center_road) {
        ascii_art[half+1][half] = ROAD_CHAR;
    }
  }
  if (getWest()/**/ == "road") {
    for (int i = 0; i < half-1; i++) {
      ascii_art[half][i] = ROAD_CHAR;
    }
    if (center_road) {
      ascii_art[half][half-1] = ROAD_CHAR;
    }
  }
  if (getEast()/**/ == "road") {
    for (int i = half+2; i < inner_size; i++) {
      ascii_art[half][i] = ROAD_CHAR;
    }
    if (center_road) {
      ascii_art[half][half+1] = ROAD_CHAR;
    }
  }

  // Construct the curved pieces of "corner" roads
  if (!center_road) {
    if (getNorth()/**/ == "road" && getEast()/**/ == "road") {
      for (int c = 1; c < road_curve; c++) {
        ascii_art[half-c][half+road_curve-c] = ROAD_CHAR;
        ascii_art[half-c][half+road_curve-c] = ROAD_CHAR;
        ascii_art[half-c][half] = ' ';
        ascii_art[half][half+road_curve-c] = ' ';
      }
    }
    if (getEast()/**/ == "road" && getSouth()/**/ == "road") {
      for (int c = 1; c < road_curve; c++) {
        ascii_art[half+c][half+road_curve-c] = ROAD_CHAR;
        ascii_art[half+c][half+road_curve-c] = ROAD_CHAR;
        ascii_art[half+c][half] = ' ';
        ascii_art[half][half+road_curve-c] = ' ';
      }
    }
    if (getSouth()/**/ == "road" && getWest()/**/ == "road") {
      for (int c = 1; c < road_curve; c++) {
        ascii_art[half+c][half-road_curve+c] = ROAD_CHAR;
        ascii_art[half+c][half-road_curve+c] = ROAD_CHAR;
        ascii_art[half+c][half] = ' ';
        ascii_art[half][half-road_curve+c] = ' ';
      }
    }
    if (getWest()/**/ == "road" && getNorth()/**/ == "road") {
      for (int c = 1; c < road_curve; c++) {
        ascii_art[half-c][half-road_curve+c] = ROAD_CHAR;
        ascii_art[half-c][half-road_curve+c] = ROAD_CHAR;
        ascii_art[half-c][half] = ' ';
        ascii_art[half][half-road_curve+c] = ' ';
      }
    }
  }


  // -------------------------------------------------------------------
  // CITIES
  // construct the curved wedges of cities for each edge
  if (getNorth()/**/ == "city") {
    int depth = city_depth;
    if (getEast()/**/ == "city" || getWest()/**/ == "city") {
      depth = half;
    }
    for (int i = 0; i < depth; i++) {
      for (int j = i+1; j < inner_size-i-1; j++) {
        ascii_art[i][j] = CITY_CHAR;
      }
    }
  }
  if (getSouth()/**/ == "city") {
    int depth = city_depth;
    if (getEast()/**/ == "city" || getWest()/**/ == "city") {
      depth = half;
    }
    for (int i = 0; i < depth; i++) {
      for (int j = i+1; j < inner_size-i-1; j++) {
        ascii_art[GLOBAL_TILE_SIZE-3-i][j] = CITY_CHAR;
      }
    }
  }
  if (getWest()/**/ == "city") {
    int depth = city_depth;
    if (getNorth()/**/ == "city" || getSouth()/**/ == "city") {
      depth = half;
    }
    for (int i = 0; i < depth; i++) {
      for (int j = i+1; j < inner_size-i-1; j++) {
        ascii_art[j][i] = CITY_CHAR;
      }
    }
  }
  if (getEast()/**/ == "city") {
    int depth = city_depth;
    if (getNorth()/**/ == "city" || getSouth()/**/ == "city") {
      depth = half;
    }
    for (int i = 0; i < depth; i++) {
      for (int j = i+1; j < inner_size-i-1; j++) {
        ascii_art[j][GLOBAL_TILE_SIZE-3-i] = CITY_CHAR;
      }
    }
  }

  // If there are at least 3 wedges of city, fill in the middle as city
  if (num_cities >= 3) {
    for (int i = city_depth; i < inner_size-city_depth; i++) {
      for (int j = city_depth; j < inner_size-city_depth; j++) {
        ascii_art[i][j] = CITY_CHAR;
      }
    }
  } 

  // If there are 2 neighboring wedges of city, fill in the gap
  if (getNorth()/**/ == "city" && getWest()/**/ == "city") {
    for (int i = 0; i < half; i++) {
      ascii_art[i][i] = CITY_CHAR;
    }
  }
  if (getNorth()/**/ == "city" && getEast()/**/ == "city") {
    for (int i = 0; i < half; i++) {
      ascii_art[i][GLOBAL_TILE_SIZE-3-i] = CITY_CHAR;
    }
  }
  if (getSouth()/**/ == "city" && getWest()/**/ == "city") {
    for (int i = 0; i < half; i++) {
      ascii_art[GLOBAL_TILE_SIZE-3-i][i] = CITY_CHAR;
    }
  }
  if (getSouth()/**/ == "city" && getEast()/**/ == "city") {
    for (int i = 0; i < half; i++) {
      ascii_art[GLOBAL_TILE_SIZE-3-i][GLOBAL_TILE_SIZE-3-i] = CITY_CHAR;
    }
  }
  
  // -------------------------------------------------------------------
  // DRAW THE ABBEY BUILDING
  if (hasAbbey()) {
    ascii_art[half-2][half] = '^';
    ascii_art[half-1][half-1] = '/';
    ascii_art[half-1][half  ] = ' ';
    ascii_art[half-1][half+1] = '\\';
    ascii_art[half  ][half-2] = '/';
    ascii_art[half  ][half-1] = '|';
    ascii_art[half  ][half  ] = ' ';
    ascii_art[half  ][half+1] = '|';
    ascii_art[half  ][half+2] = '\\';
    ascii_art[half+1][half-1] = '|';
    ascii_art[half+1][half  ] = ' ';
    ascii_art[half+1][half+1] = '|';
    ascii_art[half+2][half-1] = '+';
    ascii_art[half+2][half  ] = '-';
    ascii_art[half+2][half+1] = '+';
  }
}

// ==========================================================================

