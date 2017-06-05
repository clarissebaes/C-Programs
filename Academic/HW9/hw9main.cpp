#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cassert>
#include "hash.h"
using namespace std;
int main(){
	string command;
	Hash tableish(100); //creats initial table
	string genome; 
	while(cin>>command){ // gets the commands
		if(command=="genome"){ //gets the genome from the file
			string file;
			cin>>file;
			ifstream genome_file;
			genome_file.open(file.c_str());
			string temp;
			while(genome_file>>temp){
				genome+=temp; //saves the full genome to  a string
			}
		}
		if(command=="table_size"){ //sets table size
			int tableSize;
			cin>>tableSize;
			tableish.setTableSize(tableSize);
		}
		if(command=="occupancy"){ //sets occupancy
			float maxSize;
			cin>>maxSize;
			tableish.setMaxOccupancy(maxSize);
		}
		if(command == "kmer"){ //sets kmer size
			int kmerSize;
			cin>>kmerSize;
			tableish.setKmerSize(kmerSize); //hashs the genome according to the kmer size
			for(int i=0; i<(genome.size()-kmerSize);i++){
				string tempKmer;
				for(int j=0;j<kmerSize;j++){
					tempKmer+=genome[i+j];
				}
				tableish.Insert(tempKmer,i); //inserts the kmer and starting position to the has funciton
			}
		}
		if(command == "quit"){}//quits
		if(command == "query"){
			int maxMisCount;
			string daKey;
			int kmerSize = tableish.getKmerSize();
			cin>>maxMisCount; //max miscounts the genome can have
			cin>>daKey; // the key your looking for
			cout<<"Query: "<<daKey<<endl;
			string searchKey = daKey.substr(0,kmerSize);
			vector<int> startPoz = tableish.getStartPos(searchKey);
			if(startPoz.size()==0){ //if the position vector is empty no matches
				cout<<"No Match"<<endl;
			}
			else{ //else I run through the vector
				int miscount =0;
				vector<string> output;
				bool full = true;
				vector<int> leMisCounts;
				vector<int> finalpos;
				for(int x= 0; x<startPoz.size();x++){ //runs through the starting postion vector
					full = true;
					miscount=0;
					string temp ="";
					for(int k=0; k<daKey.size(); k++){ // iterates through the query
						temp+=genome[(startPoz[x])+k];
						if(daKey[k]!=genome[(startPoz[x])+k]){
							miscount++; //keeps track of miscounts
						}
						if(miscount>maxMisCount){ //if miscounts exceed
							full = false;
							temp = "";
							break;
						}
					}
					if(full ==true){ //if it went through the whole sequence then 
						finalpos.push_back(startPoz[x]); //pushes back the position to a final output vector
						output.push_back(temp);
						leMisCounts.push_back(miscount); 
						temp ="";
					}
				}
				int count=0;
				for(int j =0; j<output.size();j++){
					if(output[j].size()<daKey.size()){
						break;
					}
					else{
						cout<<finalpos[j]<<" "<<leMisCounts[j]<<" "<<output[j]<<endl;
						count++;
					}
				}
				if(count ==0){ //prints out no matches
					cout<<"No Match"<<endl;
				}
			}
		}
	}
}