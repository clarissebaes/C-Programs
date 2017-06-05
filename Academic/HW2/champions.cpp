#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include "champions.h"
//CHampion class Implementation

Champions::Champions(){//Default constructor
	champname = "Champ Name";
	playername = "player Name";
	wins = 0;	
	loss = 0;
	win_per = 0;
	min_death = 0;

}
Champions::Champions(string pn,string cn, int w, int l, float wp, int md){//constructor
		champname = cn;
		playername= pn;
		wins = w;	
		loss = l;
		win_per = wp;
		min_death = md;
}
//most of them do what they say they do no tricks no lies
int Champions::getwins() const{
	return wins;
}

int Champions::getloss() const{
	return loss;
}

float Champions::getwin_per(){
	win_per = (float(wins)/float(loss+wins));//calculates win percentage
	return win_per;
}
int Champions::getmin_death() const{
	return min_death;
}
string Champions::getname() const{
	return champname;
}
string Champions::getplayername() const{
	return playername;
}

//Modifiers
void Champions::incrwins(){
	wins++; //incraments winss
}
void Champions::incrloss(){
	loss++; //incraments loss
}
void Champions::incrmin_death(){
	min_death++; //incraments minion deaths
}
