#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <cassert>
#include <math.h>
using namespace std;

class Hash{
private: //private variables 
	vector<pair< string, vector <int> > > table;
	int tablesize;
	int numKeys;
	float maxOccupancy;
	int kmerLength;
public: //public variables
	Hash();
	Hash(int tablesize_);
	int convertLetter(char x);
	int HashFunction(string key_);
	void Insert(string key, int startPosition);
	void resize(int newTableSize);
	void setTableSize(int newTableSize);
	void setMaxOccupancy(float newMax);
	void setKmerSize(int kmerSize);
	vector<int> getStartPos(string key);
	int getKmerSize();
};