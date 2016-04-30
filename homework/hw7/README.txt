HOMEWORK 7: LIBRARY MAPS


NAME:  Tyler Leite

COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in the “Collaboration Policy & Academic Integrity”
handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  ~2hrs



ORDER NOTATION ANALYSIS: 
Give the big O notation of each of the library operations and justify
your answer.  Let n be the number of different titles in the library,
m be the maximum number of copies of a given item, p be the number of
patrons using the library, and c be the maximum number of items any
patron has checked out at one time.  (Please be concise!)


add (a): m


checkout (c): m*log(n) + log(p)


return (r): n*m*log(n) + log(p)


lookup (l): m*log(n) + m


print (p): p*m*log(p)



YOUR OWN TEST CASES:
describe each test case you created and your motivation for designing
each (why is the test case helpful for debugging and/or interesting)

The test cases I devised were mostly designed to make sure that ordinary use of
the program would work (e.g. making sure that a person can check out a book they
checked out once before but have returned). Additionally, the test cases were
meant to weed out input that would cause errors like having a negative amount of
an item in stock or someone having multiple copies of the same book. The third
motivation behind the test cases is to make sure that the program can deal with
nothingness such as no people with books checked out or no books left of a
certain title or even just no books in general.

addItems tests: 
add 0 of an item
add a negative number of books

checkoutItem tests:
person checked out book already
person checked out book before, but has returned it since then
title doesn't exist
title no longer available
title wasn't available, but has been returned since then

returnItems tests:
person has no items
person does not exist

lookup tests:
book doesn't exist

printpeople tests:
no people



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


