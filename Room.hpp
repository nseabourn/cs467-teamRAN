#ifndef ROOM_hpp
#define ROOM_hpp

#include <curses.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <set>
#include "common.hpp"
#include "Interactable.hpp"

//had to use forward declaration since Room and Interactable include eachother
//class Interactable;

class Room{
private:
	int roomNumber;
	Room* north;
	Room* east;
	Room* south;
	Room* west;
	char* longDescription;
	char* shortDescription;
	std::vector<std::string> travelCommands;
	bool visitedBefore;
	std::vector<Interactable*> items;

	int numberItems;
	//std::set<Interactable*> items;

public:
	Room();
	void connectUp(Room*);
	void connectRight(Room*);
	void connectDown(Room*);
	void connectLeft(Room*);
	void setRoomNumber(int);
	int getRoomNumber();
	void setLongDescription(std::string);
	void setShortDescription(std::string);
	std::vector<std::string> getTravelCommandsVector();
	void addTravelCommand(std::string);
	Room* getNorthRoom();
	Room* getEastRoom();
	Room* getSouthRoom();
	Room* getWestRoom();
	int getTravelVectorPosition(std::string);
	int getItemsListPosition(std::string);
	void addInteractable(Interactable*);
	bool removeInteractable(Interactable*);
	std::vector<Interactable*> getItemsList();
	int getNumberItems();
	void freeRoom();

	void printLongDescription();
	void printDescription();

};

#endif