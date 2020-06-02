#ifndef INTERACTABLE_hpp
#define INTERACTABLE_hpp

#include <curses.h>
#include <string>
#include <string.h>
#include <vector>
#include "common.hpp"
//#include "Room.hpp"
//#include "Game.hpp"

class Interactable{
protected:
	
	char* name;
	char* desc;
	int type; //refer to room template for type number
	/*std::string longDesc;
	Room* room; //points to the room this interactable is in. if null, interactable is held by player
	Room* originalRoom;
	bool holdable;*/
	//Game* game;
public:

	Interactable();
	Interactable(std::string, std::string);
	virtual ~Interactable();
	void setName(std::string);
	char* getName();
	void freeInteractable();
	char* getDescription();
	int getType();
	virtual bool accuse();
	virtual void question();
	virtual Interactable* unlock(std::vector<Interactable*>);
	virtual bool getIsLocked();
	virtual void empty();
	virtual void addItem(Interactable*);
	virtual Interactable* solve(char*); 
	bool take();
	virtual void frisk();
	virtual std::vector<Interactable*> getItemsList();
	virtual void eat();
	/*Interactable(std::string name_, std::string desc, Room* r, bool h);
	void setName(std::string name_);
	void setShortDesc(std::string desc);
	void setLongDesc(std::string desc);
	void setRoom(Room* r);
	void setOriginalRoom(Room* r);
	void setHoldable(bool h);
	//void setGame(Game* g);
	std::string getShortDesc();
	virtual std::string getLongDesc();
	Room* getRoom();
	Room* getOriginalRoom();
	bool getHoldable();
	//Game* getGame();
	virtual std::vector<std::string> listUserOptions(); //send list of things the user can do. the index of the action is what is used in calling callFunction
	virtual std::string callFunction(int n); //calls the function that the user chose*/
};

#endif
