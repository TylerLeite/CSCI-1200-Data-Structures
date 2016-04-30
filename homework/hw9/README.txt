HOMEWORK 9: PERFECT HASHING


NAME:  Tyler Leite


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  3.5 hrs



SUMMARY OF RESULTS: 
Summarize your results on the provided examples.  Were you able to
construct a perfect hash function?  If not, how close did you get (how
many collisions)?  If yes, what was the smallest perfect hash you were
able to construct for the different examples?  What was your
compression ratio?  Did you make any additional test cases?

As far as I can tell, my hash function is lossless, though it produced results
slightly worse than the provided compressed image (in the car, at least). 

Car:
original: 6481 bytes
compressed: 2570 bytes (60.3% reduction)
 -offset: 212 bytes
 -occupancy: 317 bytes
 -hash_data: 2041 bytes
    
Lightbulb:
original: 49167 bytes
compressed: 7615 bytes (84.5% reduction)
 -offset: 500 bytes
 -occupancy: 2059 bytes
 -hash_data: 5056 bytes
 
Chair:
original: 119 bytes (42.0% reduction)
compressed: 69 bytes (
 -offset: 18 bytes
 -occupancy: 13 bytes
 -hash_data: 38 bytes
 
Custom Case 1 (turdle_git.ppm) - about 50% white pixels:
original: 12340 bytes
compressed: 8191 (33.6% reduction)
 -offset: 745
 -occupancy: 521
 -hash_data: 6925
 
Custom Case 2 (brick_wall.ppm) - 0 white pixels:
original: 49167 bytes
compressed: 56109 (14.1% increase)
 -offset: 4112 bytes
 -occupancy: 2059 bytes
 -hash_data: 49938 bytes
 
Custom Case 3 (white.ppm) - 100% white pixels:
original: 49206 bytes
compressed:2084 bytes (95.8% reduction)
 -offset: 14 bytes
 -occupancy: 2059 bytes
 -hash_data: 11 bytes



OFFSET SEARCH FOR EXTRA CREDIT:
If you implemented a search strategy instead of or in addition to the
greedy method from the paper, describe it here.

For each pixel in offset, I keep track of each pixel in the input file that ends
up there and make sure that none of them collide with each other in the hash
image. This way, there are no collisions. Worst case scenario, hash_data is
slightly bigger than the original image, but that is only when most of the image
is not white and the compression will always be lossless.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!






