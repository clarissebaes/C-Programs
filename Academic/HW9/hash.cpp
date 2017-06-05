#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert> 
#include <math.h>
#include "hash.h"
using namespace std;
Hash::Hash(){ //default constructor
	tablesize = 100;
	maxOccupancy = 0.5;
	numKeys =0;
	for(int i=0; i<tablesize; i++){ //creats an empty hash table
		pair <string, vector<int> > tempPair;
		vector<int> tempvect;
		tempPair = make_pair("empty",tempvect);
		table.push_back(tempPair);
	}
}
Hash::Hash(int tablesize_){//constructor
	tablesize = tablesize_;
	numKeys=0;
	maxOccupancy = 0.5;
	for(int i=0; i<tablesize; i++){//creates an empty hash table
		pair <string, vector<int> > tempPair;
		vector<int> tempvect;
		tempPair = make_pair("empty",tempvect);
		table.push_back(tempPair);
	}
}
int Hash::convertLetter(char x){ //converts the letters to ints 0-3
	if(x == 'A'){return 0;}
	if(x == 'C'){return 1;}
	if(x == 'G'){return 2;}
	if(x == 'T'){return 3;}
}
int Hash::HashFunction(string key){// converts the kmer to an int using my hash function
	int kmerLength = key.size();
	int output = 0;
	for(int i=0;i<kmerLength;i++){
		int baseNum = convertLetter(key[i]);//converts the leter to an int
		int power = pow(4,i);//takes 4 and raises it to whatever index its at power
		output += (baseNum*power);//multiplies the base number by 4^(index)
	}
	return output; //out pout number is the DNA Kmer in base 4
}
void Hash::Insert(string key, int startPosition){ //inserts the kmers into the  has table
	if ( numKeys>= (maxOccupancy*tablesize)){ 
	//if the number of kmers in the table passes occupancy -> calls resize func
		resize(2*tablesize+1); //doubles the table
	}
	int hashvalue = HashFunction(key); //gets hash value
	int index = hashvalue%tablesize;//divides by table size
	if(table[index].first == "empty" || table[index].first == key){ //checks if hased index is empty or the same kmer
		table[index].first = key; //sets first to the key
		table[index].second.push_back(startPosition); //pushes back the starting location
		numKeys++;
	}
	else{
		while(table[index].first != "empty"){ //iterates through table till you find an empty sopot
			index++;
			if(index>=tablesize){
				index=0;
			}
		}
		if(table[index].first == "empty"){
			table[index].first = key;
			table[index].second.push_back(startPosition);
			numKeys++;
		}
	}
}
void Hash::resize(int newTableSize){//resizes the table
	vector<pair< string, vector<int> > > newTable;
	for(int i=0; i<newTableSize; i++){ //makes a new empty table
		pair <string, vector<int> > tempPair;
		vector<int> tempvect;
		tempPair = make_pair("empty",tempvect);
		newTable.push_back(tempPair);
	}
	for(int i=0; i<tablesize;i++){//runs through old table and rehashes the dat
		if(table[i].first != "empty"){ //if there is a key it rehashes the info stored
			string tempKey = table[i].first;
			vector<int> tempPos = table[i].second;
			int hashVal = HashFunction(tempKey);//runs key through hash function
			int newIndex = hashVal%newTableSize; //gets new index 
			newTable[newIndex].first = tempKey; //reassigns the information
			newTable[newIndex].second = tempPos;
		}
	}
	tablesize = newTableSize; //sets new table size
	table= newTable; // sets new table
}
vector<int> Hash::getStartPos(string key){ //returns a vecotr of all opissible starting posiitons
	vector<int> outputVect;
	int hashVal = HashFunction(key);
	int index = hashVal%tablesize; //hashes the input
	for(int j = index;j<tablesize;j++){ //runs through table fro mthat hash index
		if(table[j].first == key){ //if key matches 
			outputVect=(table[j].second); //gets the output 
			break;
		}
	} 
	return outputVect;
}
void Hash::setTableSize(int newTableSize){//sets table size
	tablesize=newTableSize;
	resize(newTableSize);
}
void Hash::setMaxOccupancy(float newMax){//sets max occupancy 
	maxOccupancy=newMax;
}
void Hash::setKmerSize(int kmerSize){//sets kmer size
	kmerLength = kmerSize;
}
int Hash::getKmerSize(){//sets kmer length
	return kmerLength;
}