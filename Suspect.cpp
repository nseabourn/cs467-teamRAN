#include "Suspect.hpp"

Suspect::Suspect(): isMurderer(false) {
	type = 1;
}

Suspect::Suspect(std::string nameIn, std::string descriptionIn, bool isGuilty, std::string answerIn) : Interactable(nameIn, descriptionIn), isMurderer(isGuilty) {
	type = 1;
	answer = new char[1000];
	strcpy(answer, answerIn.c_str());
}

Suspect::~Suspect(){
	delete[] answer;
}

void Suspect::question(){
	wclear(win);
	wmove(win, 0, 0);
	wprintw(win, answer);
	wmove(win, 1, 0);
}

bool Suspect::accuse() {
	if (isMurderer) {
		wclear(win);
		wmove(win, 0, 0);
		wprintw(win, "Congratulations! You accused the correct person!");
	}
	else {
		wclear(win);
		wmove(win, 0, 0);
		wprintw(win, "Sorry! They were not the murderer!");
	}
	return true;
}

void Suspect::frisk(){
	if (isMurderer){
		wmove(win, 0, 0);
		wprintw(win, "After frisking the suspect, you found a knife covered in blood.");
	} else {
		wmove(win, 0, 0);
		wprintw(win, "You did not find anything.");
	}
}
/*
Suspect::Suspect(bool m, std::string name_, std::string desc, Room* r, Game* g):
	Interactable{name_, desc, r, g, false}, isMurderer{m}{}

std::string Suspect::getDesc(){
	//will send a concatenation of the suspects details
	return "";
}

bool Suspect::getIsMurderer(){
	return isMurderer;
}

void Suspect::setIsMurderer(bool m){
	isMurderer = m;
}

std::string Suspect::accuse(){
	game->setGameOverStatus(true);
	if(isMurderer){
		return "You chose correctly.";
	}
	else{
		return "You chose incorrectly.";
	}
}

std::vector<std::string> Suspect::listUserOptions(){
	return std::vector<std::string>{"Describe", "Accuse"};
}

std::string Suspect::callFunction(int n){
	switch(n){
		case 0:
			return longDesc;
			break;
		case 1:
			return accuse();
			break;
		default:
			return "You cannot do that.";
	}
	
}
*/
