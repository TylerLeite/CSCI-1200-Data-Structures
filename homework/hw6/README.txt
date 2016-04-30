HOMEWORK 6: CARCASSONNE RECURSION


Tyler Leite



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

n/a

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  ~10hrs



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (h and w)? 
The number of tiles (t)? 
The number of road (r) and city (c) edges? 
The number of duplicate tiles?
Whether rotations are allowed?  
Etc. 

For no rotations, running time is (t+2)*2^t. If rotations are allowed, the 
running time is quadrupled. Right now, the tiles that make up each solution are
stored independently in memory. To increase memory performance, I could have a 
single reference vector of tiles and make the solutions in terms of position in 
that vector to save memory. I made locations a member of Tile so that fewer
different tiles would have to be made. Number of road and city edges, number of
duplicate tiles, and board width/height do not affect performance in any
significant way since the solutions are made with positions relative to each
other rather than on a board. Only when the solution is finished is it fit into
a board.


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles with various command line arguments.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


