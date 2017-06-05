#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "champions.h"
#include "players.h"
#include "Time.h"
using namespace std;
bool isinchamps(string name_player, vector<Champions> class_vector){
	for (unsigned int i = 0; i<class_vector.size();i++){ //This checks if a player is already in the champion class
		if (name_player == class_vector[i].getname()){
			return true;//if player in the class then this returns true
		}
	}
return false;
}

bool isinplayers(string name_player, vector<Players> class_vector){
	for (unsigned int i = 0; i<class_vector.size();i++){//this checks if a player is in the player class
		if (name_player == class_vector[i].getname()){
			return true;//returns true if the player is already in the player class
		}
	}
return false;
}

bool sortplayers(Players player_1, Players player_2){
	if (player_1.getkdr()>player_2.getkdr()){//sorts the players first by KDR
		return true;
	}
	if(player_1.getkdr()<player_2.getkdr()){
		return false;
	}
	else{
		if (player_1.getkills()>player_2.getkills()){//then by kills
			return true;
		}
		if(player_1.getkills()<player_2.getkills()){
			return false;
		}
		else{
			if(player_1.getdeaths()<player_2.getdeaths()){//then least deaths
				return true;
			}
			if(player_1.getdeaths()>player_2.getdeaths()){
				return false;
			}
			else{
				if(player_1.getname()<player_2.getname()){//then alphabetically
					return true;
				}
				else{
					return false;
				}
			}
		}
	}
}
bool sortchamps(Champions champ_1, Champions champ_2){
	if (champ_1.getwin_per()>champ_2.getwin_per()){//Sorts champions by win percentage
		return true;
	}
	if(champ_1.getwin_per()<champ_2.getwin_per()){
		return false;
	}
	else{
		if (champ_1.getwins()>champ_2.getwins()){//then wins
			return true;
		}
		if(champ_1.getwins()<champ_2.getwins()){
			return false;
		}
		else{
			if(champ_1.getloss()<champ_2.getloss()){//then least losses
				return true;
			}
			if(champ_1.getloss()>champ_2.getloss()){
				return false;
			}
			else{
				if(champ_1.getname()<champ_2.getname()){//then alphabetically
					return true;
				}
				else{
					return false;
				}
			}
		}
	}
}
int main(int argc, char* argv[]){
	ifstream inputStats;
	string type;
	inputStats.open(argv[1]);//opens input file
	ofstream outfile(argv[2]);//sets output file
	type = argv[3];//type of chart the user request
	outfile<<fixed<<setprecision(2);//sets precision and layot for output file later on
	string var_trash;//trash variable for non essential inputs
	string match_id;
	vector<Players> player_objects;//creates a vector of player objects
	vector<Champions> champion_objects;//creates a vector of champion objects
	vector<Time> match_time_objects;//creats a vector of time objects
	int match_incr = 0;//used to keep track of each individual match and times for later on
	while(inputStats){//while loop that runs through the input file
		string var;//the current word
		inputStats>>var;
		if (var == "MATCH"){
			inputStats>>var_trash;
			inputStats>> match_id;//assigns match id
			match_time_objects.push_back(Time(match_id));//passes match id through the time class to create an object for that specific match
			match_incr++;//increments the match counter
		}
		if (var == "LOSING" || var == "WINNING"){ //Runs through both winning and lossing teams
			inputStats>> var_trash;
			for(int i=0; i<5;i++){//you can use a for a loop since each team will always have 5 players
				string player;
				string champ;
				inputStats>>player;
				inputStats>>var_trash;
				inputStats>>var_trash;
				inputStats>>champ;
				if (not(isinchamps(champ,champion_objects))){//checks if champ is in the champ class already
					if (var == "LOSING"){//if they arent it creates an object of the champ in the class
						champion_objects.push_back(Champions(player,champ,0,1,0,0));
					}//either sets wins to 1 or losses to  1 depending on what team they are on
					if (var == "WINNING"){
						champion_objects.push_back(Champions(player,champ,1,0,0,0));
					}
				}
				else{//if the champ already is in the class
					for (unsigned int i = 0; i<champion_objects.size(); i++)
						if (champ == champion_objects[i].getname()){
							if (var == "LOSING"){
								champion_objects[i].incrloss();
							}
							if (var == "WINNING"){
								champion_objects[i].incrwins();
							}
						}
				}
				if (not isinplayers(player, player_objects)){//checks if player is in player class
					Players temp_player = Players(player,0,0,0);//adds player
					temp_player.addchamps(champ);
					player_objects.push_back(temp_player);
				}
				else{
					for(unsigned int i =0; i<player_objects.size(); i++){// if the player is already in the class
						if (player == player_objects[i].getname()){
							player_objects[i].addchamps(champ);//adds the champ to the player's champ list
						}
					}
				}
			}
		}
		if (var == "@"){ //checks the events
			vector<string> temp_vect;
			string time;
			string killer_name, victim_name;
			inputStats>> time;
			match_time_objects[match_incr-1].addtime(time);//adds the time to the custom class time vector
			inputStats>> killer_name;
			if (killer_name == "minion"){//checks for minion deaths
				inputStats>> var_trash;
				inputStats>> victim_name;
				for (unsigned int i = 0; i<champion_objects.size();i++){
					if (victim_name == champion_objects[i].getplayername()){
						champion_objects[i].incrmin_death();//incraments the champions minion deaths
					}
				}
				for (unsigned int i = 0; i<player_objects.size();i++){
					if(victim_name== player_objects[i].getname()){
						player_objects[i].incrdeaths();//incraments the player death
					}
				}
			}
			else{
				for (unsigned int i = 0; i<player_objects.size();i++){
					if(killer_name== player_objects[i].getname()){
						player_objects[i].incrkills();//incraments the killer's kills in the player class
					}
				}
			}
		}
		if (var == "killed"){//checks for victims
			string victim_name;
			inputStats>>victim_name;
			for (unsigned int i = 0; i<player_objects.size();i++){
				if(victim_name== player_objects[i].getname()){
					player_objects[i].incrdeaths();//incraments the players death count
				}
			}
		}
	}
	sort(champion_objects.begin(), champion_objects.end(), sortchamps);//sorts the vector of champion class using sort function from above
	if(type == "champions"){//if the user request champion
		outfile<<left<<setw(24)<<"CHAMPION NAME";//printing out for the specific layout
		outfile<<right<<setw(4)<<"WINS"<<right<<setw(8)<<"LOSSES";
		outfile<<right<<setw(8)<<"WIN%"<<right<<setw(16)<<"MINION DEATHS"<<endl;
		for (unsigned int i = 0; i<champion_objects.size();i++){
			outfile<<left<<setw(24)<<champion_objects[i].getname()<<right<<setw(4)<<champion_objects[i].getwins();
			outfile<<right<<setw(8)<<champion_objects[i].getloss()<<right<<setw(8)<<champion_objects[i].getwin_per();
			outfile<<right<<setw(16)<<champion_objects[i].getmin_death()<<endl;
		} 
	}
	sort(player_objects.begin(), player_objects.end(), sortplayers);//sorts player vector using above sorting function
	if(type == "players"){ 
		outfile<<left<<setw(23)<<"PLAYER NAME";
		outfile<<right<<setw(5)<<"KILLS"<<right<<setw(8)<<"DEATHS";
		outfile<<right<<setw(8)<<"KDR"<<"   "<<"PLAYED WITH CHAMPION(S)"<<endl;
		for (unsigned int i = 0; i<player_objects.size();i++){//prints out chart in a specific layout
			outfile<<left<<setw(23)<<player_objects[i].getname()<<right<<setw(5)<<player_objects[i].getkills();
			outfile<<right<<setw(8)<< player_objects[i].getdeaths()<<right<<setw(8)<<player_objects[i].getkdr()<<"   ";
			
			for(unsigned int j =0; j<((player_objects[i].returnchamp()).size());j++){
				if(j>0){
					outfile<<", "<<(player_objects[i].returnchamp())[j];
				}
				else{
					outfile<<(player_objects[i].returnchamp())[j];
				}
			}
			outfile<<endl;
		}
	}
	if(type == "custom"){//if the user request the custom chart
		outfile<<left<<setw(23)<<"Mathc ID"<<right<<setw(20)<<"Time of First Kill";
		outfile<<right<<setw(20)<< "Time of Last Kill"<<right<<setw(30);
		outfile<<"Aversge Time between Kills"<<endl;
		for (unsigned int i = 0; i<match_time_objects.size();i++){
			outfile<<left<<setw(23)<<match_time_objects[i].getmatchid()<<right<<setw(10)<<match_time_objects[i].getfirsttime();
			outfile<<right<<" seconds"<<right<<setw(13)<<match_time_objects[i].getlasttime();
			outfile<<right<<" seconds"<<right<<setw(15)<<match_time_objects[i].getavgtime()<<" seconds"<<endl;
		}
	}
	outfile.close();
	return 0;
}

