#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//custom Time class declaration
class Time{

	public:
		//Constructor
		Time();
		Time(string m_id);

		//Accessors
		float getfirsttime() const;
		float getlasttime() const;
		float getavgtime();
		string getmatchid();

		//Modifiers
		void addtime(string kill_time);


	private:
		vector<float> match_time_vect;//used to store the specific time of the kills
		vector<float> time_between_vect;//used to store the time inbetween killss
		string match_id;

}; 





