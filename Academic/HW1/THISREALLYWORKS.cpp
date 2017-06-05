#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>
using namespace std;

void print_chart(vector<vector<string> > seatz, string ALPHABET, string flight_num){
	cout<<"Seating Chart for Flight "<<flight_num<<endl<<"\t";//<<"        ";
	for (unsigned int i=0; i < seatz[1].size()-1; i++){
		cout<<ALPHABET[i] <<"    ";
	}
	//cout<<seatz.size();
	cout<<"Seating Class"<<endl;
	for (unsigned int i = 0; i <  seatz.size()-1; ++i){
		cout<<i+1 <<"\t";//<<"       ";
		//cout<<i;
		for (unsigned int j = 1; j < seatz[i].size(); ++j){
			//cout<<j;
			cout<<seatz[i][j]<<" ";
		}
	cout<<seatz[i][0]<<endl;
	//}
}
}

void srn(vector<string> command_info, vector<vector<string> > &seatz, string ALPHABET){
	string clazz;
	clazz = command_info[2];
	if (clazz!= "F" && clazz!= "B" && clazz!= "C"){
		cout<<"Invalid seating class - "<< clazz<< endl;
	}
	else{
		int x = 1;
		for (unsigned int i = 0; i< seatz.size(); i++){
			if (clazz == seatz[i][0]){
				for (unsigned int j = 0; j< seatz[i].size(); j++){ //instead j = 7 size of vec -1
					while (x>0){
						if (seatz[i][j] == "...." && (j == 1|| j ==seatz[i].size()-1 || seatz[i][j+1] == 
							"!!!!" || seatz[i][j-1] == "!!!!")){
							seatz[i][j] = command_info[1];
							cout<<"Passenger "<< command_info[1]<< " was given seat "<< i +1 << ALPHABET[j-1]<<"."<<endl;
							string upgrade;
							x=-1;
						}
						j++;
						if (j >= seatz[i].size()){
							i++;
							j = 0;
							break;
						}
					}		
				}
				break; 
			}
		}
		//fills in middle seats
		if (clazz!= "F" && clazz!= "B" && clazz!= "C"){
			cout<<"Invalid seating class - "<< clazz<< endl;
			for (unsigned int i = 0; i< seatz.size(); i++){
				if (clazz == seatz[i][0]){
					for (unsigned int j = 0; j< seatz[i].size(); j++){ //instead j = 7 size of vec -1
						while (x>0){
							if (seatz[i][j] == "...."){
								seatz[i][j] = command_info[1];
								cout<<"Passenger "<< command_info[1]<< " was given seat "<< i +1 << ALPHABET[j-1]<<"."<<endl;
								string upgrade;
								x=-1;
							}
							j++;
							if (j >= seatz[i].size()){
								i++;
								j = 0;
								break;
							}
						}		
					}
					break; 
				}
			}
		}


}
}

