#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Time.h"
using namespace std;
//Custom Time Class Implementation
Time::Time(){
	match_id = "Match ID";
}
Time::Time(string m_id){//input the match id
	match_id = m_id;

}
float Time::getfirsttime() const{
	float first = ((match_time_vect[0])/10000);//converts the time from millisecs to seconds
	return first;

}
float Time::getlasttime() const{//same as first time
	float last = ((match_time_vect[(match_time_vect.size()-1)])/1000);
	return last;
}
float Time::getavgtime(){//finds average time between kills
	float total =0;
	for(unsigned int i = 0; i<(match_time_vect.size()-1);i++){
		float diff;
		diff = float(match_time_vect[i+1]-match_time_vect[i]);//determins the time between each kil
		time_between_vect.push_back(diff);//adds the time between to  a vector
	}
	for(unsigned int i = 0; i<time_between_vect.size();i++){//finds the average of the time between kills
		total+=time_between_vect[i];
	}
	float avg = (float(total)/time_between_vect.size())/1000;
	return avg;
}
string Time::getmatchid(){
	return match_id;
}
void Time::addtime(string kill_time){//converts the string to a  float and adds it the match time vector
	float kill_time_float = atof(kill_time.c_str());
	match_time_vect.push_back(kill_time_float);
}



