#include <fstream>
#include <iostream>
#include <string>
#include "SongLibrary.h"

/*
CSCI-1200 Homework 5 Main File
Written by Buster O. Holzbauer
Spring 2017

Consult SongLibrary.h for typedefs of GroupID, LibraryNode, GroupListNode
DO NOT EDIT ANYTHING IN THIS FILE!
*/

//Input parsing
bool ReadLibraryFromFile(LibraryNode*& library, char* library_filename);
std::istream& ReadSongFromInput(std::istream& input, std::string& artist, 
                                std::string& title, std::string& album,
                                unsigned int& year, Song& song);

//Library Functions
bool AddToLibrary(LibraryNode*& library, const Song& song);
LibraryNode* SongExists(LibraryNode* library, const Song& song);
LibraryNode* SongExists(LibraryNode* library, const Song& song, std::ostream& out);

int main(int argc, char** argv){
	LibraryNode* library = NULL; //Head of library
	GroupListNode* song_groups = NULL; //Head of song_groups

	if(argc!=6){
		std::cerr << "Proper usage is: " << argv[0] << " [library file] [command"
							<< " file] [library output] [song group output] [print output]" 
              << std::endl;
		return -1;
	}

	std::ofstream library_output(argv[3]);
	if(!library_output){
		std::cerr << "Couldn't open " << argv[3] << " for writing." << std::endl;
		return -1;
	}

	std::ofstream song_group_output(argv[4]);
	if(!song_group_output){
		std::cerr << "Couldn't open " << argv[4] << " for writing." << std::endl;
		return -1;
	}

	std::ofstream print_output(argv[5]);
	if(!print_output){
		std::cerr << "Couldn't open " << argv[5] << " for writing." << std::endl;
		return -1;
	}

	if(ReadLibraryFromFile(library,argv[1])){
		std::cout << "Successfully read in library." << std::endl;
	}
	else{
		std::cerr << "Error reading in library." << std::endl;
		return -1;
	}

	std::ifstream command_input(argv[2]);
	if(!command_input){
		std::cerr << "Couldn't open " << argv[2] << " for reading." << std::endl;
		return -1;
	}

	//Steady state - let's parse input
	std::string command;
	std::string artist;
	std::string title;
	std::string album;
	unsigned int year;
	std::string dummy; //Just to eat up extra \n characters.
	Song song;
	bool invalid_flag = false;

	while(std::getline(command_input,command)){
		if(command == "add_to_library"){
			ReadSongFromInput(command_input,artist,title,album,year,song);	//Read in the song
			LibraryNode* library_ptr = SongExists(library,song);
			if(library_ptr){
				library_output << "Song already in library" << std::endl;
			}
			else{
				AddToLibrary(library,song);
				library_output << "Library now contains song: " << song;
			}
		}
		else if(command == "next_in_library"){
			ReadSongFromInput(command_input,artist,title,album,year,song);
			LibraryNode* library_ptr = SongExists(library,song);
			if(!library_ptr){
				library_output << "Couldn't find a matching song." << std::endl;
			}
			else if(library_ptr->ptr){
				library_output << "The next song is: " << library_ptr->ptr->value;
			}
			else{
				library_output << "There are no songs after this one in the library." << std::endl;
			}
		}
		else if(command == "song_exists"){
			ReadSongFromInput(command_input,artist,title,album,year,song);
			if(SongExists(library,song)){
				library_output << "Found the following song in the library: " << song;
			}
			else{
				library_output << "Couldn't find a matching song." << std::endl;
			}
		}
		else if(command == "make_group"){
			GroupID group_num;
			command_input >> group_num;
			std::getline(command_input,dummy);

			if(GroupExists(song_groups,group_num)){
				song_group_output << "Group " << group_num << " already exists." << std::endl;
			}
			else{
				MakeGroup(song_groups, group_num);
				song_group_output << "Added group ID " << group_num << std::endl;
			}
		}
		else if(command == "group_exists"){
			GroupID group_num;
			command_input >> group_num;
			std::getline(command_input,dummy);

			GroupListNode* list_ptr = GroupExists(song_groups,group_num);
			if(list_ptr){
				song_group_output << "List " << group_num << " exists." << std::endl;
			}
			else{
				song_group_output << "No group exists with ID " << group_num << std::endl;
			}
		}
		else if(command == "song_in_group"){
			ReadSongFromInput(command_input,artist,title,album,year,song);
			GroupID group_num;
			command_input >> group_num;
			std::getline(command_input,dummy);
			
			GroupListNode* list_ptr = GroupExists(song_groups,group_num);
			if(!list_ptr){
				song_group_output << "There is no group with ID " << group_num << std::endl;
			}
			else if(SongInGroup(list_ptr->value,song)){
				song_group_output << "In group ID " << group_num << " found song: " << song;
			}
			else{
				song_group_output << "Song was not in group ID " << group_num << std::endl;
			}			
		}
		else if(command == "add_to_group"){
			ReadSongFromInput(command_input,artist,title,album,year,song);
			GroupID group_num;
			command_input >> group_num;
			std::getline(command_input,dummy);

			LibraryNode* library_ptr = SongExists(library,song);
			GroupListNode* list_ptr = GroupExists(song_groups,group_num);
			if(!library_ptr){
				song_group_output << "No matching song in the library." << std::endl;
			}
			else if(!list_ptr){
				song_group_output << "There is no group with ID " << group_num << std::endl;
			}
			else if(library_ptr->value.usedInList()){
				song_group_output << "That song is already in a song group!" << std::endl;
			}
			else{
				AddToGroup(library_ptr, list_ptr);
				song_group_output << "Added a song to group ID " << group_num << ": " << song;
			}
		}
		else if(command == "remove_from_group"){
			ReadSongFromInput(command_input,artist,title,album,year,song);

			LibraryNode* library_ptr = SongExists(library,song);
			if(!library_ptr){
				song_group_output << "Could not find a song by that name in the library." << std::endl;
			}
			else if(library_ptr->value.getSongGroupPointer() == NULL){
				song_group_output << "Could not find a group with that song used." << std::endl;
			}
			else{
				//Need the group number for our output
				GroupID group_num = library_ptr->value.getSongGroupPointer()->id;
				RemoveFromGroup(library_ptr,song_groups);
				song_group_output << "Succesfully removed the following song from group " << group_num << ": " << song;
			}
		}
		else if(command == "combine_groups"){
			GroupID group_num1,group_num2;
			command_input >> group_num1 >> group_num2;
			std::getline(command_input,dummy);
			GroupListNode* list_ptr1 = GroupExists(song_groups,group_num1);
			GroupListNode* list_ptr2 = GroupExists(song_groups,group_num2);
			if(!list_ptr1){
				song_group_output << "Could not find a group with ID " << group_num1 << std::endl;
			}
			else if(!list_ptr2){
				song_group_output << "Could not find a group with ID " << group_num2 << std::endl;
			}
			else{
				CombineGroups(song_groups,list_ptr1,list_ptr2);
				song_group_output << "Merged group ID " << group_num2 << " into group ID " << group_num1 << std::endl;
			}
		}
		else if(command == "remove_group"){
			GroupID group_num;
			command_input >> group_num;
			std::getline(command_input,dummy);

			GroupListNode* list_ptr = GroupExists(song_groups,group_num);
			if(!list_ptr){
				song_group_output << "Could not find a group with ID " << group_num << std::endl;
			}
			else{
				RemoveGroup(song_groups,list_ptr);
				song_group_output << "Removed group " << group_num << std::endl;
			}
		}
		else if(command == "print_library"){
			PrintLibrary(library,print_output);
		}
		else if(command == "print_group_sequential"){
			GroupID group_num;
			command_input >> group_num;
			std::getline(command_input,dummy);
			GroupListNode* list_ptr = GroupExists(song_groups,group_num);
			if(!list_ptr){
				print_output << "Could not find group ID " << group_num << std::endl;
			}
			else{
				PrintGroupSequential(list_ptr->value,print_output);
			}
		}
		else if(command == "print_group_rewind"){
			ReadSongFromInput(command_input,artist,title,album,year,song);
			GroupID group_num;
			command_input >> group_num;
			std::getline(command_input,dummy);

			LibraryNode* library_ptr = SongExists(library,song);
			if(!library_ptr){
				print_output << "No match found in library." << std::endl;
			}
			else if(!library_ptr->value.usedInList() || library_ptr->value.getSongGroupPointer()->id != group_num){
				print_output << "Song is not used in a group with ID " << group_num << std::endl;
			}
			else{
				PrintGroupRewind(library_ptr->value.getSongGroupPointer(),print_output);
			}
		}
		else if(command == "print_group_marathon"){
			ReadSongFromInput(command_input,artist,title,album,year,song);
			GroupID group_num;
			command_input >> group_num;
			std::getline(command_input,dummy);

			LibraryNode* library_ptr = SongExists(library,song);
			if(!library_ptr){
				print_output << "No match found in library." << std::endl;
			}
			else if(!library_ptr->value.usedInList() || library_ptr->value.getSongGroupPointer()->id != group_num){
				print_output << "Song is not used in a group with ID " << group_num << std::endl;
			}
			else{
				PrintGroupMarathon(library_ptr->value.getSongGroupPointer(),print_output);
			}
		}
		else if(command == "print_longest_group_rewind"){
			GroupID group_num;
			command_input >> group_num;
			std::getline(command_input,dummy);

			GroupListNode* list_ptr = GroupExists(song_groups,group_num);
			if(!list_ptr){
				print_output << "No group with ID " << group_num << std::endl;
			}
			else{
				PrintLongestGroupRewind(list_ptr,print_output);
			}
		}
		else{
			std::cerr << "Invalid command: " << command << std::endl;
			invalid_flag = true;
			break;
		}
	}


	//Execution complete, need to clean up
	//Delete song groups
	DeleteAllSongGroups(song_groups);

	//Delete library
	LibraryNode* library_itr = library;
	while(library_itr != NULL){
		LibraryNode* curr_library_itr = library_itr;
		library_itr = library_itr->ptr;
		delete curr_library_itr;
	}

	if(invalid_flag){
		return -1;
	}
	return 0;
}

