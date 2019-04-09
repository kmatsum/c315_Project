#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET "\033[0m"
#define BOLDRED "\033[1;31m"
#define CYAN "\033[0;36m"
#define BOLDCYAN "\033[1;36m"
#define CYANBLINK "\033[5;36m"


//Monster Structure = = = = = = = = = = = = = = = = = = = = = = = = = = = =
typedef struct monster
{
	char name[50];
	//int health;
	struct monster* next;
} monster;
//END OF: Monster Structure = = = = = = = = = = = = = = = = = = = = = = = =


	
//FUNCTION: main  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
int main()
{	
	//FUNCTION PROTOTYPES = = = = = = = = = = = = = = = = = = = = = = = = = = =
	void welcomeMessage(char*);
	
	monster* insertAlly(monster*); //add a new ally
	monster* removeAlly(monster*); //remove a preexisting ally
	monster* peekAllies(monster*); //view all allies
	
	int sizeAlly(monster*); //view the number of allies
	int isEmptyAlly(monster*); //see if ally linked list is empty
	int randomNum(); //returns a random number from the API
	
	monster* fileIO (monster*);
	void printList(monster*);
	//END OF: Function Prototypes = = = = = = = = = = = = = = = = = = = = = = =
	
	
	
	//Variables = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	char playerName[20]; //create player name array 
	//Enemy enemies[4] = {NULL}; //create enemy array
	monster* monsterList = NULL;
	monster* allies = NULL; //create ally linked list
	monster* currentAlly = NULL; //create current ally pointer
	int currentEnemy; //index of current enemy
	//END OF: Variables = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	
	
	
	//Populate Variables  = = = = = = = = = = = = = = = = = = = = = = = = = = =
	//populate Ememy array
	
	//Game Code = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	welcomeMessage(playerName);
	monsterList = fileIO(monsterList);
	//END OF: Game Code
	
} //END OF: main

//FUNCTION: insertAlly  = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: removeAlly  = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: peekAllies  = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: sizeAlly  = = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: isEmptyAlly = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: randomNum = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


