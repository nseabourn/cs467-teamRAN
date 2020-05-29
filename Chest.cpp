#include "Chest.hpp"

Chest::Chest(std::string nameIn, std::string descriptionIn, Interactable* keyIn) : Interactable(nameIn, descriptionIn), isLocked(true), key(keyIn) {
	type = 3;
}

bool Chest::getIsLocked(){
	return isLocked;
}

//returns item used to unlock it, or nullptr if not unlocked, or this if already unlocked
Interactable* Chest::unlock(std::vector<Interactable*> inventory){
	if(!isLocked){
		return this;
	}

	for(std::vector<Interactable*>::iterator it = inventory.begin(); it != inventory.end(); it++){
		if((*it) == key){
			isLocked = false;
			return key;
		}
	}

	return nullptr;
}


void Chest::addItem(Interactable* item){
	items.push_back(item);
}

std::vector<Interactable*> Chest::getItemsList() {
	return items;
}

void Chest::empty(){
	items.clear();
}

/*Chest::Chest(): Interactable{}, successString{"default"}, failString{"default"}, items{std::vector<Interactable*>{}}, isCorrect{false} {}

Chest::Chest(std::string name_, std::string desc, Room* r, Game* g, bool h, bool c):
	Interactable{std::string name_, std::string desc, Room* r, Game* g, h}, successString{"default"}, failString{"default"}, items{std::vector<Interactable*>{}}, isCorrect{c}  {}

void Chest::setSuccessString(std::string s){
	successString = s;
}

void Chest::setFailString(std::string s){
	failString = s;
}

void Chest::setIsOpen(bool c){
	isOpen = c;
}

std::string Chest::getSuccessString(){
	return successString;
}

std::string Chest::getFailString(){
	return failString;
}

std::string Chest::getCorrectAnswer(){
	return correctAnswer;
}

bool Chest::getIsOpen(){
	return isOpen;
}

bool addNeededItem(Interactable* i){
	std::set<Interactable*>::iterator it = neededItems.find(i);
	if(it != neededItems.end())
		return false;
	neededItems.insert(i);
	return true;
}

bool removeNeededItem(Interactable* i){
	std::set<Interactable*>::iterator it = neededItems.find(i);
	if(it == neededItems.end())
		return false;
	neededItems.erase(i);
	return true;	
}

std::set<Interactable*> getNeededItems(){
	return neededItems;
}

void setCombination(std::vector<int> arr){
	combination = arr;
}

std::vector<int> getCombination(){
	return combination;
}

bool addItemInside(Interactable* i){
	std::set<Interactable*>::iterator it = itemsInside.find(i);
	if(it != itemsInside.end())
		return false;
	itemsInside.insert(i);
	return true;
}

bool removeItemInside(Interactable* i){
	std::set<Interactable*>::iterator it = itemsInside.find(i);
	if(it == itemsInside.end())
		return false;
	itemsInside.erase(i);
	return true;	
}

std::vector<std::string> listItemsInside(){
	std::vector<std::string> vec;
	vec.reserve(itemsInside.size());
	for(int i=0; i<itemsInside.size(); i++){
		vec.push_back(itemsInside[i]->name);
	}
	return vec;
}

std::vector<std::string> Chest::listUserOptions(){
	if(!isOpen)
		return std::vector<std::string>{"Describe", "Try to Open"};
	else{
		return std::vector<std::string>{"Describe", "Take Item", "Leave Item"};
	}	
}

std::string Chest::callFunction(int n){
	if(!isOpen){
		switch(n){
			case 0:
				return longDesc;
				break;
			case 1:
				return tryOpen();
				break;
			default:
				return "You cannot do that.";
		}
	}

	else{
		switch(n){
			case 0:
				return longDesc;
				break;
			case 1:
				return takeItem();
				break;
			case 2:
				return leaveItem();
				break;
			default:
				return "You cannot do that.";
		}
	}
}

std::string tryOpen(){

}

std::string takeItem(){

}

std::string leaveItem(){

}*/
