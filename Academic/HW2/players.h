#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//Player Class declaration
class Players{

	public:
		//Constructor
		Players();
		Players(string pn, int k, int d, float kdr);

		//Accessors
		int getkills() const;//my functions do what they say they do
		int getdeaths() const;
		float getkdr();
		string getchamp() const;
		string getname() const;
		vector<string> returnchamp();

		//Modifiers
		void incrkills();
		void incrdeaths();
		void addchamps(string new_champ_namez);


	private:
		vector<string> champ_namez;//vector of champ namess
		string player_name;
		int kills;
		int deaths;
		double kdr;


}; 