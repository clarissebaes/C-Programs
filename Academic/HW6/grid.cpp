#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <typeinfo>
#include <algorithm>
#include "grid.H"
using namespace std;
//default constructor
Grid::Grid(){
	row=0;
	col=0;
}
//constructor
Grid::Grid(vector<vector<char> > &board_, vector<string> inwordlist_,  vector<string> outwordlist_, vector<string> drctVect_){
	inwordlist = inwordlist_;
	outwordlist = outwordlist_;
	drctVect = drctVect_;//vector of directions
	board = board_;
	row = board.size();
	col = board[0].size();
	abc = "abcdefghijklmnopqrstuvwxyz";
}
//used the search from loc code from the lecture notes. Modified it so we could find the bad words linearly based on the direction
bool Grid::search_from_loc(loc position, const string& word, vector<loc>& path,string &direction,vector<vector<char> > &board_){
	int curr_row = position.row;
	int curr_col = position.col;
	if( curr_row < 0 || curr_col < 0 || //if the point goes out of bound return false and stop recursion
			curr_row >=row|| curr_col >= col){
		return false;
	}
	if(board_[position.row][position.col] != word[path.size()-1]){//if the letters on the board dont match the word return false
		return false;
	}
	if(path.size() == word.size()){//if the lenghts are the same return true
		for(int j =0;j<word.size();j++){
			if(board_[path[j].row][path[j].col] != word[j]){
				return false; //just making sure the letters match up
			}
		}

		return true;
	}
	loc new_pos;
	//Decide where to recurse next based on direction and shifts point accordingly
		if (direction == "up"){
		new_pos.row = position.row-1;
		new_pos.col = position.col;
		path.push_back(new_pos);
		if(search_from_loc(new_pos,word,path,direction,board_)){  //If recursive call finds a solution
			return true;
		}
		else{ //Otherwise
			path.pop_back();
		}
	}
	if (direction == "down"){
		new_pos.row = position.row +1;
		new_pos.col = position.col;
		path.push_back(new_pos);
		if(search_from_loc(new_pos,word,path,direction,board_)){  
			return true;
		}
		else{ 
			path.pop_back();
		}
	}
	if (direction == "left"){
		new_pos.row = position.row;
		new_pos.col = position.col-1;
		path.push_back(new_pos);
		if(search_from_loc(new_pos,word,path,direction,board_)){  
			return true;
		}
		else{ 
			path.pop_back();
		}
	}
	if (direction == "right"){
		new_pos.row = position.row;
		new_pos.col = position.col+1;
		path.push_back(new_pos);
		if(search_from_loc(new_pos,word,path,direction,board_)){  
			return true;
		}
		else{ 
			path.pop_back();
		}
	}
	if (direction == "up_left"){
		new_pos.row = position.row-1;
		new_pos.col = position.col-1;
		path.push_back(new_pos);
		if(search_from_loc(new_pos,word,path,direction,board_)){  
			return true;
		}
		else{ 
			path.pop_back();
		}
	}
	if (direction == "up_right"){
		new_pos.row = position.row-1;
		new_pos.col = position.col+1;
		path.push_back(new_pos);
		if(search_from_loc(new_pos,word,path,direction,board_)){  
			return true;
		}
		else{ 
			path.pop_back();
		}
	}
	if (direction == "down_left"){
		new_pos.row = position.row+1;
		new_pos.col = position.col-1;
		path.push_back(new_pos);
		if(search_from_loc(new_pos,word,path,direction,board_)){  
			return true;
		}
		else{ 
			path.pop_back();
		}
	}
	if (direction == "down_right"){
		new_pos.row = position.row+1;
		new_pos.col = position.col+1;
		path.push_back(new_pos);
		if(search_from_loc(new_pos,word,path,direction,board_)){  
			return true;
		}
		else{ 
			path.pop_back();
		}
	}

	return path.size() == word.size();
}
//If you can insert the word it returns true
bool Grid::CanInsert(const string word, loc start, string direction){
	int i=0;
	loc NewPoint = start; 
	while(i<word.size()){//while loop for the length of the word
		int old_row = NewPoint.row;
		int old_col = NewPoint.col;

		if(((NewPoint.row < row && NewPoint.col<col)&&(board[NewPoint.row][NewPoint.col] == '.')) || (board[NewPoint.row][NewPoint.col] == word[i])){
			//checks if theres a free spot or if the letters match
			NewPoint = MovePoint(NewPoint,direction);//shifts point in the direction
			i++;//moves on to the next letter
		}
		else{
			return false;
		}
		if(NewPoint.row == old_row && NewPoint.col == old_col ){
			if(i==word.size()){
				return true;
			}
			return false;
		}
	}
	if(i<word.size()){//if you exit the while loop too early
		return false;
	}
	return true;


}
bool Grid::check(vector<vector<char> > &board_){//checks for (-) words
	vector<loc> path;
	bool found = false;
	for(int i = 0; i<outwordlist.size();i++){ //iterates through list of words not to be included
		string noword = outwordlist[i];
		for(int d =0; d<drctVect.size();d++){//iterates through all the directions
	   		for (int r=0; r<row && !found; ++r){
	   			for(int c=0; c<col && !found; ++c){//iterates to each spot in the grid
					if (board[r][c] == noword[0]){//if the letter matches the first letter of the word
						loc position(r,c);
						path.push_back(position);
		            	if(search_from_loc(position, noword, path,drctVect[d],board_)){
				 			return true;
						}
						else{
							path.pop_back();
						}		
					} 
				}
			}
	    }
	}
	return false;
}
void Grid::InsertWord(const string word, loc &start,string &direction,int &wordcount){
	//recursive function that actually inserts the indivdual word
	loc NewPoint = start;
	if(CanInsert(word,start,direction)){ //checks if you can insert the word
		int i=0;
		while(i< word.size()){
			board[NewPoint.row][NewPoint.col] = word[i]; //inserts each letter
			NewPoint = MovePoint(NewPoint,direction); //shifts point
			i++;
		}
		//after you insert the word, checks if you made any (-) words if so end the recursion and returns
		bool found = check(board);
		if(found){
			ClearGrid();
			direction = "END"; //base case for my later recursion
			return;

			}
		start.row=0;
		start.col=0;
		wordcount++; //incraments to next word to be inserted
		if(wordcount >= inwordlist.size()){ //checks if you inserted all the words
			addLetters(board); //adds letters to the blanks
			bool found = check(board); //checks for bad words			
			if(!found){ //if no bad words found then you push backthe completed board to the solutions vector
				solutions.push_back(board);
			}
			ClearGrid();
			direction = "END";
		}
		return;
	}
	NewPoint.incrament(row,col); //checks next grid spot to try and insert the word
	if(NewPoint.row < 0 || NewPoint.row >= row || NewPoint.col < 0 || NewPoint.col >= col){
		direction ="END";
		return;
	}
	else{InsertWord(word, NewPoint,direction,wordcount);} //calls insert word recursivly
	return;

}
// clears grid
void Grid::ClearGrid(){
	for(int i = 0; i<row;i++){
		for(int j=0; j<col;j++){
			board[i][j]='.';
		}
	}
}
// recursivley adds legal letters to blank spaces
 void Grid::addLetters(vector<vector<char> > &blanks_){
 	vector<vector<char> > tempboard = blanks_;
 	if(!HasBlanks(blanks_)){
		bool found = check(blanks_);			
			if(!found){
				solutions.push_back(blanks_);
			}
		return;
	}

 	for(int i=0;i<26;i++){ //iterates through the alphabet
 		bool fixed = false;
 		bool found=false;
			for(int j=0;j<outwordlist.size();j++){ //checks the (-) word list if any letters are excluded
				if(outwordlist[j].size()==1){
					if(outwordlist[j][0]==abc[i]){
						found =true; //if letters are excluded it skips over that letter to be inserted
						break;
					}
				}
			}
			if(found==true){continue;}
		 	for(int j=0;j<row;j++){
				for(int k = 0; k<col;k++){
					if(blanks_[j][k]=='.'){ //inserts the letter
						blanks_[j][k]=abc[i];
						addLetters(blanks_);
						blanks_=tempboard; 
					}
				}
			} 	
	 }
 }
 //checks if a grid has blank spaces returns true if it does
 bool Grid::HasBlanks(vector<vector<char> > &tempboard){
 	bool blanks= false;
 	for(int j=0;j<row;j++){
		for(int k = 0; k<col;k++){
			if(tempboard[j][k]=='.'){ //'.' means its blank
				blanks = true;
				break;
			}
		}
		if(blanks==true){break;}
	}
	return blanks;

 }

