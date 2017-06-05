#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>
#include "mtrand.h"
using namespace std;

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef  map< string, map< string, int> >  MY_MAP_2;
typedef  map< string, map< string, map<string, int> > > MY_MAP_3;

bool ReadNextWord(istream &istr, string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}
vector<string> ReadQuotedWords(istream &istr) {
  // returns a vector of strings of the different words
  vector<string> answer;
  string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}
int main (){
  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP_2 data2;
  MY_MAP_3 data3;
  string command;
  int window;    
  while (cin >> command) {

    // load the sample text file
    if (command == "load") {
    	string filename;		
    	string parse_method;
    	cin >> filename >> window >> parse_method;  
 		ifstream storytxt;
 		vector<string> wordz;
 		storytxt.open(filename.c_str());
 		wordz = ReadQuotedWords(storytxt);
 		if(window==2){
	 		for(int i =0;i<wordz.size();i++){
	 			if(i<wordz.size()-1){
	 				++data2[wordz[i]][wordz[i+1]];
	 			}
	 			else{
	 				++data2[wordz[i]]["endzz"];
	 			}
	 		}  
	 	}
	 	if(window==3){
	 		for(int i =0;i<wordz.size()-2;i++){
	 			if(i<wordz.size()-2){
	 				++data3[wordz[i]][wordz[i+1]][wordz[i+2]];
	 			}
	 		}  
	 	}

	 	cout<<"Loaded "<<filename<<" with window = "<<window<<" and parse method = "<<parse_method<<endl<<endl;


    } 
    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
    	if(window ==2){//checks if its 2 or 3 windows
	  		int count =0;
	   		MY_MAP_2::iterator it;
	   	    vector<string> sentence = ReadQuotedWords(cin);
	        for(it=data2.begin(); it!=data2.end();it++){//iterates through outter window
				if(it->first == sentence[0]){
					map< string, int>::iterator tempit;
					map< string, int> tempmap = it->second;
					for(tempit=tempmap.begin(); tempit!=tempmap.end();tempit++){//itetrates through inner window
						count+=tempit->second;			
					}
				}
		 	}
		 	cout<<sentence[0]<<" ("<<count<<")"<<endl;
		    for(it=data2.begin(); it!=data2.end();it++){
				if(it->first == sentence[0]){
					map< string, int>::iterator tempit;
					map< string, int> tempmap = it->second;
					for(tempit=tempmap.begin(); tempit!=tempmap.end();tempit++){
						if(tempit->first!="endzz"){//checks if its last word 
							cout<<sentence[0]<<" "<<tempit->first<<" ("<<tempit->second<<")"<<endl;
						}		
					}
				}
			}
		}
    	if(window ==3){//checks if window 3
	  		int count =0;
	   		MY_MAP_3::iterator it;
	   	    vector<string> sentence = ReadQuotedWords(cin);
	   	    if(sentence.size()==1){//checks if they requested 1 word
		        for(it=data3.begin(); it!=data3.end();it++){
					if(it->first == sentence[0]){//check if the word matches
						map< string, map< string, int> >::iterator tempit1;
						map< string, map< string, int> > tempmap1 = it->second;
						for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
							map< string, int>::iterator tempit2;
							map< string, int> tempmap2 = tempit1->second;
							for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
								count+=tempit2->second;			
							}			
						}
					}
			 	}
			 	cout<<sentence[0]<<" ("<<count<<")"<<endl;
			 	//prints out the total counts above and each individual below
			    for(it=data3.begin(); it!=data3.end();it++){//smae nested iterator for loop
					if(it->first == sentence[0]){
						count =0;
						map< string, map< string, int> >::iterator tempit1;
						map< string, map< string, int> > tempmap1 = it->second;
						for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
							count =0;	
							map< string, int>::iterator tempit2;
							map< string, int> tempmap2 = tempit1->second;
							for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
								count+=tempit2->second;			
							}
							cout<<sentence[0]<<" "<<tempit1->first<<" ("<<count<<")"<<endl;	
						}
					}
				}
			}
			if(sentence.size()==2){ //checks if they asked for 2 words
				count =0;
		        for(it=data3.begin(); it!=data3.end();it++){//very similar to above except this time its keeping track of 2 words
					if(it->first == sentence[0]){
						map< string, map< string, int> >::iterator tempit1;
						map< string, map< string, int> > tempmap1 = it->second;
						for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
							map< string, int>::iterator tempit2;
							map< string, int> tempmap2 = tempit1->second;
							if(tempit1->first == sentence[1]){
								for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
									count+=tempit2->second;			
								}	
							}		
						}
					}
			 	}//same as above
			 	cout<<sentence[0]<<" "<<sentence[1]<<" ("<<count<<")"<<endl;
		        for(it=data3.begin(); it!=data3.end();it++){
					if(it->first == sentence[0]){
						count =0;
						map< string, map< string, int> >::iterator tempit1;
						map< string, map< string, int> > tempmap1 = it->second;
						for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
							count =0;
							map< string, int>::iterator tempit2;
							map< string, int> tempmap2 = tempit1->second;
							if(tempit1->first == sentence[1]){
								for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
									count =0;
									count+=tempit2->second;	
									cout<<sentence[0]<<" "<<sentence[1]<<" "<<tempit2->first<<" ("<<count<<")"<<endl;		
								}

							}		
						}
					}
			 	}
			}
		}
	cout<<endl;
    }
    // generate the specified number of words 
    else if (command == "generate") {
    	if(window ==2){
		    vector<string> sentence = ReadQuotedWords(cin);
		    // how many additional words to generate
		    int i =0;
		    int length;
		    cin >> length;
		    string selection_method;
		    cin >> selection_method;
		    string curword = sentence[0];
		    if (selection_method == "random") { //random selection
		    	MY_MAP_2::iterator it;
				static MTRand_int32 mtrand;//random generator
				while(i<length){
					for(it=data2.begin(); it!=data2.end();it++){
						vector<string> possiblewords;
						if(it->first == curword){
							map< string, int>::iterator tempit;
							map< string, int> tempmap = it->second;
							for(tempit=tempmap.begin(); tempit!=tempmap.end();tempit++){
								for(int i=0;i<tempit->second;i++){
									possiblewords.push_back(tempit->first);//adds the words to a vector of possible words how
																		//ever much they apear in text
								}		
							}
							int randnum = mtrand() % possiblewords.size();//sets max to size of possible words vector
							curword=possiblewords[randnum];//randomly indexes a value 
							sentence.push_back(curword);
							i++;
							break;
						}
					}

				}
				for(int i=0; i<sentence.size();i++){//prints out the sentence
					cout<<sentence[i];
					if(i<sentence.size()-1){
						cout<<" ";
					}
				}
				cout<<endl<<endl;
		   	} 
		    else{
				assert (selection_method == "most_common");//generates the sentence based on the most a common word
				string curword = sentence[0];
				MY_MAP_2::iterator it;
				while(i<length){//length of sentence
					int maxcout =0;
					string maxword;
					for(it=data2.begin(); it!=data2.end();it++){
						if(it->first == curword){
							map< string, int>::iterator tempit;
							map< string, int> tempmap = it->second;
							for(tempit=tempmap.begin(); tempit!=tempmap.end();tempit++){
								if(tempit->second>maxcout){//checks if the count is larger than max count
									maxword=tempit->first;//maxword is redefined 
									maxcout=tempit->second;//maxcount is redefined
								}		
							}
							sentence.push_back(maxword);//pushbacks the maxword
							curword=maxword;//redfines current word as max word
							break;
						}
					}
					i++;

				}
				for(int i=0; i<sentence.size();i++){//prints out sentence
					cout<<sentence[i];
					if(i<sentence.size()-1){
						cout<<" ";
					}
				}
				cout<<endl<<endl;
		    }
		}
    	if(window ==3){//Honestly this is the same as the window 2 but with another nested for loop
		    vector<string> sentence = ReadQuotedWords(cin);
		    int i =0;
		    int length;
		    cin >> length;
		    string selection_method;
		    cin >> selection_method;
		    if(sentence.size() == 1){
			    if (selection_method == "random") { 
					static MTRand_int32 mtrand;
					int count =  0;
					string curword = sentence[0];
					string prevcurword;
					string tempword;
					MY_MAP_3::iterator it;
					int i =0;
					while(i<length){
						int maxcount =0;
						string maxword;
						for(it=data3.begin(); it!=data3.end();it++){
							vector<string> possiblewords;
							if(i==0){
								if(it->first == curword){
									count =0;
									map< string, map< string, int> >::iterator tempit1;
									map< string, map< string, int> > tempmap1 = it->second;
									for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
										count =0;	
										map< string, int>::iterator tempit2;
										map< string, int> tempmap2 = tempit1->second;
										for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
											for(int i=0;i<tempit2->second;i++){
												possiblewords.push_back(tempit1->first);
											}		
										}
									}
									int randnum = mtrand() % possiblewords.size();
									prevcurword=curword;
									curword=possiblewords[randnum];
									sentence.push_back(curword);
									i++;
									break;	
								}
							}
							
							else{
								if(it->first == prevcurword){
									count =0;
									map< string, map< string, int> >::iterator tempit1;
									map< string, map< string, int> > tempmap1 = it->second;
									for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
										if(tempit1->first == curword){
											count =0;	
											map< string, int>::iterator tempit2;
											map< string, int> tempmap2 = tempit1->second;
											for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
												for(int i=0;i<tempit2->second;i++){
													possiblewords.push_back(tempit2->first);//same idea as above
												}	
											}
										}			
									}
									int randnum = mtrand() % possiblewords.size();
									prevcurword=curword;
									curword=possiblewords[randnum];
									sentence.push_back(curword);
									i++;
									break;
											
								}
							}
						}
					}
					for(int i=0; i<sentence.size();i++){//prints out sentence
						cout<<sentence[i];
						if(i<sentence.size()-1){
							cout<<" ";
						}
					}
					cout<<endl<<endl;

			   	} 
			    else{
					assert (selection_method == "most_common");//genereates most commone sentence same idea as window 2
					int count =  0;
					string curword = sentence[0];
					string prevcurword;
					string tempword;
					MY_MAP_3::iterator it;
					int i =0;
					while(i<length){
						int maxcount =0;
						string maxword;
						for(it=data3.begin(); it!=data3.end();it++){
							if(i==0){
								if(it->first == curword){
									count =0;
									map< string, map< string, int> >::iterator tempit1;
									map< string, map< string, int> > tempmap1 = it->second;
									for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
										count =0;	
										map< string, int>::iterator tempit2;
										map< string, int> tempmap2 = tempit1->second;
										for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
											count+=tempit2->second;			
										}
										if(count>maxcount){
												maxcount = count;
												maxword = tempit1->first;
										}
				 
									}
								}
							}
							else{
								maxcount=0;
								if(it->first == prevcurword){
									count =0;
									map< string, map< string, int> >::iterator tempit1;
									map< string, map< string, int> > tempmap1 = it->second;
									for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
										if(tempit1->first == curword){
											count =0;	
											map< string, int>::iterator tempit2;
											map< string, int> tempmap2 = tempit1->second;
											for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
												count =0;
												count+=tempit2->second;	
												tempword =tempit2->first;
												if(count>maxcount){//if the count of the word is higher than max counting 
													maxcount = count;//redinfes maxcount
													maxword = tempword;//redefines 
												}	
											}
										}				
									}
								}
							}
						}
						sentence.push_back(maxword);
						i++;
						prevcurword=curword;
						curword=maxword;
					}
					for(int i=0; i<sentence.size();i++){//prints out sentence
						cout<<sentence[i];
						if(i<sentence.size()-1){
							cout<<" ";
						}
					}
					cout<<endl<<endl;
			    }
			}
			if(sentence.size()==2){//sentence size 2

			    if (selection_method == "random") {//random generator again similar to above
			    	static MTRand_int32 mtrand;
					string curword = sentence[1];
					string prevcurword = sentence[0];
					MY_MAP_3::iterator it;
					int i =0;
			    	while(i<length){
						for(it=data3.begin(); it!=data3.end();it++){
							vector<string> possiblewords;
							if(it->first == prevcurword){
								map< string, map< string, int> >::iterator tempit1;
								map< string, map< string, int> > tempmap1 = it->second;
								for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
									if(tempit1->first == curword){	
										map< string, int>::iterator tempit2;
										map< string, int> tempmap2 = tempit1->second;
										for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
											for(int i=0;i<tempit2->second;i++){
												possiblewords.push_back(tempit2->first);
											}	
										}
									}			
								}
								int randnum = mtrand() % possiblewords.size();
								prevcurword=curword;
								curword=possiblewords[randnum];
								sentence.push_back(curword);
								i++;
								break;
										
							}
						}
					}
					for(int i=0; i<sentence.size();i++){
						cout<<sentence[i];
						if(i<sentence.size()-1){
							cout<<" ";
						}
					}
					cout<<endl<<endl;
			   	} 
			   	else{//this is the same as above
					assert (selection_method == "most_common");
					int count =  0;
					string curword = sentence[1];
					string prevcurword = sentence[0];
					string tempword;
					MY_MAP_3::iterator it;
					int i =0;
					while(i<length){
						int maxcount =0;
						string maxword;
						for(it=data3.begin(); it!=data3.end();it++){
							maxcount=0;
							if(it->first == prevcurword){
								count =0;
								map< string, map< string, int> >::iterator tempit1;
								map< string, map< string, int> > tempmap1 = it->second;
								for(tempit1=tempmap1.begin(); tempit1!=tempmap1.end();tempit1++){
									if(tempit1->first == curword){
										count =0;	
										map< string, int>::iterator tempit2;
										map< string, int> tempmap2 = tempit1->second;
										for(tempit2=tempmap2.begin(); tempit2!=tempmap2.end();tempit2++){
											count =0;
											count+=tempit2->second;	
											tempword =tempit2->first;	
											if(count>maxcount){//checking if xount of the individual word is higher than max again
												maxcount = count;
												maxword = tempword;
											}	
										}
		
									}					
								}

							}
						}
						sentence.push_back(maxword);
						i++;
						prevcurword=curword;
						curword=maxword;

					}
					for(int i=0; i<sentence.size();i++){//prints out sentence
						cout<<sentence[i];
						if(i<sentence.size()-1){
							cout<<" ";
						}
					}
					cout<<endl<<endl;
				} 
			}
		}
    } 
    else if (command == "quit") {//quits
      break;
    } else {
      cout << "WARNING: Unknown command: " << command << endl;
    }
  }
}