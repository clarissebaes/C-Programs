#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "players.h"
using namespace std;
//Player class implementation
Players::Players(){//default constructor
	player_name = "Player Name";
	kills = 0;
	deaths = 0;
	kdr = 0.00;
}

Players::Players(string pn, int k, int d, float akdr){//construct from playername, kills,deaths,kdr
 
 	player_name = pn;
	kills = k;	
	deaths = d;
	kdr = akdr;
}
int Players::getkills() const{
	return kills;
}
int Players::getdeaths() const{
	return deaths;
}
void Players::addchamps(string new_champ_namez){
	int x = 1;
	for (unsigned int i = 0; i<champ_namez.size();i++){
		if (new_champ_namez == champ_namez[i]){//checks if the champ is already in the player's champ vector
			x=-1;
		}
	}
	if (x==1){//if champ is not in player champ vector it is added
		champ_namez.push_back(new_champ_namez);
	}
}
float Players::getkdr(){
	float kdrz;//calculates kdr
	if (deaths == 0){//since you cant divide by 0 when deaths = 0, kdr =kills
		kdrz = float(kills);
	}
	else{//calculates kdr
		kdrz = float(kills)/float(deaths);
	}
	return kdrz;
}
vector<string> Players::returnchamp(){
	sort(champ_namez.begin(),champ_namez.end());//alphabetizes the champs
	return champ_namez;
}
string Players::getname() const{
	return player_name;
}
void Players::incrkills(){
	kills++;
}
void Players::incrdeaths(){
	deaths++;
}