void ssr(vector<string> &command_info, vector<vector<string> > &seatz, string ALPHABET, vector<string> vec_of_class){
	string seat_req = command_info[2];
	string pass_id = command_info[1];
	string seat_req_converted;
	string row(1, seat_req[0]);
	vector<string> class_vec;
	int row_num =  (atoi(row.c_str()))-1;
	int col_num =  ALPHABET.find(seat_req[1]);
	//cout<< "Seat req" <<row_num << col_num <<pass_id<< endl;
	//cout<<seatz[row_num][col_num + 1]<< "jjj"<< endl;
	//cout<<seatz[2][1]<<endl;
	if (row_num < seatz.size() && col_num < seatz[1].size()){

		if (seatz[row_num][col_num+1] == "...."){
			seatz[row_num][col_num+1] = pass_id;
			cout<< "Passenger "<< pass_id << " was given seat "<< seat_req<<"."<< endl;
			string upgrade;
		}
		else{
			cout<<"Passenger "<< pass_id<< " requested an occupied seat "<< seat_req<<"."<<endl;
		string upgrade;
			command_info[2] = vec_of_class[row_num];
			//cout<<row_num<<"   ";
			//cout<<command_info[col_num];
			//cout<<vec_of_class[row_num]<<"   ";
			srn(command_info, seatz, ALPHABET);
		}
	}
	else{
		cout<<"Passenger "<< pass_id<< " requested an invalid seat "<< seat_req<<"."<<endl;
		string upgrade;
	}
}
void upl(vector <vector<string> > &freq_vector, vector<vector<string> > &seatz, vector<string> &upgrade_vect_b, vector<string> &upgrade_vect_f){
	vector<string> non_upgrade_vect;
	upgrade_vect_f.clear();
	upgrade_vect_b.clear();
	//cout<<"YEEEEE"<<freq_vector.size()<<endl;
		for(unsigned int k = 0; k<freq_vector.size(); k++){
			int x = 1;
			string pass_id = freq_vector[k][0];
			for (unsigned int i = 0; i< seatz.size(); i++){
				for (unsigned int j = 0; j< seatz[i].size(); j++){
					if (pass_id == seatz[i][j]){
						//cout<<pass_id<<"X"<<endl;
						non_upgrade_vect.push_back(pass_id);
						x=-1;
					}
				}
			}
		//cout<<non_upgrade_vect.size()<<endl;
		//cout<<x<<k;
		if (x==1){
			if(pass_id != "NO"){
				//cout<<pass_id<<endl;
			}
				//cout<<pass_id<<"mememe";
				if (x==1){
					//cout<<pass_id<<"mememe";
					if (freq_vector[k][1] == "C"){
						upgrade_vect_b.push_back(pass_id);
						cout<<pass_id<<"mememe4";
					}
					if (freq_vector[k][1] == "B"){
						upgrade_vect_f.push_back(pass_id);
					}
				}
			
		}
	}
}

void cxl( vector<string> &command_info, vector<vector<string> > &seatz, vector<string> &upgrade_vect,vector<vector<string> > &freq_vector){
	string pass_id = command_info[1];
	vector <string> new_upgrade_vect;
	//cout<<new_upgrade_vect.size()<<"mememememe";
	int x = 1;
	for (unsigned int i = 0; i< seatz.size(); i++){
		for (unsigned int j = 0; j< seatz[i].size(); j++){
			if (pass_id == seatz[i][j]){
				seatz[i][j] = "....";
			}
		}
	}
	for (unsigned int i =0; i< upgrade_vect.size(); i++){
		if (pass_id == upgrade_vect[i]){
			//cout<<"here";
			upgrade_vect[i]="NO";
		}
	}
		

	for(unsigned int k = 0; k<freq_vector.size(); k++){
		//cout<<"asdf"<<freq_vector[k]<<endl;
		if (pass_id == freq_vector[k][0]){
			//cout<<"here";
			freq_vector[k][0]="NO";
			//cout<<"asdf"<<freq_vector[k]<<endl;
		}
	}
	//cout<<upgrade_vect[i]<<"dddddddd"<<endl;
	

}