void Grid::FillGrids(){//movves the solutions with blanks to a separte vector to deal with it
	for(int i=0; i<solutions.size();i++){
		vector<vector<char> > tempboard;
		if(HasBlanks(solutions[i])){
			blanks.push_back(solutions[i]);
			solutions.erase(solutions.begin()+i);
		}

	}
}
//prints all of my grids
void Grid::PrintGrids(ostream& stream){
	sort(solutions.begin(), solutions.end() );
	solutions.erase(unique(solutions.begin(), solutions.end() ), solutions.end() );
	stream<<numofsols()<<" solution(s)";
	for(int g = 0; g<solutions.size();g++){
		stream<<"Board: "<<endl;
		for(int i=0; i<row;i++){
			stream<<"  ";
			for(int j =0; j<col;j++){
				stream<<solutions[g][i][j];
			}
			stream<<endl;
		}
	}
}
//prints one of my grids
void Grid::PrintSingleGrid(ostream& stream){
	stream<<"Board:"<<endl;
	for(int i=0; i<row;i++){
		stream<<"  ";
		for(int j =0; j<col;j++){
			stream<<solutions[0][i][j];
		}
		stream<<endl;
	}
}
//shifts point based on direction 
loc Grid::MovePoint(loc start, string direction){
	int row_ = start.row;
	int col_ = start.col;
	loc NewPoint;
	if(direction == "up"){
		NewPoint.row = row_-1;
		NewPoint.col = col_;
	}
	else if(direction =="down"){
		NewPoint.row = row_+1;
		NewPoint.col = col_;
	}
	else if(direction =="left"){
		NewPoint.row = row_;
		NewPoint.col = col_-1;
	}
	else if(direction == "right"){
		NewPoint.row = row_;
		NewPoint.col = col_+1;
	}
	else if(direction=="up_left"){
		NewPoint.row = row_-1;
		NewPoint.col = col_-1;

	}
	else if(direction=="up_right"){
		NewPoint.row = row_-1;
		NewPoint.col = col_+1;
	}
	else if(direction == "down_left"){
		NewPoint.row = row_+1;
		NewPoint.col = col_-1;
	}
	else if(direction == "down_right"){
		NewPoint.row = row_+1;
		NewPoint.col = col_+1;
	}
	else{ // if no direction return old point
		NewPoint.row = row_;
		NewPoint.col = col_;
	}
	if(NewPoint.row < 0 || NewPoint.row >= row || NewPoint.col < 0 || NewPoint.col >= col){ //if point goes out of bounds
		return start;
	}
	return NewPoint;
}

