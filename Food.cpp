#include "Food.hpp"

Food::Food() {
	type = 7;
}

Food::Food(std::string nameIn, std::string descriptionIn) : Interactable(nameIn, descriptionIn){
	type = 7;
}

void Food::eat(){
	wmove(win, 0, 0);
	wprintw(win, "You just ate the %s", name);
}

