#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


//File: champions.h
//Purpose:

class Champions{

	public:
		//Constructor
		Champions();
		Champions(string pn, string cn, int w, int l, float wp, int md);

		//Accessors
		int getwins() const;
		int getloss() const;
		float getwin_per();
		int getmin_death() const;
		string getname() const;
		string getplayername() const;

		//Modifiers
		void incrwins();
		void incrloss();
		void incrmin_death();

	private: 

		int wins;
		int loss;
		float win_per;
		int min_death;
		string champname;
		string playername;

}; 