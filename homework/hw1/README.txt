HOMEWORK 1: MOIRE STRINGS


NAME:  Tyler Leite


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

www.cplusplus.com/reference/

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  1h 50m



EXTRA CREDIT SHAPES:.


Random
---------
Creates a shape with variable width, changing by at most 1 (either 1 bigger,
one smaller, or the same) each line. The shape is centered with respect to
a square with the same height as the shape.

./main abcde 10 random out.txt:

attempt 1:
  ******* 
  *abcde* 
 *abcdea* 
 *bcdeab* 
  *cdeab* 
  *cdea*  
  *bcdea* 
 *bcdeab* 
  *cdeab* 
 ******** 

attempt 2:
   *****  
   *abc*  
   *dea*  
   *bc*   
   *de*   
   *abc*  
  *deab*  
  *cdeab* 
 *cdeabc* 
 *********

Hourglass
---------
Creates a rounded (i.e. the outline is chromosome-shaped) hourglass filled
with the text. Some heights work better than others (e.g. 10 looks great, 7
needs to apply itself if it wants to see significant improvement), but the 
general shape is retained for all but exceptionally small heights (1-3).

./main \.\|\|_ 10 hourglass out.txt:
 ************
 *.||_.||_.|*
 *|_.||_.||_*
  *.||_.||_*
   *.||_.|*
      **
   *|_.||_*
  *.||_.||_*
 *.||_.||_.|*
 ************

./main \.\|\|_ 7 hourglass out.txt:
 ********
 *.||_.|*
 *|_.||*
    **
 *_.||_*
 *.||_.|*
 ********

