#include <cassert>
#include "location.h"


// CONSTRUCTOR
Location::Location (int r, int c, int rot) : row(r), column(c), rotation(rot) { 
  assert (rotation == 0 || 
          rotation == 90 || 
          rotation == 180 || 
          rotation == 270); 

  for (int i = 0; i < 4; i++){
    open_neighbors[i] = true;
  }
}


// Check if these two locations are the same
bool Location::operator==(const Location& loc2) const {
    return row == loc2.row && column == loc2.column;// && rotation == loc2.rotation;
}


// helper function to output the placement of this tile within a solution
std::ostream& operator<<(std::ostream &ostr, const Location &loc) {
  ostr << "(" << loc.row << "," << loc.column << "," << loc.rotation << ")";
  return ostr;
}
