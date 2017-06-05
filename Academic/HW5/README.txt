HOMEWORK 5: DSRADIO SONG GROUPS


NAME:  < Clarisse Baes >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< TA Lindsey, Milena Gonzalez, Kelly Patel >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 45ish >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of s = the number of songs in the library,
g = the number of song groups, a = the average number of songs by the same 
artist, and l = the average length of song groups.

AddSongToLibrary O(s*s)

GroupExists O(g)

AddToGroup O(l(l*l*l))

MakeGroup O(g)

PrintGroupRewind O(y)

PrintLongestGroupRewind O(g*l(y)*y)

RemoveGroup O(g*(g(l(l))))

DeleteAllSongGroups O(g(g(g(l(l)))))

RemoveFromGroup O(g(l(l))

PrintGroupMarathon O(a)



TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

I used GDB for segmentation faults and Dr. Memory for memory leaks.
I also used cout statements and created test cases based off the test cases given


MISC. COMMENTS TO GRADER:  
This was the absolute worst. I got about 2 hours of sleep a night. Thank you for destroying everything
good in this world. 0/10 would not recommend to a friend. Please have mercy on grading this. I tried 
really hard. 

