HOMEWORK 9: MINIBLAST

This program is an extremely simplified version of BLAST. My version works in a manner somewhat similar to BLAST. 
BLAST is used to regularly search Genbank, a repository of sequence data containing over 1 trillion bases (letters) 
of sequence data. My version of BLAST, MiniBLAST, will search small genome files with query strings in a DNA 
alphabet (A,C,G,T).


My program accepts the following commands:
	• genome filename - Read a genome sequence from filename. The genome file consists of lines DNA
	characters.
	• table size N - this is an optional command. N is an integer. It is the initial hash table size. If it does
	not appear in the command file, the initial table size should be set to 100.
	• occupancy f - this is an optional command. f is a float. When the occupancy goes above this level, the 2
	table should be resized. If it does not appear in the command file, the initial level should be set to 0.5.
	• kmer k - k is an integer. The genome should be indexed with kmers of length k.
	• query m query string - Search the genome for a match to query string allowing for m mismatches.
	• quit - Exit the program.



HASH FUNCTION DESCRIPTION

My Hash function takes the DNA sequence and converts it to a 
number in base 4. First I convert the letter to an int (0-3)
and then I take the index that the letter is at and then raise 4 
to that power (ie. 4^(index)). Then I take the converted letter number
multiply it by the 4 raised to its index. 

HASH TABLE IMPLEMENTATION

My Hash table is a vector of pairs. The pairs consist of a string(kmer)
and a vector of ints (vector of starting positions). I have a default constructor
and constructor that creates a table of the requested size and has each index
have a string that says "empty" and an empty int vector. Then when I input the genome
and kmer size, I run through the entire genome, and hash each kmer and insert it, at 
the index that results from my hash function/table size.










