#include <fstream>
#include <iostream>
#include <string>
#include <typeinfo>
#include "SongLibrary.h"
using namespace std;

//////////////////DO NOT CHANGE THIS CODE////////////////////////

//Construct a Song object with values
Song::Song(const string& title, const string& artist, 
     const string& album, unsigned int year){
	this->title = title;
	this->artist = artist;
	this->album = album;
	this->year = year;
	used = false;
	this->song_group_ptr = NULL;
}

//Song equality doesn't depend on pointers or being used
bool operator== (const Song& s1, const Song& s2){
	return (s1.getYear() == s2.getYear()) && (s1.getTitle() == s2.getTitle())
          && (s1.getAlbum() == s2.getAlbum()) && (s1.getArtist() == s2.getArtist());
}

//Modifier for group pointer
void Song::updateSongGroupPointer(SongGroupNode* ptr){
	if(ptr){
		//Check that ptr is actually for this Song.
		assert(ptr->m_song->value == *this); 
		song_group_ptr = ptr;
	}
	else{
		song_group_ptr = NULL;
	}
}

//Make output easier by overload operator<<
ostream& operator<< (ostream& ostr, const Song& song){
	if(!song.getSongGroupPointer()){
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
	       << song.getAlbum() << "\" (" << song.getYear() << ")" << endl;
	}
	else{
		ostr << "\"" << song.getTitle() << "\" by " << song.getArtist() << " on \"" 
		<< song.getAlbum() << "\" (" << song.getYear() << ")" << " in Song Group "
		<< song.getSongGroupPointer()->id << endl;
	}
	return ostr;
}

/////////////////////////YOUR CODE STARTS HERE/////////////////////////////////


//////////////////////////////GROUP FUNCTIONS/////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are searching for
BEHAVIOR:
None
RETURN: 
NULL if no list matches the ID, otherwise returns the GroupListNode* containing
the head of the list with ID id.
*/
GroupListNode* GroupExists(GroupListNode* song_groups, GroupID id){
	GroupListNode* ret = song_groups;
	for(;ret!=NULL; ret = ret -> ptr){//runs through the list of group heads
		if (id == ret->value->id){//checks if the id matches up
			return ret;//if it does the group exist already and it returns the head of that list
		}
	}

return NULL;//if it doesnt exist it returns null


}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-id is the ID of the list we are creating
BEHAVIOR:
Add a new song group to song_groups, give the new song group ID id. Order of
song groups is not guaranteed.
RETURN:
None
*/
void MakeGroup(GroupListNode*& song_groups, GroupID id){
	//MakeGroup makes groups who knew
	SongGroupNode* new_node = new SongGroupNode;
		//sets all the pointer to NULL
	new_node-> next_song_ptr = NULL;
	new_node-> prev_song_ptr = NULL;
	new_node-> next_by_artist_ptr = NULL;
	new_node-> prev_by_year_ptr = NULL;
	new_node -> m_song = new Node<Song>;
	new_node -> m_song->ptr = NULL;
	new_node -> m_song->value = Song();
	SongGroupNode* ptrz =NULL;
	new_node -> m_song->value.updateSongGroupPointer(ptrz);
	new_node -> id = id;
	cout<<"size: "<<sizeof(*new_node)<<endl;


	if(!song_groups){//checks if the list of heads exist
		song_groups = new GroupListNode;//creates new group head node
		song_groups -> ptr = NULL;//sets pointers to NULL
		song_groups -> value = NULL;
		song_groups -> value = new_node;

	}
	else{//if the group of heads exist
		GroupListNode* head = song_groups;
		GroupListNode* oneafter = head->ptr;
		while(oneafter != NULL){//iterates through the head list
			oneafter = oneafter->ptr;
			head = head->ptr;
		}
		head->ptr = new GroupListNode;// creats the new head
		head->ptr->value = new_node;//adds the new songgroupnode to the list
		head->ptr->ptr = NULL;
	}
	delete ptrz;
}