bool ReadLibraryFromFile(LibraryNode*& library, char* library_filename){
	std::ifstream library_input(library_filename);
	if(!library_input){
		std::cerr << "Couldn't open " << library_filename << " for reading." << std::endl;
		return false;
	}

	if(library){
		std::cerr << "Cannot read library file into pre-filled library" << std::endl;
		return false;
	}

	library = NULL;
	LibraryNode* curr = library;

	std::string artist;
	std::string title;
	std::string album;
	unsigned int year;
	Song song;
	while(ReadSongFromInput(library_input,artist,title,album,year,song)){
		if(!curr){
			//First node
			curr = new LibraryNode;
			curr->ptr = NULL;
			library = curr;
		}
		else{
			curr->ptr = new LibraryNode;
			curr = curr->ptr;
			curr->ptr = NULL;
		}
		curr->value = song;
	}

	return true;
}

std::istream& ReadSongFromInput(std::istream& input,	std::string& artist,
                                std::string& title, std::string& album,
                                unsigned int& year, Song& song){
	if(std::getline(input,artist)){
		std::getline(input,title);
		input >> year;
		std::getline(input,album); //Consume extra \n left by >> read.
		std::getline(input,album);
		song = Song(title,artist,album,year);
	}
	return input;
}

LibraryNode* SongExists(LibraryNode* library, const Song& song){
	LibraryNode* ret = library;
	for(; ret!=NULL; ret = ret->ptr){
		if(song == ret->value){
			break;
		}
	}

	//Didn't find song
	return ret;
}

bool AddToLibrary(LibraryNode*& library, const Song& song){
	if(SongExists(library,song)){
		return false;
	}
	else{
		if(!library){
			//Empty library!
			library = new LibraryNode;
			library->ptr = NULL;
			library->value = song;
		}
		else{
			//Find+Add to tail
			LibraryNode* head = library;
			LibraryNode* oneafter = head->ptr;
			while(oneafter != NULL){
				oneafter = oneafter->ptr;
				head = head->ptr;
			}
			head->ptr = new LibraryNode;
			head->ptr->value = song;
			head->ptr->ptr = NULL;
		}
		return true;
	}
}
