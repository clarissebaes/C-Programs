/*
Homework 5 supporting classes
Written by Buster O. Holzbauer, Spring 2017
DO NOT CHANGE ANY OF THE CODE IN THIS FILE!!!
*/

#include <string>
#include <iostream>
#include <cassert>

#ifndef DS_S17_SONG_
#define DS_S17_SONG_

typedef unsigned int GroupID; //ID numbers for lists

class SongGroupNode; //Forward declaration

//Small templated class to make singly-linked lists
template <class T>
class Node{
public:
	Node<T>* ptr;
	T value;
};

//Song class each object represents a song.
class Song{
public:
	Song(){} //Default does nothing
 	Song(const std::string& title, const std::string& artist, 
       const std::string& album, unsigned int year);

	//Accessors
	const std::string& getTitle() const {	return title; }
	const std::string& getArtist() const {	return artist; }
	const std::string& getAlbum() const {	return album; }
	unsigned int getYear() const {	return year; }
	bool usedInList() const { return used; }
	SongGroupNode* getSongGroupPointer() const { return song_group_ptr; }

	//Modfiers
	void updateSongGroupPointer(SongGroupNode* ptr);
	void setUsedInGroup(bool val) {used = val;}

private:
	std::string title; //Name of the song
	std::string artist; //Artist / Band name
	std::string album; //Album name
	unsigned int year; //Year song was written
  bool used; //True if the song is in a playlist, false otherwise
	SongGroupNode* song_group_ptr; //Point to the songlist node, NULL if I don't have one
};

bool operator== (const Song& s1, const Song& s2);
std::ostream& operator<< (std::ostream& ostr, const Song& song);

//SongGroups are special double/quadruple-linked lists made up of one or more SongGroupNode
class SongGroupNode{
public:
	SongGroupNode* next_song_ptr; //Next song by order added
	SongGroupNode* prev_song_ptr; //Prev song by order added
	SongGroupNode* next_by_artist_ptr; //Next song by the same artist, in order added
	SongGroupNode* prev_by_year_ptr; //Previous song in list with an earlier year
	Node<Song>* m_song; //Pointer to a song
 	GroupID id; //Numeric list ID
};

typedef Node<Song> LibraryNode; //For song library nodes
typedef Node<SongGroupNode*> GroupListNode; //For keeping the heads of songlists

//////////////////////////////Function Prototypes to make things easier///////////

//Playlist Creation/Update
GroupListNode* GroupExists(GroupListNode* song_groups, GroupID id);
void MakeGroup(GroupListNode*& song_groups, GroupID id);
bool SongInGroup(SongGroupNode* group_head, const Song& song);
void AddToGroup(LibraryNode* library_ptr, GroupListNode* list_ptr);
void RemoveFromGroup(LibraryNode* library_ptr, GroupListNode* song_groups);
void CombineGroups(GroupListNode*& song_groups, GroupListNode*& list_ptr1, GroupListNode*& list_ptr2);
void RemoveGroup(GroupListNode*& song_groups, GroupListNode* list_ptr);
void RecomputePrevByYear(GroupListNode* list_ptr);


//Printing
void PrintLibrary(LibraryNode* library_head,std::ostream& print_file);
void PrintGroupSequential(SongGroupNode* group_head,std::ostream& print_file);
void PrintGroupRewind(SongGroupNode* group_ptr,std::ostream& print_file);  //Need a starting song
void PrintGroupMarathon(SongGroupNode* group_ptr,std::ostream& print_file); //Need a starting song
void PrintLongestGroupRewind(GroupListNode* group_head,std::ostream& print_file);

//Delete
void DeleteAllSongGroups(GroupListNode*& song_groups);
#endif
