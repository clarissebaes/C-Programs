HOMEWORK 8: B+ TREES

In this assignment I implemented a partial and modified version of B+ trees.

TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your implementation?

I Tested each individual case, by commenting out the rest of the cases.
I also used a lot of cout statments(i.e. for loops that cout all the values
with in a key vector, couts to print out the parent node and its keys) to
confirm I was pushing back and inserting the popper values. I also utilized 
Dr. Memory to find various memory leaks.  Dr. Memory helped figure out what
was wrong with my destructor. At first I wasnt iterating through all of the
children pointers.