/*
ARGUMENTS:
-group_head points to the head of a song group
-song is the Song we are checking the group for
BEHAVIOR:
None
RETURN:
If song is found in the group return true. If song is not found,
return false.
*/
bool SongInGroup(SongGroupNode* group_head, const Song& song){
	SongGroupNode* song_node = group_head;
	while(song_node->next_song_ptr != NULL){//iterates through the song group list
		song_node = song_node->next_song_ptr;
		if(song_node->m_song->value == song){
			//checks if the current song is the same as the inputed song
			return true;
		}
	}
	return false;
}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* node of type song containing the Song we want to add.
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Modify the group pointed to by list_ptr to reflect that the song is in the group.
This may change the length of the list. Modifies the Song's members as well.
RETURN:
None
*/
void AddToGroup(LibraryNode* library_ptr, GroupListNode* list_ptr){
	SongGroupNode* cur_song = list_ptr->value;
	if(!SongInGroup(list_ptr->value,library_ptr->value)){//checks if the song is already in the group
		int counter = 0;
		cout<<"check 1"<<endl;
		while (cur_song -> next_song_ptr != NULL){
			counter++;
			//goes to the end of the list
			cur_song = cur_song->next_song_ptr;
		}
		//creates the new node that you'll add and sets all the pointers to NULL
		SongGroupNode* new_node = new SongGroupNode;
		new_node->m_song = library_ptr;
		(new_node->m_song ->value).setUsedInGroup(true);
		new_node->next_song_ptr=NULL;
		new_node->prev_song_ptr=cur_song;
		new_node->next_by_artist_ptr =NULL;
		new_node->prev_by_year_ptr =NULL;
		new_node->id = list_ptr->value->id;
		(new_node->m_song->value).updateSongGroupPointer(new_node);
		//re-assigns the next by artist pointers 		
		SongGroupNode* comp_song = cur_song->prev_song_ptr;
		//comp song travers the list so you can compare the artist of the current song
		//to the artist of all the existing songs in the list
		while(comp_song!=NULL && comp_song->m_song->ptr != NULL){
			//checks if the artist are the same, if they are it sets the next by artist pointers
			if((comp_song->m_song->value).getArtist() == (cur_song->m_song->value).getArtist()){
				comp_song->next_by_artist_ptr = cur_song;
				RecomputePrevByYear(list_ptr);
				break;
			}
			comp_song = comp_song->prev_song_ptr;//incraments the comp song to the next prev song
		}
		comp_song = new_node->prev_song_ptr;
		//reassigns the prev by year pointers
		while(comp_song!=NULL && comp_song->m_song->ptr != NULL){
			if((comp_song->m_song->value).getYear() < (new_node->m_song->value).getYear()){
				new_node->prev_by_year_ptr = comp_song;
				RecomputePrevByYear(list_ptr);
				break;
			} 
			comp_song = comp_song->prev_song_ptr;
		}

	RecomputePrevByYear(list_ptr); //points to the new node
	if(cur_song->m_song->value.getSongGroupPointer()==NULL){
		cout<<"CHECK BOOIIIIISS: "<< counter<<endl;
		delete (list_ptr->value->m_song->value.getSongGroupPointer());
		// delete list_ptr->value;
		// delete cur_song;
		// list_ptr->value = new_node;
		cur_song->next_song_ptr = new_node;
		delete new_node;
		
	}
	else{
		cur_song->next_song_ptr = new_node;
		cout<<"check 2"<<endl;
		delete new_node;
	}
}
}

