#ifndef POKEMON_H
#define POKEMON_H

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
using namespace std;

class Pokemon{
public:
	Pokemon(const map<string, vector<string> >  &stats_);  //constructor
	virtual bool CheckEgg(string egg);
	virtual bool CheckAbilities(string ability);
	virtual bool CheckHeight(float height);
	virtual bool CheckBase(string baseStats);
	virtual bool SharesEggGroup(Pokemon *const pokemon);
	virtual string getLabel();
	virtual ~Pokemon(){}
	
private:
	map<string, vector<string> > stats;
};
//Pokemon egg classes of the Pokemon I have
class Bug: virtual public Pokemon{
public:
	Bug(const map<string, vector<string> >  &stats_);
private:
};

class Grass: virtual public Pokemon{
public:
	Grass(const map<string, vector<string> >  &stats_);
private:
};

class Flying: public Pokemon{
public:
	Flying(const map<string, vector<string> >  &stats_);
private:
};

class Monster: virtual public Pokemon{
public:
	Monster(const map<string, vector<string> >  &stats_);
private:
};

class Field: virtual public Pokemon{
public:
	Field(const map<string, vector<string> >  &stats_);
private:
};

//Rest of the Egg classes not associated with my pokemon

class Amorphous: public Pokemon{
public:
	Amorphous(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

class Dragon: public Pokemon{
public:
	Dragon(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

class Fairy: public Pokemon{
public:
	Fairy(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

class HumanLike: public Pokemon{
public:
	HumanLike(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

class Mineral: public Pokemon{
public:
	Mineral(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

class Water1: public Pokemon{
public:
	Water1(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

class Water2: public Pokemon{
public:
	Water2(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

class Water3: public Pokemon{
public:
	Water3(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

class Ditto: public Pokemon{
public:
	Ditto(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

class Undiscovered: public Pokemon{
public:
	Undiscovered(const map<string, vector<string> >  &stats_): Pokemon(stats_){};
private:
};

//Specific Pokemon classes

class Paras: public Grass, public Bug{
public:
	Paras(const map<string, vector<string> >  &stats_);
private:
};

class Parasect: public Paras{ //evolves from Paras
public:
	Parasect(const map<string, vector<string> >  &stats_);
private:
};

//--------------------------------------------------------------------

class Natu: public Flying{
public:
	Natu(const map<string, vector<string> >  &stats_);
private:
};

class Xatu: public Natu{ //evolves from Natu
public:
	Xatu(const map<string, vector<string> >  &stats_);
private:
};

//--------------------------------------------------------------------

class Whismur: public Monster, public Field{
public:
	Whismur(const map<string, vector<string> >  &stats_);
private:
};

class Loudred: public Whismur{
public:
	Loudred(const map<string, vector<string> >  &stats_);
private:
};

class Exploud: public Loudred{//evolves from Whismur 
public:
	Exploud(const map<string, vector<string> >  &stats_);
private:
};

//--------------------------------------------------------------------

class Shinx: public Field{
public:
	Shinx(const map<string, vector<string> >  &stats_);
private:
};

class Luxio: public Shinx{//evolves from Shinx
public:
	Luxio(const map<string, vector<string> >  &stats_);
private:
};

class Luxray: public Luxio{//evolves from Luxio
public:
	Luxray(const map<string, vector<string> >  &stats_);
private:
};

#endif