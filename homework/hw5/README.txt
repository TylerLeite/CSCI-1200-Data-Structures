HOMEWORK 5: UNROLLED LINKED LISTS


NAME: Tyler Leite


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.



Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  7hrs



TESTING & DEBUGGING STRATEGY:
Step with gdb and see where the program was messing up (usually it was the iterators not properly dealing with nodes being deleted)


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

push_front / push_back / insert: NUM_ELEMENTS_PER_NODE + NUM_NODES
pop_back / pop_front / erase: NUM_ELEMENTS_PER_NODE + NUM_NODES

STL list is faster unless you are adding an element to a node that isn't full or removing the last (i.e. right-most) element from a node and don't have to delete it afterward

deepCopy / operator= / copy constructor: NUM_NODES*ELEMENTS_PER_NODE
this is less efficient than the STL list



EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
EDIT: the problem was in pop_back

