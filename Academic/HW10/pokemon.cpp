#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>
#include <string>
#include "pokemon.h"
using namespace std;

//Pokemon Class Functions

Pokemon::Pokemon(const map<string, vector<string> >  &stats_){ //Pokemon Constructor
	stats = stats_;
}

bool Pokemon::CheckEgg(string egg){ //Checks what egg class the pokemon is in
	for(int i=0; i<stats["eggGroups"].size(); i++){
		if(egg == stats["eggGroups"][i]){
			return true; //returns true if the pokemon is in the specific egg class
		}
	}
	return false;
}

bool Pokemon::CheckAbilities(string ability){ // Distinguises the evolution paths
	//all the pokemon that evolve from/to each other share the first ability stat
	if(stats["abilities"][0]==ability){
		return true;
	}
	else{
		return false;
	}
}

bool Pokemon::CheckHeight(float height){//Used to distinguish between the different
	//levels of evolution, when there are 3 levels of evolution
	//as the pokemon evole their heights get taller
	float compHeight = atof(stats["height"][0].c_str());
	if(height<=compHeight){
		return true;
	}
	else{
		return false;
	}

}

bool Pokemon::CheckBase(string baseStats){//Distingushes each individual pokemon
	//each pokemon has a unique base stats
	if(baseStats == stats["baseStats"][0]){
		return true;
	}
	else{
		return false;
	}
}

bool Pokemon::SharesEggGroup(Pokemon *const pokemon){ 
	// Function used in breeding to see if the pokemon share an egg group
	vector <string> EggGroups = stats["eggGroups"];
	for(int i=0; i<EggGroups.size(); i++){
		if(pokemon->CheckEgg(EggGroups[i])){
			return true;
		}
	}
	return false;
}

string Pokemon::getLabel(){ // returns the label
	return stats["label"][0];
}

//Egg Classes and Constructors---------------------------------------------------------
 
Bug::Bug(const map<string, vector<string> >  &stats_):Pokemon(stats_){
	if(not CheckEgg("Bug")){ //if pokemon isnt a Bug egg type -> throws exception
		throw 7;
	}

}

Grass::Grass(const map<string, vector<string> >  &stats_):Pokemon(stats_){
	if(not CheckEgg("Grass")){//if pokemon isnt a Grass egg type -> throws exception
		throw 7;
	}
}

Flying::Flying(const map<string, vector<string> >  &stats_):Pokemon(stats_){
	if(not CheckEgg("Flying")){ //if pokemon isnt a Flying egg type -> throws exception
		throw 7;
	}
}

Monster::Monster(const map<string, vector<string> >  &stats_):Pokemon(stats_){
	if(not CheckEgg("Monster")){ //if pokemon isnt a Monster egg type -> throws exception
		throw 7;
	}
}

Field::Field(const map<string, vector<string> >  &stats_):Pokemon(stats_){
	if(not CheckEgg("Field")){ //if pokemon isnt a Feild egg type -> throws exception
		throw 7;
	}
}

//Pokemon Classes and Constructors--------------------------------------------------------

Paras::Paras(const map<string, vector<string> > &stats_):Pokemon(stats_),Grass(stats_),Bug(stats_){
	//calls grass and bug class bc its in that egg classes
	if(not CheckAbilities("35")){ //if the ability stat isnt the same then that means that means 
	//its not in that evolution path 
		throw 7;
	}
}

Parasect::Parasect(const map<string, vector<string> > &stats_):Pokemon(stats_),Paras(stats_){
	if(not CheckBase("60")){ //specific for parasect 
		throw 7;
	}
}

//-----------------------------------------------------------------------------------------

Natu::Natu(const map<string, vector<string> > &stats_):Flying(stats_){
	if(not CheckAbilities("163")){//similar idea as above
		throw 7;
	}
}

Xatu::Xatu(const map<string, vector<string> > &stats_):Natu(stats_){
	if(not CheckBase("65")){
		throw 7;
	}
	
}

//-----------------------------------------------------------------------------------------

Whismur::Whismur(const map<string, vector<string> > &stats_):Pokemon(stats_), Monster(stats_), Field(stats_){
	if(not CheckAbilities("146")){
		throw 7;
	}
}

Loudred::Loudred(const map<string, vector<string> > &stats_):Pokemon(stats_), Whismur(stats_){
	if(not CheckHeight(1.000000)){//uses the height to differentiate between the different levels of evolution
		throw 7;
	}
}

Exploud::Exploud(const map<string, vector<string> > &stats_):Pokemon(stats_), Loudred(stats_){
	if(not CheckBase("104")){
		throw 7;
	}
}

//-----------------------------------------------------------------------------------------
//same idea as above
Shinx::Shinx(const map<string, vector<string> > &stats_):Pokemon(stats_), Field(stats_){
	if(not CheckAbilities("122")){
		throw 7;
	}
	
}

Luxio::Luxio(const map<string, vector<string> > &stats_):Pokemon(stats_), Shinx(stats_){
	if(not CheckHeight(0.900000)){
		throw 7;
	}
	
}

Luxray::Luxray(const map<string, vector<string> > &stats_):Pokemon(stats_), Luxio(stats_){
	if(not CheckBase("80")){
		throw 7;
	}
	
}