#ifndef _LOCATION_H_
#define _LOCATION_H_

#include <iostream>


// Tiny all-public class to store the grid coordinates and rotation
// for placing a tile onto the board
class Location {
public:
  Location () : row(0), column(0), rotation(0) {}
  Location (int r, int c, int rot);
  int row;
  int column;
  int rotation; // should be 0, 90, 180, or 270

  bool open_neighbors[4];

    // Check of these two locations are the same
    bool operator==(const Location& loc2) const;
};

// Helper function to output a location as part of a puzzle solution
std::ostream& operator<<(std::ostream &ostr, const Location &loc);


#endif
