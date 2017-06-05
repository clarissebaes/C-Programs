#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <cstdlib> // used for atoi
using namespace std;
//prints out seat layout
void print_chart(vector<vector<string> > seatz, string ALPHABET, string flight_num){
	cout<<"Seating Chart for Flight "<<flight_num<<endl<<"\t";
	for (unsigned int i=0; i < seatz[1].size()-1; i++){
		cout<<ALPHABET[i] <<"    ";//prints out the letter rows based on the seatlayout
	}
	cout<<"Seating Class"<<endl;
	for (unsigned int i = 0; i <  seatz.size()-1; ++i){
	//double for loop (i rows,j cols) iterates through seat layout and prints out each coresponding seat
		cout<<i+1 <<"\t";
		for (unsigned int j = 1; j < seatz[i].size(); ++j){
			cout<<seatz[i][j]<<" ";
		}
	cout<<seatz[i][0]<<endl;
	}
}
bool srn( vector<string> command_info, vector<vector<string> > &seatz, string ALPHABET){
	//used when a passenger request a class
	string clazz;//seatz is the 2d vector of the seat layout, passed by refrence so it can be changed
	clazz = command_info[2];
	//command info is a vector of the commands and seatz is a 2d vector of the seat layout
	if (clazz!= "F" && clazz!= "B" && clazz!= "C"){//checks if a valid class is picked
		cout<<"Invalid seating class - "<< clazz<< endl;
	}
	else{
		int x = 1;
		for (unsigned int i = 0; i< seatz.size(); i++){
		//this double for loop(i rows,j cols) iterates through the seating chart
			if (clazz == seatz[i][0]){
			//makes sure that the requested class matches the class of the row
				for (unsigned int j = 0; j< seatz[i].size(); j++){ //i
					while (x>0){//while loop keeps checking for seats until the passenger is seated
						if (seatz[i][j] == "...." && (j == 1|| j ==seatz[i].size()-1 || seatz[i][j+1] == 
							"!!!!" || seatz[i][j-1] == "!!!!")){
							//if statement checks for windows(j=1 or size of row-1) 
							//or aisles(seat next to !!!!) and if the seat is open(....)
							seatz[i][j] = command_info[1];//if seat is open assigns passenger id to the seat(replaces .... with pass id)
							cout<<"Passenger "<< command_info[1]<< " was given seat "<< i +1 << ALPHABET[j-1]<<"."<<endl;
							string upgrade;
							x=-1;//if the passenger is seated then x=-1 and breaks while loop
						}
						j++;//iterates j (col) if passenger is not seated
						if (j >= seatz[i].size()){//checks if passenger gets to end of row & is still not seated
							i++;//incraments i so passenger checks next row
							j = 0;//resets j(col) to first column
							break;
						}
					}		
				}
				return(true);//used later on in upp function to check if the passenger is upgraded
				break; 
			}
		}
		//fills in middle seats once all window and aisle seats are filled
		if (clazz!= "F" && clazz!= "B" && clazz!= "C"){//confirms a valid class is requested
			cout<<"Invalid seating class - "<< clazz<< endl;
			for (unsigned int i = 0; i< seatz.size(); i++){//similar double for loop mentioned above
				if (clazz == seatz[i][0]){
					for (unsigned int j = 0; j< seatz[i].size(); j++){ 
						while (x>0){
							if (seatz[i][j] == "...."){//checks if the seat is unoccupied(....)
								seatz[i][j] = command_info[1];//if seat is free assigns pass id to seat, seat layout
								cout<<"Passenger "<< command_info[1]<< " was given seat "<< i +1 << ALPHABET[j-1]<<"."<<endl;
								string upgrade;
								x=-1;
							}
							j++;
							if (j >= seatz[i].size()){//similar loop and check as above
								i++;
								j = 0;
								break;
							}
						}		
					}
				return(true); //used later on in upp function to check if Milena Gonzalezthe passenger is upgraded
				break; 
				}
			}
		}
	}
	return(false);	
}
// ssr is used when the passenger request a specific seat
void ssr(vector<string> &command_info, vector<vector<string> > &seatz, 
	string ALPHABET, vector<string> vec_of_class){
	string seat_req = command_info[2];//specific requested seat
	string pass_id = command_info[1];
	string seat_req_converted;//convert the string request seat (ex.2B) to corresponging int(22)
	string row(1, seat_req[0]);//string of the row number
	vector<string> class_vec;
	int row_num =  (atoi(row.c_str()))-1;//converts the string row number to an integer
	int col_num =  ALPHABET.find(seat_req[1]);//finds the index of the row letter of the entire alphabet to get column number 
	if (row_num < seatz.size() && col_num < seatz[1].size()){//makes sure the requested seat is actually in the plane

		if (seatz[row_num][col_num+1] == "...."){//checks if seat is unoccupied
			seatz[row_num][col_num+1] = pass_id;
			cout<< "Passenger "<< pass_id << " was given seat "<< seat_req<<"."<< endl;
			string upgrade;
		}
		else if (seatz[row_num][col_num+1] == "!!!!"){//checks if requested seat is an aisle
			cout<<"Passenger "<< pass_id<< " requested an invalid seat "<< seat_req<<"."<<endl;
			string upgrade;
			command_info[2] = vec_of_class[row_num];
			srn(command_info, seatz, ALPHABET);
			//if the passenger is not seat, run the srn to try and sit the passenger in another seat with in the class
		}
		else{//if seat does not contain a .... or !!!!, the seat is occupied by another passenger
			cout<<"Passenger "<< pass_id<< " requested an occupied seat "<< seat_req<<"."<<endl;
			//string upgrade;
			command_info[2] = vec_of_class[row_num];
			srn(command_info, seatz, ALPHABET);
		}
	}
	else{//when the  passenger request a seat that does not exist on the plane
		cout<<"Passenger "<< pass_id<< " requested an invalid seat "<< seat_req<<"."<<endl;
		//string upgrade;
	}
}
//upl prints the potential upgrade list
void upl(vector <vector<string> > &freq_vector, vector<vector<string> > &seatz, vector<string> &upgrade_vect_b, vector<string> &upgrade_vect_f){
	//freq_vector is a 2d vector of the all the frequent flyer's pass id and current class request
	vector<string> non_upgrade_vect;
	upgrade_vect_f.clear();//clears the upgrading to first class vector
	upgrade_vect_b.clear();//smae thing with the upgrade to business class vector
		for(unsigned int k = 0; k<freq_vector.size(); k++){//iterates through the freq_vector
			int x = 1;//used to check if the frequent flyer is already seated
			string pass_id = freq_vector[k][0];
			for (unsigned int i = 0; i< seatz.size(); i++){//iterates through seating layout
				for (unsigned int j = 0; j< seatz[i].size(); j++){
					if (pass_id == seatz[i][j]){//checks if the frequent flyer is already seated if they are they dont need to be upgraded
						non_upgrade_vect.push_back(pass_id);//adds them to the non upgrade vector
						x=-1;//since they are seated x is set to -1 so that they dont pass through next if statement
					}
				}
			}
		if (x==1){//if x is 1 it means that the frequent flyer was not seated and qualifies for an upgrade
			if(pass_id != "NO"){//
				
				if (freq_vector[k][1] == "C"){//adds them to the upgrade to business list
					upgrade_vect_b.push_back(pass_id);
				}
				if (freq_vector[k][1] == "B"){//adds them to upgrade to first list
					upgrade_vect_f.push_back(pass_id);
				}
			}
		}
	}
}
//cxl used to cancle and remove the passenger from the seat layout and upgrade vectors
void cxl( vector<string> &command_info, vector<vector<string> > &seatz, vector<string> &upgrade_vect_b, vector<string> &upgrade_vect_f,vector<vector<string> > &freq_vector){
	string pass_id = command_info[1];
	vector <string> new_upgrade_vect;
	int x = 1; //used later on to see if the passenger was actually found if x=-1 passenger was found, if x=1 passenger was not found
	for (unsigned int i = 0; i< seatz.size(); i++){
		for (unsigned int j = 0; j< seatz[i].size(); j++){
			if (pass_id == seatz[i][j]){//if passenger is seated then their id in the seat is replaced by .... and is now unocupied
				seatz[i][j] = "....";
				x =-1;
			}
		}
	}
	for (unsigned int i =0; i< upgrade_vect_f.size(); i++){
		if (pass_id == upgrade_vect_f[i]){//changes id in the upgrade list so that their name will not be printes
			upgrade_vect_f[i]="NO";
			x =-1;
		}
	}
	for (unsigned int i =0; i< upgrade_vect_b.size(); i++){// same as above but for business upgrades
		if (pass_id == upgrade_vect_b[i]){
			upgrade_vect_b[i]="NO";
			x =-1;
		}
	}
	for(unsigned int k = 0; k<freq_vector.size(); k++){//same as bove but for the overall frequent flyers list
		if (pass_id == freq_vector[k][0]){
			freq_vector[k][0]="NO";
			x = -1;
		}
	}
	if (x == 1){//if passenger wasnt found out puts this error
		cout<<"Passenger "<<pass_id<<" could not be found"<<endl;
	}
}
//UPP actually prints the upgrades
void upp(vector<string> &upgrade_vect_b, vector<string> &upgrade_vect_f, vector<vector<string> > &seatz, string ALPHABET){
	vector<vector<string> > input_vector;//this 2d vector imitates the structure of the command vector so that it can be passed into the srn function
		for (unsigned int i = 0; i< upgrade_vect_f.size(); i++ ){
			string pass_id = upgrade_vect_f[i];
			if (pass_id != "NO"){//pass id is NO hwne the passenger cancled, makes sure only eligible passengers are checked for upgrades
				vector<string> temp_vector;//temp used to make the input vector
				string pass_id = upgrade_vect_f[i];
				string clazz = "F";
				temp_vector.push_back(pass_id);
				temp_vector.push_back(pass_id);
				temp_vector.push_back(clazz);//clazz is the [2] index in input_vector which mirrios the command vector
				if(srn(temp_vector, seatz, ALPHABET) == true){//if true then the passenger was upgraded
					cout<<"Passenger "<< pass_id<<" was upgraded to the first class section."<<endl;
				}
			}
		}
		for (unsigned int i = 0; i< upgrade_vect_b.size(); i++ ){//same ish as the above first class loop
			string pass_id = upgrade_vect_b[i];//
			if (pass_id != "NO"){
				vector<string> temp_vector;
				string clazz = "B";
				temp_vector.push_back(pass_id);
				temp_vector.push_back(pass_id);
				temp_vector.push_back(clazz);
				srn(temp_vector, seatz, ALPHABET);
				if(srn(temp_vector, seatz, ALPHABET) == true){
					cout<<"Passenger "<< pass_id<<" was upgraded to the business class section."<<endl;

				}
			}
		}

}
int main(int argc, char* argv[]){
	const string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ");// global string used to index and change the col letters to integers
	ifstream seat_layout_file;//read in layout file
	seat_layout_file.open(argv[1]);
	vector<vector<string> > seat_vector; //declares the 2d seat layout vector
	vector<string> class_vec;
	if (!seat_layout_file.good()) {//checks if file is good
	    std::cerr << "Can't open " << argv[1] << " to read.\n";
	    exit(1);
  	}
	//creates initial 2d vector using the seating layout file provided
	while (seat_layout_file){
		string col;
		getline (seat_layout_file, col);//each line will be a vecotr of the seats and aisles
		vector<string> temp_vector;//vector of each line that will be added to 
		for (unsigned int i = 0; i< col.size(); i+=2){
			string temp_string;
			if (i == 0){
				temp_string = col[i];
				temp_vector.push_back(temp_string);
				class_vec.push_back(temp_string);
			}
			if(i > 0){
				temp_string = string(4,col[i]);// makes the single . or ! to .... or !!!! for layout
				temp_vector.push_back(temp_string);
			}
		}
		seat_vector.push_back(temp_vector); //adds the temp vector of each line to the main 2d vector
	}
	ifstream flight_commands;
	flight_commands.open(argv[2]);
	if (!flight_commands.good()) {//reads in command file 
	 std::cerr << "Can't open " << argv[2] << " to read.\n";//checks if file is good
	    exit(1);
  	}
	vector<vector<string> > command_vector;
	while (flight_commands){// makes the the 2d command vector
		vector<string> temp_vector;//temp vector concept same as the concept as the above while loop to make the 2d vector
		string command;
		getline (flight_commands, command);
		if (command.size()<4){// if command sizes<4 that means this line only contains one 3 letter command and no other info
			temp_vector.push_back(command);//adds it the temp vector
		} 

		if (command.size()>3){//if size greater than 3 means more info on line
			string order;
			string passenger_id;
			order = command.substr(0,3);//gets the first three indexs of the line which is the command
			passenger_id = command.substr(4,4);//gets hte passenger id
			temp_vector.push_back(order);//adds it info to the temp vector
			temp_vector.push_back(passenger_id);

			if (command.size()> 8){// if greater than 8 command is either srn or ssr because you need to index the info differently for each
			string character;
			character = command[10];
				if (character == " "){//if the 10th index is a space then the command is SRN and the passenger only requested a class
					string seat_command;
					string frequent_fly; 
					seat_command = command.substr(9,1);//indexes the calss info
					frequent_fly = command.substr(11,1);//Y or N for frequent flyer
					temp_vector.push_back(seat_command);//adds the info to the temp vector 
					temp_vector.push_back(frequent_fly);
				}
				else {//if the 10th space is not a space then they requested a specific seat
					string seat_command;
					string frequent_fly;
					seat_command = command.substr(9,2);//takes the specific seat (ex. 1A)
					frequent_fly = command.substr(12,1);
					temp_vector.push_back(seat_command);//adds it to the temp vector
					temp_vector.push_back(frequent_fly);
				}
			}
		}
		command_vector.push_back(temp_vector);//adds the temp vector to the 2d vector
	}
	vector<vector<string> > freq_fly_vect;//creates a 2d vector of all the frequent flyer's Passenger id and what class they are in
	for (unsigned int i = 0; i < command_vector.size()-1;i++){
		vector<string> temp_fly_vect;
		if (command_vector[i].size() == 4){
			string is_frequent;
			string fly_class;
			is_frequent = command_vector[i][3];
			fly_class = command_vector[i][2];
			if( is_frequent == "Y"){//checks if they are a frequent flyer
				string freq_fly_id = command_vector[i][1];//if they are a frequent flyer their info gets added to the temp vector
				temp_fly_vect.push_back(freq_fly_id);
				temp_fly_vect.push_back(fly_class);
				freq_fly_vect.push_back(temp_fly_vect);//temp vector gets added to main 2d frequent flyer vectir
			}
		}		
	}
	vector<string> upgrade_vect_f;//upgrade vector for going to first class
	vector<string> upgrade_vect_b;//upgrade vector for going to business
	for (unsigned int i = 0; i <command_vector.size(); i++ ){//for loop iterates through the command vector 
		vector<string> command_info = command_vector[i];//if statement checks for commands and then runs corresponding functions
		if (command_info[0] == "SRN"){
			srn(command_info, seat_vector, ALPHABET);
		}
		if (command_info[0] == "SSR"){
			ssr(command_info, seat_vector, ALPHABET, class_vec);
		}
		if (command_info[0] == "PRT"){
			string flight_num = command_vector[0][0];
			print_chart(seat_vector, ALPHABET, flight_num);//prints layout vector
		}
		if (command_info[0] == "UPL"){
			upl(freq_fly_vect, seat_vector,upgrade_vect_b,upgrade_vect_f);
			int x = 1;
			cout<<"The following passengers are scheduled to be upgraded to first class:"<<endl;
			for (unsigned int i =0; i< upgrade_vect_f.size(); i++){
				if (upgrade_vect_f[i] != "NO"){//if name is NO that means the passenger cancled so they dont get print
					for (unsigned int j = 0; j< seat_vector.size(); j++){
						for (unsigned int k = 0; k< seat_vector[j].size(); k++){
							if (upgrade_vect_f[i] != seat_vector[j][k]){//checks if the passenger is seated or not
								x =-1;//if the passenger isnt seated x =-1 and they are eligible for an upgrade
							}
						}	
					}
				}
				if (x<1){
					cout<<upgrade_vect_f[i]<<endl;//prints out those who are upgraded
				}
			}
			cout<<"The following passengers are scheduled to be upgraded to business class:"<<endl;
			for (unsigned int i =0; i< upgrade_vect_b.size(); i++){//same concept as above
				if (upgrade_vect_b[i] != "NO"){//same ish as the the first class
					for (unsigned int j = 0; j< seat_vector.size(); j++){
						for (unsigned int k = 0; k< seat_vector[j].size(); k++){
							if (upgrade_vect_b[i] != seat_vector[j][k]){
								x =-1;
							}
						}
					}	
				}
				if (x<1){
					cout<<upgrade_vect_b[i]<<endl;
				}
			}			
		}
		if (command_info[0] == "CXL"){
			cxl(command_info, seat_vector,upgrade_vect_b, upgrade_vect_f,freq_fly_vect);
		}
		if (command_info[0] == "UPP"){
			upp(upgrade_vect_b, upgrade_vect_f, seat_vector, ALPHABET);
		}
	}
return 0;	
}


