I build a custom class named Matrix, which will mimic traditional matrices. I represented the data 
inside the Matrix class by using a two-dimensional array.

BASIC MATRIX OPERATIONS:
	multiply by coefficient()-Multiplies every element in the matrix by a coefficient

	swap row()- Takes two arguments of type unsigned int: a source row number and a target row
	number. If both rows are inside the bounds of the matrix, then the function should switch the values in the
	two rows and return true

	transpose()- transposes Matrix

BINARY MATRIX METHODS:
	add()/subtract()- the current Matrix object will always be the “left-hand” matrix. Both functions take in just 
	one argument, a second Matrix which we will refer to as B, and modify(add or subtract) A if the dimensions of A and B
	match. If the dimensions match, the functions should return true, otherwise they should return false.

NON TRADITIONAL MATRIX OPERATIONS:
	get row()/get col()- Both functions take one unsigned int and return a double*. If the requested
	row/column is outside of the matrix bounds, the method should return a pointer set to NULL.

	quarter()- The method takes no arguments and returns a Matrix* containing four Matrix elements in order: an Upper Left (UL)
	quadrant, an Upper Right (UR) quadrant, a Lower Left (LL) quadrant, and finally a Lower Right (LR)
	quadrant.



TESTING & DEBUGGING STRATEGY: 
I slowly implementated the functions in the order of that they were presented in the HW. As I
wrote my functions, I created test cases as I finished writing each function to ensure that 
each function worked. For the test cases, I created matrices and perfomred the functions on them.
I also used Dr. Memory to check for memory leaks. For each identified memory leak, I would comment
out certain blocks of code at a time, to see where exactly the leak was coming from. Then when I 
found out where in the code and what function was called, I'd fix the leak by either deleting pointers
that werent returned, set pointers = NULL, etc.



