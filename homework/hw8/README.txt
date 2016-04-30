HOMEWORK 8: BIDIRECTIONAL MAPS


NAME:  Tyler Leite


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT: 5hrs



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the library operations and justify
your answer (please be concise!)  You may assume that the tree is
reasonably well balanced for all operations.  (You do not need to
implement re-balancing.)

n = the number of elements

k = maximum number of links stored in a single node 
    (for extra credit non one-to-one associations)


size: 1

insert: log(n), same time as it takes to find where the node needs to be placed
erase: log(n), same as insert
find: log(n), representation is a binary search tree so finding is log(n)
operator[]: log(n), just calls find

key_begin: log(n) time it takes to find the smallest element
key_end: log(n) time it takes to find the largest element

value_begin: log(n), same as key_begin
value_end: log(n), same as key_end

key iterator++/--: n, worst case is if no elements have a left child and you try
                   to increment an iterator at the largest element, usually O(1)
value iterator++/--: n, same as operator++

follow_link: 1, just creates a new iterator
default constructor: 1, nothing needs to be initialized to anything other than NULL

copy constructor: n^2 n to actually copy the nodes, then n^2 to recreate the links
                  since it needs to check every value for every key
                  
destructor: n, has to erase every node

assignment operator: n^2



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


