#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include "grid.H"
using namespace std;

//makes gird
vector<vector<char> > makegrid(int row, int col){
	vector<vector<char> > board;
	for(int i = 0; i<row;i++){
		vector<char> tempvect;
		for(int j=0; j<col;j++){
			tempvect.push_back('.');
		}
		board.push_back(tempvect);
	}
	return board;
}
//prints grid
void printgrid(const vector<vector<char> > &board){
	for(int i=0; i<board.size();i++){
		for(int j =0; j<board[0].size();j++){
			cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}
}
//sorting by lenght
bool compareLen(const string& a, const string& b)
{
    return (a.size() < b.size()); 
}
//main code
int main(int argc, char* argv[]){
	int row = 0;
	int col = 0;
	vector<string> inWords;
	vector<string> outWords;
	ifstream puzzleFile;
	ofstream out_File(argv[2]);
	string num_sols(argv[3]);

	puzzleFile.open(argv[1]);
	puzzleFile>>col;
	puzzleFile>>row;
	vector<vector<char> > board = makegrid(row,col);
	vector<string> drctVect; //makes direction
	drctVect.push_back("up");
	drctVect.push_back("down");
	drctVect.push_back("left");
	drctVect.push_back("right");
	drctVect.push_back("up_left");
	drctVect.push_back("up_right");
	drctVect.push_back("down_left");
	drctVect.push_back("down_right");

	while(puzzleFile){
		string sign;
		string word;
		puzzleFile>>sign;
		if(sign=="+"){
			puzzleFile>>word;
			inWords.push_back(word);
		}    
		if(sign=="-"){
			puzzleFile>>word;
			outWords.push_back(word);
		}
	}

	vector<vector<vector<char> > > finalsols;
 	vector<Grid> gridobjects;
	vector<vector<string> > allcombos; //vector of all permutations of the input words
	sort(inWords.begin(), inWords.end());
	do { //makes a vector of objects of using all the permutations
	    allcombos.push_back(inWords);
	} while (next_permutation(inWords.begin(), inWords.end()));
	//makes a vector objects
	for(int i=0; i<allcombos.size();i++){
		gridobjects.push_back(Grid(board,allcombos[i],outWords,drctVect));
	}
	string direction= "mee";
	int wordcount =0;
	for(int g =0; g<gridobjects.size();g++){
		for(int i=0; i<board.size();i++){
			for(int j =0; j<board[0].size();j++){//runs through all grid loctions and adds all words
				wordcount =0;
				board = makegrid(row,col);
				loc start(i,j);
				gridobjects[g].AddAllWords(wordcount,start,direction);
			}
		}
		gridobjects[g].FillGrids(); // fills the blank locations
		vector<vector<vector<char> > > solz =gridobjects[g].returnsols();
		for(int i =0; i<solz.size();i++){
			finalsols.push_back(solz[i]); //adds the grid to the final solution
		}
	}

	if( num_sols == "all_solutions"){ //prints all solutions
		sort(finalsols.begin(), finalsols.end() );
		finalsols.erase(unique(finalsols.begin(), finalsols.end() ), finalsols.end() );
		out_File<<finalsols.size()<<" solution(s)"<<endl;
		for(int g = 0; g<finalsols.size();g++){
			out_File<<"Board: "<<endl;
			for(int i=0; i<row;i++){
				out_File<<"  ";
				for(int j =0; j<col;j++){
					out_File<<finalsols[g][i][j];
				}
				out_File<<endl;
			}
		}
	}
if( num_sols == "one_solution"){ //prints one solutions
		sort(finalsols.begin(), finalsols.end() );
		finalsols.erase(unique(finalsols.begin(), finalsols.end() ), finalsols.end() );
		out_File<<"Board: "<<endl;
		for(int i=0; i<row;i++){
			out_File<<"  ";
			for(int j =0; j<col;j++){
				out_File<<finalsols[0][i][j];
			}
			out_File<<endl;
		}
	}

}