/*
ARGUMENTS:
-library_ptr points to the LibraryNode* containing the Song we w
RETURN:
Noneant to remove from a group.
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Modifies the Song's member variables to reflect that it is not in a group. Modifies the group
so that the Song is not in the group. This function may cause song_groups to be modified as well.
RETURN:
None
*/
void RemoveFromGroup(LibraryNode* library_ptr, GroupListNode* song_groups){
	GroupID wanted_song_id = (library_ptr->value.getSongGroupPointer())->id; //gets the song id
	GroupListNode* head= song_groups;
		while(head != NULL){ //checks for the end of the head linked list
			if(wanted_song_id == head->value->id){//checks if the group id is the same as the song id
				//if the ids match the song is in that group
				SongGroupNode* cur_song = head->value;
				while (cur_song!= NULL){//iterates through the song group nodes
					if(cur_song -> m_song->value.getTitle() == library_ptr->value.getTitle()){//checks if the titles are the same
						SongGroupNode* comp_song = cur_song->prev_song_ptr;
						//reassigns the next by artist pointers
						while (comp_song!=NULL && comp_song->m_song->ptr != NULL){
							if(comp_song->m_song->value.getArtist()==cur_song->m_song->value.getArtist()){
								//checks if the aritist of the comp song,which traverses the list is the same as the current song
								comp_song->next_by_artist_ptr=cur_song->next_by_artist_ptr;
								//if it does it reassigns the pointer
								break;
							}
							comp_song=comp_song->prev_song_ptr;// incraments the comp song so it traverses the entire list
						}
						if(cur_song->prev_song_ptr!=NULL){//makes sure its not the first song
							//reassigns the previous songs next song pointer to the song you want to deletes next song
							cur_song->prev_song_ptr->next_song_ptr = cur_song->next_song_ptr;
						}
						else{//if it is the first then it just sets the next songs prev pointer to null
							cur_song->next_song_ptr->prev_song_ptr = NULL;
						}
						if(cur_song->next_song_ptr!=NULL){//makes sure its not the end song node
							//reassigns the next song's prev song ptr to the song you want to deletes previous song
							cur_song->next_song_ptr->prev_song_ptr = cur_song->prev_song_ptr;
						}
						else{//if it is the end song then it sets the previous songs next song pointer to null
							cur_song->prev_song_ptr->next_song_ptr=NULL;
						}
						RecomputePrevByYear(head);
						cur_song->m_song->value.setUsedInGroup(false);//sets its used in group bool to false
						delete cur_song->m_song;
						delete cur_song;
						break;
					}
				cur_song = cur_song->next_song_ptr;
				}
				RecomputePrevByYear(head);
				break;
			}

			head = head->ptr;
		}
}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-list_ptr1 contains to the song group head of Group A
-list_ptr2 contains the song group head of Group B
BEHAVIOR:
Modify Group A so that at the end of its songs, the songs of Group B are added in the same
order they were found in Group B. Remove the now-empty Group B.
*/
void CombineGroups(GroupListNode*& song_groups, GroupListNode*& list_ptr1, GroupListNode*& list_ptr2){
	GroupListNode* ahead = list_ptr1;
	GroupListNode* bhead = list_ptr2;
	SongGroupNode* b_song_node = list_ptr2 ->value;
	while(b_song_node->next_song_ptr != NULL){//iterates through song group b
		AddToGroup(b_song_node->m_song, ahead);//adds each song group node from b to the end of a
		b_song_node=b_song_node->next_song_ptr;
	}
	RemoveGroup(song_groups,bhead);//deletes song group list b

}

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
-list_ptr is the head of the song group we want to remove.
BEHAVIOR:
Remove the group from the list of song groups. No Song objects should remain associated with the
group, and the function should modify Song member variables appropriately to reflect this. Any
memory associated with the group must be released.
RETURN:
None
*/
void RemoveGroup(GroupListNode*& song_groups, GroupListNode* list_ptr){
	GroupListNode* currenthead = song_groups;
	GroupListNode* prevhead = NULL;//since the head list is singly link you need to keep track of the prev node
	SongGroupNode* current_song = list_ptr -> value;
	while(currenthead!=list_ptr){//iterates through the head list till you get to the head of the list you want to delete
		prevhead = currenthead;
		currenthead = currenthead -> ptr;
	}
	while(current_song!= NULL && current_song->m_song->ptr != NULL){
		RemoveFromGroup(current_song->m_song , song_groups);//removes each song group node with in the lsit
		SongGroupNode* next_current_song = current_song->next_song_ptr;
		delete current_song;
		current_song = next_current_song;//iterates through the list
	}
	//delete currenthead->value->m_song->value;
	delete currenthead->value->m_song;
	delete currenthead->value;
	if(prevhead!=NULL){//makes sure its not the first head list
		prevhead->ptr = currenthead-> ptr;
	}
	else if(prevhead == NULL){//if it is the first head node
		song_groups = currenthead ->ptr;
	}
	delete currenthead;
}

/*
ARGUMENTS:
-list_ptr is the head of the song group we want to add the song to.
BEHAVIOR:
Recompute all prev_by_year_ptr members in the song group pointed to by
list_ptr.
RETURN:
None
*/
void RecomputePrevByYear(GroupListNode* list_ptr){
	SongGroupNode* head = list_ptr->value;
	while(head->next_song_ptr!=NULL){//iterates through the list till you get to the end
		head = head->next_song_ptr;
	}
	SongGroupNode* shittyNode = head->prev_song_ptr;
	while(shittyNode !=NULL){//iterates backwards in the list
		SongGroupNode* backwards =shittyNode->prev_song_ptr;
		while(backwards != NULL && backwards->m_song->ptr != NULL){
			if(shittyNode->m_song->value.getYear()>backwards->m_song->value.getYear()){
				//checks if the year is the same if it is then it reassigns the prev_by year ptr
				shittyNode->prev_by_year_ptr = backwards;
				shittyNode = shittyNode->prev_song_ptr;
				break;
			}
			backwards = backwards ->prev_song_ptr;
		}
		shittyNode =shittyNode->prev_song_ptr; 
	}
}

////////////////////////////PRINT FUNCTIONS////////////////////////////////////

