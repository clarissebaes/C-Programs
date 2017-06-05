#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

class Time{

	public:
		//Constructor
		Time();
		Time(string pn);

		//Accessors
		float getfirsttime() const;
		float getlasttime() const;
		float getavgtime();

		//Modifiers
		void addtime(string kill_time);


	private:
		vector<float> time_vect;
		string player_name;
		float average_time;


}; 





