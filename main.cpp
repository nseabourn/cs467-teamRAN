#include <curses.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include "common.hpp"
#include "Game.hpp"

WINDOW* stdscr; 
WINDOW* win;
WINDOW* borderWindow;
const char* hitButton = "Please enter any button to continue.";
const int newWidth = 75;


int main() {	
	//below is formatting code to be uncommented later
	//include initializing screen, making sure screen is big enough, creating a new screen, and displaying the main menu
	const char* makeTaller = "Please make your console screen taller and try again.";
	const char* makeWider = "Please make your console screen wider and try again.";
	const char* makeWiderAndTaller = "Please make your console screen taller and wider. Try again afterwards.";
	const char* menuInstructions = "Please use the arrow keys to move up/down. Hit enter to select option.";
	char playerInput[100];
	int menuChoice;
	
	

	//initializes screen, allocates memory for screen
	stdscr = initscr();
	
	
	
	//initializes and gets width and height of screen
	int height, width;
	getmaxyx(stdscr, height, width);

	//dimensions for new screen
	int newHeight, start_y, start_x;
	newHeight = 25;
	start_y = (height - newHeight) / 2;
	start_x = (width - newWidth) / 2;

	//will display message if screen needs to be bigger
	if (height < newHeight + 6 || width < newWidth + 4) {
		move(0, 0);
		if (height < newHeight + 6 && width < newWidth + 4) {
			printw(makeWiderAndTaller);
		}
		else if (height < newHeight + 6) {
			printw(makeTaller);
		}
		else if (width < newWidth + 4) {
			printw(makeWider);
		}
		move(1, 0);
		printw(hitButton);
		refresh();
		getch();
		endwin();
		return 0;
	}
	
	//will print instructions for menu
	move(0, 0);
	printw(menuInstructions);

	//creates new window from parameters
	//borderWindow will only be used for the border of the game
	borderWindow = newwin(newHeight + 2, newWidth + 2, start_y - 1, start_x - 1);
	box(borderWindow, '|', '_');
	win = newwin(newHeight, newWidth, start_y, start_x);
	refresh();
	wrefresh(borderWindow);
	

	//this allows arrow keys and enter button to be captured
	keypad(win, TRUE);

	//obtains menu choice from user and acts accordingly
	Game game1;
	menuChoice = game1.displayMainScreen();
	move(0, 0);
	clrtoeol();
	refresh();
	switch (menuChoice) {
	
	//option for starting new game
	case 0:
		game1.displayGameInfo();
		game1.createRooms();
		break;

	//option for loading game
	case 1:
		game1.loadGame();
		break;

	//option for quitting game
	case 2:
		delwin(win);
		delwin(borderWindow);
		endwin();
		return 0;
		break;
	}

	
	//write to temp file all commands user enters. Will use to save game
	std::string tempSaveFileName = "saveFiles/.temp" + std::to_string(getpid());
	std::ofstream fout;
	fout.open(tempSaveFileName, std::fstream::out | std::fstream::trunc);
	if(!fout){
		//frees memory used by created subwindows
		delwin(win);
		delwin(borderWindow);
		
		//deallocates memory and ends ncurses
		endwin();
		game1.freeGame();
		
		std::cerr << "Unable to open file for save." << std::endl;

		exit(1);
	}
	//get past menu in save file
	for(int i=0; i<2; i++)
		fout << std::endl;


	//runs until game is over
	while (game1.getGameOverStatus() == false) {
		game1.addToRoomsVisited(game1.getCurrentRoom());
		game1.getCurrentRoom()->printDescription();
		move(0, 0);

		//gets player command and will tell player if the command is invalid
		getstr(playerInput);
		for (unsigned int i = 0; i < strlen(playerInput); i++) {
			playerInput[i] = tolower(playerInput[i]);
		}

		//-----------input that doesn't needs saving---------
		if (strcmp("quitgame", playerInput) == 0) {
			game1.setGameOverStatus(true);
			break;
		}
		else if (strncmp("savegame ", playerInput, 9) == 0 && playerInput[9] != '.') {
			game1.saveScreen();
			move(0, 0);
			clrtoeol();
			wclear(win);
			wmove(win, 0, 0);

			fout.close();
			std::string saveFileName = "saveFiles/" + std::string(&(playerInput[9]));
			fout.open(saveFileName, std::fstream::out | std::fstream::trunc | std::fstream::binary);
			std::ifstream fin;
			fin.open(tempSaveFileName, std::fstream::in | std::fstream::binary);
			if(!fout || !fin){
				wprintw(win, "Failed to save");
				wmove(win, 1, 0);
			}
			else{
				fout << fin.rdbuf();
				wprintw(win, "Saved successfully");
				wmove(win, 1, 0);
			}
			
			wprintw(win, hitButton);
			wrefresh(win);
			getch();
			game1.previousScreen();

			fin.close();
			fout.close();

			//go back to temp save file
			fout.open(tempSaveFileName, std::fstream::out | std::fstream::app);
			if(!fout){
				//frees memory used by created subwindows
				delwin(win);
				delwin(borderWindow);
				
				//deallocates memory and ends ncurses
				endwin();
				game1.freeGame();
				
				std::cerr << "Unable to open file for temp save." << std::endl;

				exit(1);
			}
			continue;
		}
		else if (strcmp("help", playerInput) == 0) {
			game1.displayHelpList();
			continue;
		}
		else if (strcmp("look", playerInput) == 0) {
			game1.saveScreen();
			wclear(win);
			game1.getCurrentRoom()->printLongDescription();
			move(0, 0);
			printw(hitButton);
			refresh();
			getch();
			game1.previousScreen();
			continue;
		}
		else if (strncmp("look at ", playerInput, 8) == 0) {
			char* object = &(playerInput[8]);
			game1.lookAt(object);
			continue;
		}
		else if (strcmp("map", playerInput) == 0) {
			game1.displayMap();
			continue;
		}
		else if (strcmp("inventory", playerInput) == 0) {
			game1.displayInventory();
			continue;
		}
		else if (strncmp("question ", playerInput, 9) == 0) {
			char* object = &(playerInput[9]);
			game1.question(object);
			continue;
		}
		//---------------------------------------------------


		//save user's input
		fout << playerInput << std::endl;

		//---------------input that needs saving-------------
		if (strncmp("go ", playerInput, 2) == 0) {
			char* destination = &(playerInput[3]);
			game1.travelTo(destination);
		}
		else if (game1.getCurrentRoom()->getTravelVectorPosition((std::string) playerInput) != -1) {
			game1.travelTo(playerInput);
		}
		else if (strncmp("take ", playerInput, 5) == 0) {
			char* object = &(playerInput[5]);
			game1.gameTake(object);
		}
		else if (strncmp("accuse ", playerInput, 7) == 0) {
			char* object = &(playerInput[7]);
			game1.gameAccuse(object);
		}
		else if (strncmp("open ", playerInput, 5) == 0) {
			char* object = &(playerInput[5]);
			game1.open(object);
		}		
		else if (strncmp("unlock ", playerInput, 7) == 0) {
			char* object = &(playerInput[7]);
			game1.unlock(object);
		}		
		else if(strncmp("solve ", playerInput, 6) == 0){
			char* object = &(playerInput[6]);
			game1.solve(object);
		}
		else if(strncmp("drop ", playerInput, 5) == 0){
			char* object = &(playerInput[5]);
			game1.drop(object);
		}
		else if(strncmp("fasttravel room ", playerInput, 16) == 0){
			char* location = &(playerInput[16]);
			game1.fastTravel(location);
		}
		else if (strncmp("frisk ", playerInput, 6) == 0){
			char* suspect = &(playerInput[6]);
			game1.gameFrisk(suspect);
		}
		else if (strncmp("eat ", playerInput, 4) == 0){
			char* object = &(playerInput[4]);
			game1.gameEat(object);
		}
		//---------------------------------------------------


		else {
			move(0, 0);
			printw("Invalid command. Please try again.");
			move(1, 0);
			printw(hitButton);
			refresh();
			getch();
			move(1, 0);
			clrtoeol();
			continue;
		}
	}


	fout.close();
	if(std::remove(tempSaveFileName.c_str()) != 0)
		std::cerr << "Unable to delete temporary save file" << std::endl;

	
	//frees memory used by created subwindows
	delwin(win);
	delwin(borderWindow);
	


	//deallocates memory and ends ncurses
	endwin();
	game1.freeGame();
	


	return 0;
}