/*
ARGUMENTS:
-library_head points to the first LibraryNode* of the song library
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the library in the order it was added.
RETURN:
None
*/
void PrintLibrary(LibraryNode* library_head,ostream& print_file){
	LibraryNode* song_node = library_head;
	int counter =0;//keeps track of number of songs
	while(song_node!=NULL){
		counter++;
		print_file<<song_node->value;//prints out song info
		song_node = song_node ->ptr;//iterates throug the library

	}
	print_file<<"Library contains "<<counter<<" song(s)"<<endl;
}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to print
-print_file points to an ostream to print output to
BEHAVIOR:
Print each song in the group in the order it was added.
RETURN:
None
*/
void PrintGroupSequential(SongGroupNode* group_head,ostream& print_file){
	print_file<<"List ID "<<group_head->id<<" contains:"<<endl;
	SongGroupNode* song_node = group_head;
	int counter = -1;
	while(song_node!=NULL){
		counter++;
		if(counter>0){//skips the first dummy node
			print_file<<song_node -> m_song->value;//prints out the song
		}
		song_node = song_node->next_song_ptr;//iterates through the song group
	}
	print_file<<counter<<" song(s)"<<endl;
	
}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR:
Print a rewind list by following the prev_by_year_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupRewind(SongGroupNode* group_ptr,ostream& print_file){
	SongGroupNode* head = group_ptr;//this funct prints out the rewind play list
	print_file<<"Rewind list for "<<head->m_song->value.getYear()<<endl;
	int counter = 0;
	while(head!=NULL){
			counter++;
			print_file<<"	#"<<counter<<": "<<head->m_song->value;
			head = head->prev_by_year_ptr;//iterates back through the list using the prev by year ptr
		}
	print_file<<"Rewind list contained "<<counter<< " song(s)."<<endl;


}

/*
ARGUMENTS:
-group_ptr points to the location in a particular song group to start printing from
-print_file points to an ostream to print output to
BEHAVIOR: 
Print a rewind list by following the next_by_artist_ptr pointers, starting from the song
pointed to by group_ptr.
RETURN:
None
*/
void PrintGroupMarathon(SongGroupNode* group_ptr,ostream& print_file){
	SongGroupNode* head = group_ptr; //prints out te list of the artist marathon
	print_file<<"Marathon list for "<<head->m_song->value.getArtist()<<endl;
	int counter = 0;
	while(head!=NULL){
			counter++;
			print_file<<"	#"<<counter<<": "<<head->m_song->value;
			head = head->next_by_artist_ptr;//iterates by the previous artist
		}
	print_file<<"Marathon list contained "<<counter<< " song(s)."<<endl;


}

/*
ARGUMENTS:
-group_head points to the first SongGroupNode* of the group to analyze
-print_file points to an ostream to print output to
BEHAVIOR:
Find the rewind list with the most songs in the song group pointed to by group_head.
Print the rewind list and the song count to print_file.
RETURN:
None
*/
void PrintLongestGroupRewind(GroupListNode* group_head,ostream& print_file){
	int max_count = -1; //longest rewind list prints
	SongGroupNode* maxStartNode = NULL; //keeps track of the start node of the longest list
	SongGroupNode* head = group_head->value;
	while(head->next_song_ptr!=NULL){//goes to the end of the list
		head = head->next_song_ptr;
	}
	while(head!=NULL){
		int temp_count = 0;//counts how many song
		SongGroupNode* tempStartNode = head; //temp start node
		SongGroupNode* backwards = head;
		while(backwards !=NULL){
			temp_count++;
			backwards = backwards->prev_by_year_ptr;
		}
		if (max_count<temp_count){ //if the temp count is higher than max count
			maxStartNode = tempStartNode; //redefines the maxstart node as the current temp node
			max_count = temp_count;
		}
		head = head->prev_song_ptr;
	}
	print_file<<"Maximum size rewind list is for year "<<maxStartNode->m_song->value.getYear()<<endl;
	int counter = 0;//prints out the list of songs
	while(maxStartNode!=NULL){
			counter++;
			print_file<<"	#"<<counter<<": "<<maxStartNode->m_song->value;
			maxStartNode = maxStartNode->prev_by_year_ptr;
	}
	print_file<<"Longest rewind list contained "<<counter<< " song(s)."<<endl;



//starting node
//comparing counter

 
}

///////////////////////////////CLEANUP/////////////////////////////////////////

/*
ARGUMENTS:
-song_groups points to a singly-linked list of song group heads
BEHAVIOR:
Delete every group. Do not leak. Modifies all groups and the song_groups list.
Update every Song to reflect not being in a group.
RETURN:
None
*/
void DeleteAllSongGroups(GroupListNode*& song_groups){
	GroupListNode* temp = song_groups;
	GroupListNode* tempx;
	while(temp!=NULL){
		tempx = temp->ptr; //keeps track of what temp is pointing since you delete temp
		RemoveGroup(song_groups, temp);//removes the group
		temp = tempx;//sets temp to what temp was pointing to
	}
	delete tempx;
}