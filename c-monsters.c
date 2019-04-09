#include <stdio.h>
#include <stdlib.h>

#define RESET "\033[0m"
#define BOLDRED "\033[1;31m"
#define CYAN "\033[0;36m"
#define BOLDCYAN "\033[1;36m"
#define CYANBLINK "\033[5;36m"

//Monster Structures  = = = = = = = = = = = = = = = = = = = = = = = = = = =
typedef struct Ememy
{
	char* name;
} Enemy;

typedef struct Ally
{
	char* name;
	struct Ally* next;
} Ally;
//END OF: Monster Structure = = = = = = = = = = = = = = = = = = = = = = = =


	
//FUNCTION: main  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
int main()
{	
	//FUNCTION PROTOTYPES = = = = = = = = = = = = = = = = = = = = = = = = = = =
	Ally* insertAlly(Ally*); //add a new ally
	Ally* removeAlly(Ally*); //remove an existing ally
	Ally* peekAllies(Ally*); //view all allies
	
	int sizeAlly(Ally*); //view the number of allies
	int isEmptyAlly(Ally*); //see if ally linked list is empty
	int randomNum(); //returns a random number from the API
	//END OF: Function Prototypes = = = = = = = = = = = = = = = = = = = = = = =
	
	
	
	//Variables = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	char playerName[20]; //create player name array 
	Enemy enemies[4] = {NULL}; //create enemy array
	Ally* allies = {NULL}; //create ally linked list
	Ally* current = {NULL}; //create current ally pointer
	//END OF: Variables = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	
	
	
	//Populate Variables  = = = = = = = = = = = = = = = = = = = = = = = = = = =
	//populate Ememy array
	
	//Game Code = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
		//Welcome Message
			printf (BOLDCYAN " ▄         ▄ ▄▄▄▄▄▄▄▄▄▄▄ ▄           ▄▄▄▄▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄▄▄▄▄ ▄▄       ▄▄ ▄▄▄▄▄▄▄▄▄▄▄\n▐░▌       ▐░▐░░░░░░░░░░░▐░▌         ▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░▌     ▐░░▐░░░░░░░░░░░▌\n▐░▌       ▐░▐░█▀▀▀▀▀▀▀▀▀▐░▌         ▐░█▀▀▀▀▀▀▀▀▀▐░█▀▀▀▀▀▀▀█░▐░▌░▌   ▐░▐░▐░█▀▀▀▀▀▀▀▀▀ \n▐░▌       ▐░▐░▌         ▐░▌         ▐░▌         ▐░▌       ▐░▐░▌▐░▌ ▐░▌▐░▐░▌\n▐░▌   ▄   ▐░▐░█▄▄▄▄▄▄▄▄▄▐░▌         ▐░▌         ▐░▌       ▐░▐░▌ ▐░▐░▌ ▐░▐░█▄▄▄▄▄▄▄▄▄ \n▐░▌  ▐░▌  ▐░▐░░░░░░░░░░░▐░▌         ▐░▌         ▐░▌       ▐░▐░▌  ▐░▌  ▐░▐░░░░░░░░░░░▌\n▐░▌ ▐░▌░▌ ▐░▐░█▀▀▀▀▀▀▀▀▀▐░▌         ▐░▌         ▐░▌       ▐░▐░▌   ▀   ▐░▐░█▀▀▀▀▀▀▀▀▀\n▐░▌▐░▌ ▐░▌▐░▐░▌         ▐░▌         ▐░▌         ▐░▌       ▐░▐░▌       ▐░▐░▌\n▐░▌░▌   ▐░▐░▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄█░▐░▌       ▐░▐░█▄▄▄▄▄▄▄▄▄\n▐░░▌     ▐░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░▌       ▐░▐░░░░░░░░░░░▌\n ▀▀       ▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀         ▀ ▀▀▀▀▀▀▀▀▀▀▀\n\n\n ▄▄▄▄▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄▄▄▄▄\n▐░░░░░░░░░░░▐░░░░░░░░░░░▌\n ▀▀▀▀█░█▀▀▀▀▐░█▀▀▀▀▀▀▀█░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░█▄▄▄▄▄▄▄█░▌\n     ▐░▌    ▐░░░░░░░░░░░▌\n      ▀      ▀▀▀▀▀▀▀▀▀▀▀\n\n\n" RESET);
			printf (BOLDRED "███▄ ▄███▓ ▒█████   ███▄    █   ██████ ▄▄▄█████▓▓█████  ██▀███    ██████\n▓██▒▀█▀ ██▒▒██▒  ██▒ ██ ▀█   █ ▒██    ▒ ▓  ██▒ ▓▒▓█   ▀ ▓██ ▒ ██▒▒██    ▒\n▓██    ▓██░▒██░  ██▒▓██  ▀█ ██▒░ ▓██▄   ▒ ▓██░ ▒░▒███   ▓██ ░▄█ ▒░ ▓██▄\n▒██    ▒██ ▒██   ██░▓██▒  ▐▌██▒  ▒   ██▒░ ▓██▓ ░ ▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒\n▒██▒   ░██▒░ ████▓▒░▒██░   ▓██░▒██████▒▒  ▒██▒ ░ ░▒████▒░██▓ ▒██▒▒██████▒▒\n░ ▒░   ░  ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒ ▒ ▒▓▒ ▒ ░  ▒ ░░   ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░\n░  ░      ░  ░ ▒ ▒░ ░ ░░   ░ ▒░░ ░▒  ░ ░    ░     ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░\n░      ░   ░ ░ ░ ▒     ░   ░ ░ ░  ░  ░    ░         ░     ░░   ░ ░  ░  ░\n       ░       ░ ░           ░       ░              ░  ░   ░           ░\n" RESET);

			printf (CYANBLINK "Press ENTER To Begin!\n" RESET);
			getchar();
			system("clear");
			printf(CYAN "Please enter your name with no spaces: \n" RESET);
			scanf("%s", playerName);
			system("clear");
			printf(BOLDCYAN "Welcome %s!\n" RESET, playerName);
	
	//END OF: Game Code
	
} //END OF: main

//FUNCTION: insertAlly  = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: removeAlly  = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: peekAllies  = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: sizeAlly  = = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: isEmptyAlly = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: randomNum = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