int main(int argc, char* argv[]){
	const string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	ifstream seat_layout_file;
	seat_layout_file.open(argv[1]);//("acme_prop_seats.txt");
	vector<vector<string> > seat_vector;
	vector<string> class_vec;
	//creates initial 2d vector using the seating layout file provided
	while (seat_layout_file){
		string col;
		getline (seat_layout_file, col);
		vector<string> temp_vector;
		for (unsigned int i = 0; i< col.size(); i+=2){
			string temp_string;
			if (i == 0){
				temp_string = col[i];
				temp_vector.push_back(temp_string);
				class_vec.push_back(temp_string);
			}
			if(i > 0){
				temp_string = string(4,col[i]);
				temp_vector.push_back(temp_string);
			}
		}
		seat_vector.push_back(temp_vector);
	}

	ifstream flight_commands;
	flight_commands.open(argv[2]);//("acme_flight100_small.txt");
	vector<vector<string> > command_vector;
	while (flight_commands){
		vector<string> temp_vector;
		string command;
		getline (flight_commands, command);
		if (command.size()<4){
			temp_vector.push_back(command);
		} 

		if (command.size()>3){

			string order;
			string passenger_id;
			order = command.substr(0,3);
			passenger_id = command.substr(4,4);
			temp_vector.push_back(order);
			temp_vector.push_back(passenger_id);

			if (command.size()> 8){
			string character;
			character = command[10];
				if (character == " "){
					string seat_command;
					string frequent_fly;
					seat_command = command.substr(9,1);
					frequent_fly = command.substr(11,1);
					temp_vector.push_back(seat_command);
					temp_vector.push_back(frequent_fly);
				}
				else {
					string seat_command;
					string frequent_fly;
					seat_command = command.substr(9,2);
					frequent_fly = command.substr(12,1);
					temp_vector.push_back(seat_command);
					temp_vector.push_back(frequent_fly);
				}
			}
		}
		command_vector.push_back(temp_vector);
	}
	vector<vector<string> > freq_fly_vect;
	for (unsigned int i; i < command_vector.size()-1;i++){
		vector<string> temp_fly_vect;
		if (command_vector[i].size() == 4){
			string is_frequent;
			string fly_class;
			is_frequent = command_vector[i][3];
			fly_class = command_vector[i][2];
			if( is_frequent == "Y"){
				string freq_fly_id = command_vector[i][1];
				temp_fly_vect.push_back(freq_fly_id);
				temp_fly_vect.push_back(fly_class);
				freq_fly_vect.push_back(temp_fly_vect);
			}
		}
		cout<<i<<"Check"<<endl;
		
	}
	vector<string> upgrade_vect_f;
	vector<string> upgrade_vect_b;
	//cout<<freq_fly_vect.size()<<"FFF";
	//cout<<"memems canceld"<<upgrade_vect_f.size()<<"xx"<<endl;
	for (unsigned int i = 0; i <command_vector.size(); i++ ){
		vector<string> command_info = command_vector[i];
		//cout<<command_info[0];
		if (command_info[0] == "SRN"){
			srn(command_info, seat_vector, ALPHABET);
		}
		if (command_info[0] == "SSR"){
			ssr(command_info, seat_vector, ALPHABET, class_vec);
		}
		if (command_info[0] == "PRT"){
			string flight_num = command_vector[0][0];
			print_chart(seat_vector, ALPHABET, flight_num);
		}
		if (command_info[0] == "UPL"){
			upl(freq_fly_vect, seat_vector,upgrade_vect_b,upgrade_vect_f);
			cout<<"The following passengers are scheduled to be upgraded to first class:"<<endl;
			for (unsigned int i =0; i< upgrade_vect_f.size(); i++){
				if (upgrade_vect_f[i] != "NO"){
				cout<<upgrade_vect_f[i]<<endl;

				}
			}
			cout<<"The following passengers are scheduled to be upgraded to business class:"<<endl;
			for (unsigned int i =0; i< upgrade_vect_b.size(); i++){
				if (upgrade_vect_b[i] != "NO"){
					cout<<upgrade_vect_b[i]<<"ccd"<<endl;

				}
				if (upgrade_vect_b[i] == "NO"){
					i++;

				}
			}

			//upl(freq_fly_vect, seat_vector,upgrade_vect_b,upgrade_vect_f);
			//cout<<"The following passengers are scheduled to be upgraded to business class:"<<endl;
			//for (unsigned int i =0; i< upgrade_vect_b.size(); i++){
			//	if (upgrade_vect_b[i] != "NO"){
			//		cout<<upgrade_vect_b[i]<<"cce"<<endl;
			//	}
			//	if (upgrade_vect_f[i] == "NO"){
			//		i++;

			//	}
			//}
			
		}
		if (command_info[0] == "CXL"){
			cxl(command_info, seat_vector,upgrade_vect_f,freq_fly_vect);
		}
	}

return 0;	
}