void Grid::AddAllWords(int &wordcount, loc &start,string direction){ // adds all words recursivley
	if(direction=="END"){ //base case
		return;
	}
	if(start.row < 0 || start.row >= row || start.col < 0 || start.col >= col){
		return; //goes out of bounds end the recursion
	}
	if(wordcount==inwordlist.size()){return;} //if you add all the words stop recursion
	string word = inwordlist[wordcount];
	int prevword = wordcount;// saves previous word
	vector<vector<char> > tempboard = board; //saves previous board
	direction = "up"; // runs through all directions and calls insert word
		InsertWord(word, start,direction,wordcount);
		AddAllWords(wordcount,start,direction); //then calls itself again
	board = tempboard; //same as above for all directions
	wordcount =prevword;
		direction = "left";
		InsertWord(word, start,direction,wordcount);
		AddAllWords(wordcount,start,direction);
	wordcount =prevword;
	board = tempboard;
	direction = "down";
		InsertWord(word, start,direction,wordcount);
		AddAllWords(wordcount,start,direction);
	direction = "right";
	board = tempboard;
	wordcount =prevword;
		InsertWord(word, start,direction,wordcount);
		AddAllWords(wordcount,start,direction);
	wordcount =prevword;
	board = tempboard;
	direction = "up_left";
		InsertWord(word, start,direction,wordcount);
		AddAllWords(wordcount,start,direction);
	wordcount =prevword;
	board = tempboard;
	direction = "up_right";
		InsertWord(word, start,direction,wordcount);
		AddAllWords(wordcount,start,direction);
	wordcount =prevword;
	board = tempboard;
	direction = "down_left";
		InsertWord(word, start,direction,wordcount);
		AddAllWords(wordcount,start,direction);
	wordcount =prevword;
	board = tempboard;
	direction = "down_right";
		InsertWord(word, start,direction,wordcount);
		AddAllWords(wordcount,start,direction);
	wordcount =prevword;
	board = tempboard;
	return;
}
int Grid::numofsols(){ //returns number of solutions
	return solutions.size();
}

vector<vector<vector<char> > > Grid::returnblanks(){ //returns blankgrid 
	return blanks;
}
vector<vector<vector<char> > > Grid::returnsols(){ //returns solutions
	return solutions;
}
