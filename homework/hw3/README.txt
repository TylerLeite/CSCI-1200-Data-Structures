HOMEWORK 3: JAGGED ARRAY


NAME:  Tyler Leite

COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.



Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  4hrs



ORDER NOTATION:
For each function, for each version (packed vs. unpacked).  
b = the number of bins
e = the total number of elements
k = the most elements in a bin

numElements
 unpacked: 1
 packed: 1

numBins
 unpacked: 1
 packed: 1

numElementsInBin
 unpacked: b
 packed: b

getElement
 unpacked: b+k
 packed: e

isPacked
 unpacked: 1
 packed: 1

clear
 unpacked: b*k
 packed: b+e

addElement
 unpacked: k
 packed: 1

removeElement
 unpacked: k
 packed: 1

pack
 unpacked: b*k
 packed: 1

unpack
 unpacked: 1
 packed: b*k

print 
 unpacked: b*k
 packed: b+e

constructor w/ integer argument
 unpacked: b
 packed: n/a

copy constructor
 unpacked:b*k
 packed: b+e

destructor
 unpacked:b*k
 packed: b+e

assignment operator
 unpacked: b*k
 packed: b+e




MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


