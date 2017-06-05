#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

class loc {
public:
  loc(int r=0, int c=0) : row(r), col(c) {}
  void incrament(int maxrow, int maxcol){
  	if(col<maxcol){
		col+=1;
	}
	if(col>=maxcol){
		row+=1;
		col=0;
	}
  }
  int row, col;
};

class Grid{

	public:
		Grid(); //defalut constructor
		Grid(vector<vector<char> > &board_, vector<string> inwordlist_,  vector<string> outwordlist_, vector<string> drctVect_);//constructor
		bool search_from_loc(loc position, const string& word, vector<loc>& path,string &direction,vector<vector<char> > &board_);
		bool CanInsert(const string word, loc start, string direction); //Checks if the given word can be inserted at the start position facing direction d
		bool check(vector<vector<char> > &board_);
		void InsertWord(const string word, loc &start,string &direction,int &wordcount); //Place word at a random, valid location facing a random direction
		void ClearGrid(); //Sets the grid to be all null values
		void addLetters(vector<vector<char> > &blanks_); //adds letters to blanks
		bool HasBlanks(vector<vector<char> > &tempboard); //checks for blanks
		void FillGrids(); //Fills null values with random characters
		void PrintGrids(ostream& stream); //Prints all grids
		void PrintSingleGrid(ostream& stream); //prints single grid
		loc MovePoint(loc start, string direction); //Returns the shifted point
		void AddAllWords(int &wordcount, loc &start,string direction); //recursively adds all words
		int numofsols(); //returns num of solutions
		vector<vector<vector<char> > > returnblanks(); //return blank solution grids
		vector<vector<vector<char> > > returnsols(); //returns all solutions
		

	private:
		vector<vector<char> > board;
		vector<vector<vector<char> > >solutions;
		vector<vector<vector<char> > >blanks;
		vector<string> inwordlist;
		vector<string> outwordlist;
		vector<string> drctVect;
		string abc;

		int row;
		int col;

};