void welcomeMessage(char* playerName)
{
	printf (BOLDCYAN " ▄         ▄ ▄▄▄▄▄▄▄▄▄▄▄ ▄           ▄▄▄▄▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄▄▄▄▄ ▄▄       ▄▄ ▄▄▄▄▄▄▄▄▄▄▄\n▐░▌       ▐░▐░░░░░░░░░░░▐░▌         ▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░▌     ▐░░▐░░░░░░░░░░░▌\n▐░▌       ▐░▐░█▀▀▀▀▀▀▀▀▀▐░▌         ▐░█▀▀▀▀▀▀▀▀▀▐░█▀▀▀▀▀▀▀█░▐░▌░▌   ▐░▐░▐░█▀▀▀▀▀▀▀▀▀ \n▐░▌       ▐░▐░▌         ▐░▌         ▐░▌         ▐░▌       ▐░▐░▌▐░▌ ▐░▌▐░▐░▌\n▐░▌   ▄   ▐░▐░█▄▄▄▄▄▄▄▄▄▐░▌         ▐░▌         ▐░▌       ▐░▐░▌ ▐░▐░▌ ▐░▐░█▄▄▄▄▄▄▄▄▄ \n▐░▌  ▐░▌  ▐░▐░░░░░░░░░░░▐░▌         ▐░▌         ▐░▌       ▐░▐░▌  ▐░▌  ▐░▐░░░░░░░░░░░▌\n▐░▌ ▐░▌░▌ ▐░▐░█▀▀▀▀▀▀▀▀▀▐░▌         ▐░▌         ▐░▌       ▐░▐░▌   ▀   ▐░▐░█▀▀▀▀▀▀▀▀▀\n▐░▌▐░▌ ▐░▌▐░▐░▌         ▐░▌         ▐░▌         ▐░▌       ▐░▐░▌       ▐░▐░▌\n▐░▌░▌   ▐░▐░▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄█░▐░▌       ▐░▐░█▄▄▄▄▄▄▄▄▄\n▐░░▌     ▐░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░▌       ▐░▐░░░░░░░░░░░▌\n ▀▀       ▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀         ▀ ▀▀▀▀▀▀▀▀▀▀▀\n\n\n ▄▄▄▄▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄▄▄▄▄\n▐░░░░░░░░░░░▐░░░░░░░░░░░▌\n ▀▀▀▀█░█▀▀▀▀▐░█▀▀▀▀▀▀▀█░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░█▄▄▄▄▄▄▄█░▌\n     ▐░▌    ▐░░░░░░░░░░░▌\n      ▀      ▀▀▀▀▀▀▀▀▀▀▀\n\n\n" RESET);
	printf (BOLDRED "███▄ ▄███▓ ▒█████   ███▄    █   ██████ ▄▄▄█████▓▓█████  ██▀███    ██████\n▓██▒▀█▀ ██▒▒██▒  ██▒ ██ ▀█   █ ▒██    ▒ ▓  ██▒ ▓▒▓█   ▀ ▓██ ▒ ██▒▒██    ▒\n▓██    ▓██░▒██░  ██▒▓██  ▀█ ██▒░ ▓██▄   ▒ ▓██░ ▒░▒███   ▓██ ░▄█ ▒░ ▓██▄\n▒██    ▒██ ▒██   ██░▓██▒  ▐▌██▒  ▒   ██▒░ ▓██▓ ░ ▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒\n▒██▒   ░██▒░ ████▓▒░▒██░   ▓██░▒██████▒▒  ▒██▒ ░ ░▒████▒░██▓ ▒██▒▒██████▒▒\n░ ▒░   ░  ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒ ▒ ▒▓▒ ▒ ░  ▒ ░░   ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░\n░  ░      ░  ░ ▒ ▒░ ░ ░░   ░ ▒░░ ░▒  ░ ░    ░     ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░\n░      ░   ░ ░ ░ ▒     ░   ░ ░ ░  ░  ░    ░         ░     ░░   ░ ░  ░  ░\n       ░       ░ ░           ░       ░              ░  ░   ░           ░\n" RESET);

	printf (CYANBLINK "Press ENTER To Begin!\n" RESET);
	getchar();
	system("clear");
	printf(CYAN "Please enter your name with no spaces: \n" RESET);
	scanf("%s", playerName);
	system("clear");
	printf(BOLDCYAN "Welcome %s!\n" RESET, playerName);
}


void printList(monster* n) {
	while(n != NULL) {
    	printf("%s", n -> name);
    	//printf("%s", n -> attack);
    	//printf("%s, ", n -> defense);
    	//printf("%s, ", n -> speed);
    	n = n -> next;
	}
	printf("\n");
}



//FUNCTION: FileIO
monster* fileIO (monster* xHead) {
	FILE *MONSTERLIST = fopen("Monsters.txt", "r");
	char* line;
	size_t bufsize = 64;
	monster* head = (monster*)malloc(sizeof(monster*));
	monster* current = head;
	
	if(MONSTERLIST == NULL) {
		printf("There are no Names in this file...\nPlease create or find the file...\nClosing program...\n");
		exit(0);
	}
	
	line = (char*) malloc(bufsize * sizeof(char));
	
	fgets(line, sizeof(line), MONSTERLIST);
	strcpy(head -> name, line);
	
	
	
	while (!feof(MONSTERLIST)) { /* read a line */
		getline(&line, &bufsize, MONSTERLIST);
		monster* temp = (monster*)malloc(sizeof(monster));
		
		strcpy(temp -> name, line);
		
		current -> next = temp;
		current = temp;
		printf("line = %s", line);
		printf("temp = %s", temp -> name);
		printf("\n");
	}
	
	printList(head);
}