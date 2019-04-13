#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Use function randomNumberAPICall to get a value (Not finished yet). In order to compile correctly, type: gcc -Wall c-monsters.c  -lcurl -o "Whatever Name"
//#include "api.h"

#define RESET "\033[0m"
#define BOLDRED "\033[1;31m"
#define CYAN "\033[0;36m"
#define BOLDCYAN "\033[1;36m"
#define CYANBLINK "\033[5;36m"


//Monster Structure = = = = = = = = = = = = = = = = = = = = = = = = = = = =
typedef struct monster {
	char name[64];
	int attack;
	int defence;
	int speed;
	struct monster* next;
} monster;
//END OF: Monster Structure = = = = = = = = = = = = = = = = = = = = = = = =



	
//FUNCTION: main  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
int main () {	
	//FUNCTION PROTOTYPES = = = = = = = = = = = =
	void welcomeMessage (char*);
	
	monster* fillPlayerRoster (monster*); //add a monster to player roster
	//monster* removeAlly (monster*); //remove a preexisting ally
	//monster* peekAllies (monster*); //view all allies
	
	int sizeList (monster*); //view the number of monsters
	int randomNum (); //returns a random number from the API
	
	monster* fileIO ();
	void printList (monster*);
	//END OF: Function Prototypes = = = = = = = =
	
	randomNumberAPICall();
	
	//Variables = = = = = = = = = = = = = = = = =
	char playerName[20]; //create player name array 
	monster enemies[4]; //create enemy array
	monster* availableMonsterList = NULL; //List of ALL avilable monster for players to use
	monster* playerRoster = NULL; //create ally linked list
	monster* currentPlayerMonster = NULL; //create current ally pointer
	monster* currentEnemyMonster = NULL; //Create current ally pointer
	int currentEnemy; //index of current enemy
	//END OF: Variables = = = = = = = = = = = = =
	
	
	
	//Populate Variables  = = = = = = = = = = = =
	//Populate Enemy array
	
	//Game Code = = = = = = = = = = = = = = = = =
	welcomeMessage(playerName); //welcome user
	availableMonsterList = fileIO(); //import monsters
	printList(availableMonsterList); //print available monsters
	playerRoster = fillPlayerRoster(availableMonsterList); //add available monsters to roster
	printList(playerRoster); //print player selected monsters
	printf("\n\nYou have added a total of %d Monsters!\n\n",sizeList(playerRoster));
	printf("============================================================\n\n");
	
} //END OF: main










//FUNCTION: welcomeMessage  = = = = = = = = = = = = = = = = = = = = = = = = = =
void welcomeMessage(char* playerName) {
	printf (BOLDCYAN " ▄         ▄ ▄▄▄▄▄▄▄▄▄▄▄ ▄           ▄▄▄▄▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄▄▄▄▄ ▄▄       ▄▄ ▄▄▄▄▄▄▄▄▄▄▄\n▐░▌       ▐░▐░░░░░░░░░░░▐░▌         ▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░▌     ▐░░▐░░░░░░░░░░░▌\n▐░▌       ▐░▐░█▀▀▀▀▀▀▀▀▀▐░▌         ▐░█▀▀▀▀▀▀▀▀▀▐░█▀▀▀▀▀▀▀█░▐░▌░▌   ▐░▐░▐░█▀▀▀▀▀▀▀▀▀ \n▐░▌       ▐░▐░▌         ▐░▌         ▐░▌         ▐░▌       ▐░▐░▌▐░▌ ▐░▌▐░▐░▌\n▐░▌   ▄   ▐░▐░█▄▄▄▄▄▄▄▄▄▐░▌         ▐░▌         ▐░▌       ▐░▐░▌ ▐░▐░▌ ▐░▐░█▄▄▄▄▄▄▄▄▄ \n▐░▌  ▐░▌  ▐░▐░░░░░░░░░░░▐░▌         ▐░▌         ▐░▌       ▐░▐░▌  ▐░▌  ▐░▐░░░░░░░░░░░▌\n▐░▌ ▐░▌░▌ ▐░▐░█▀▀▀▀▀▀▀▀▀▐░▌         ▐░▌         ▐░▌       ▐░▐░▌   ▀   ▐░▐░█▀▀▀▀▀▀▀▀▀\n▐░▌▐░▌ ▐░▌▐░▐░▌         ▐░▌         ▐░▌         ▐░▌       ▐░▐░▌       ▐░▐░▌\n▐░▌░▌   ▐░▐░▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄█░▐░▌       ▐░▐░█▄▄▄▄▄▄▄▄▄\n▐░░▌     ▐░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░▌       ▐░▐░░░░░░░░░░░▌\n ▀▀       ▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀         ▀ ▀▀▀▀▀▀▀▀▀▀▀\n\n\n ▄▄▄▄▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄▄▄▄▄\n▐░░░░░░░░░░░▐░░░░░░░░░░░▌\n ▀▀▀▀█░█▀▀▀▀▐░█▀▀▀▀▀▀▀█░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░█▄▄▄▄▄▄▄█░▌\n     ▐░▌    ▐░░░░░░░░░░░▌\n      ▀      ▀▀▀▀▀▀▀▀▀▀▀\n\n\n" RESET);
	printf (BOLDRED "███▄ ▄███▓ ▒█████   ███▄    █   ██████ ▄▄▄█████▓▓█████  ██▀███    ██████\n▓██▒▀█▀ ██▒▒██▒  ██▒ ██ ▀█   █ ▒██    ▒ ▓  ██▒ ▓▒▓█   ▀ ▓██ ▒ ██▒▒██    ▒\n▓██    ▓██░▒██░  ██▒▓██  ▀█ ██▒░ ▓██▄   ▒ ▓██░ ▒░▒███   ▓██ ░▄█ ▒░ ▓██▄\n▒██    ▒██ ▒██   ██░▓██▒  ▐▌██▒  ▒   ██▒░ ▓██▓ ░ ▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒\n▒██▒   ░██▒░ ████▓▒░▒██░   ▓██░▒██████▒▒  ▒██▒ ░ ░▒████▒░██▓ ▒██▒▒██████▒▒\n░ ▒░   ░  ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒ ▒ ▒▓▒ ▒ ░  ▒ ░░   ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░\n░  ░      ░  ░ ▒ ▒░ ░ ░░   ░ ▒░░ ░▒  ░ ░    ░     ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░\n░      ░   ░ ░ ░ ▒     ░   ░ ░ ░  ░  ░    ░         ░     ░░   ░ ░  ░  ░\n       ░       ░ ░           ░       ░              ░  ░   ░           ░\n" RESET);

	printf (CYANBLINK "Press ENTER To Begin!\n" RESET);
	getchar();
	system("clear");
	printf(CYAN "Please enter your name with no spaces: \n" RESET);
	scanf("%s", playerName);
	system("clear");
	printf(BOLDCYAN "Welcome %s!\n" RESET, playerName);
} //END OF: welcomeMessage




//FUNCTION: FileIO  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
monster* fileIO () {
	//Variables
	FILE *MONSTERLIST = fopen("Monsters.txt", "r"); //File Variable
	char* line; //Charachter array start pointer
	size_t bufsize = 256; //Size of the Stream buffer
	
	monster* head = (monster*)malloc(sizeof(monster*)); //Temporary head for the Linked List we are creating
	monster* current = head; //Current pointer for the Monster
	
	//Check if the FILE exists
	if(MONSTERLIST == NULL) {
		printf("There are no Names in this file...\nPlease create or find the file...\nClosing program...\n");
		exit(0);
	}
	
	//Provide the line pointer with enough memory
	line = (char*) malloc(bufsize * sizeof(char));
	
	
	
	
	//Reading the File  = = = = = = = =

	getline(&line, &bufsize, MONSTERLIST); //Read the first line (Name)
	strcpy(head -> name, line); //Store first line into the first node of the linked list
	
	getline(&line, &bufsize, MONSTERLIST); //Read next line (All other interger stats)
	sscanf(line, "%d\t%d\t%d", &(head -> attack), &(head -> defence), &(head -> speed)); //This uses the scanf function to read the input buffer as integers using %d

	getline(&line, &bufsize, MONSTERLIST); //Read the empty line in the text file
	
	
	//While Loop to keep adding monsters to the Linked List...
	while (!feof(MONSTERLIST)) { //While NOT end of file
		
		//Create a Temporary node
		monster* temp = (monster*)malloc(sizeof(monster));
		
		getline(&line, &bufsize, MONSTERLIST); //Read the first line (Name)
		strcpy(temp -> name, line); //Store first line into the first node of the linked list
	
		getline(&line, &bufsize, MONSTERLIST); //Read next line (All other interger stats)
		sscanf(line, "%d\t%d\t%d", &(temp -> attack), &(temp -> defence), &(temp -> speed));  //This uses the scanf function to read the input buffer as integers using %d
		
		getline(&line, &bufsize, MONSTERLIST); //Read the empty line in the text file
		
		//Add temp to the linked list...
		current -> next = temp;
		current = temp;
	}
	
	//Return the head of the entire monsersLinkedList
	return head;
} //END OF: FileIO




//FUNCTION: printList = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void printList(monster* n) {
	int index = 1;
	printf("\nThe available Monsters are...\n\n");
	while(n != NULL) {
		printf("%d ---- \t", index);
    	printf("Name: %s", n -> name);
    	printf("\tAttack: %d\n", n -> attack);
    	printf("\tDefence: %d\n", n -> defence);
    	printf("\tSpeed: %d\n", n -> speed);
		printf("\n");
		index ++;
    	n = n -> next;
	}
	printf("\n");
} //END OF: printList




//FUNCTION: sizeList  = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
int sizeList (monster* head)
{
	//variables
	monster* currentMonster = head;
	int size = 0;
	
	//loop
	while(currentMonster != NULL) {
		currentMonster = currentMonster -> next;
		size++;
	}
	
	return size;
} //END OF: sizeList




//FUNCTION: fillPlayerRoster  = = = = = = = = = = = = = = = = = = = = = = = = =
monster* fillPlayerRoster (monster* importedMonsters) {
	//variables
	monster* head = NULL; //player list pointer to return
	monster* currentMonster = importedMonsters;
	int index; //variable to store user index choice
	int count = 0; //variable to keep track of number of added monsters
	
	printf("============================================================\n\n");
	printf("Please enter the numbers of the Monsters to add to your roster.\n");
	printf("You may choose between 1 and 6 Monsters.\n");
	printf("Enter '0' when you are done.\n\n");
	
	while (1 == 1) {
		//reset monster list
		currentMonster = importedMonsters;
		
		//read and check user input
		int checking = 1;
		int done = 0;
		
		while (checking == 1) {
			//read user input
			printf("Index: ");
			scanf(" %d",&index);
			
			//break if 0 was entered to quit
			if (index == 0) {
				//return if 0 monsters have been entered
				if (count == 0) {
					printf("\nYou have not added any Monsters!\n\n");
				} else {
					done = 1;
					break;
				}
			}
			
			//check for max of 6 monsters
			if (count == 6) {
				printf("\nYou have reached the maximum of 6 monsters.\n");
				done = 1;
				break;
			}
			
			//check for invalid input
			if (!(index <= sizeList(importedMonsters))) {
				printf("\nYou have entered an invalid index.\n");
				printf("Please enter a number between 1 and %d.",sizeList(importedMonsters));
				printf("\nEnter 0 if you are done adding monsters.\n\n");
			}
			
			if (!((index == 0) || (count == 6) || ((index > sizeList(importedMonsters))))) {
				checking = 0;
			}
		}
		
		//check if done
		if (done == 1) {
			break;
		}
		
		//save the entered monster to the list
		monster* temp = (monster*) malloc(sizeof(monster)); //node to store data
		int i = 1; //int to compare with desired index
		
		//cycle through imported list
		while(currentMonster != NULL) {
			//when at the desired monster
			if (i == index) {
				//copy data to node 
				strcpy(temp->name, currentMonster -> name);
				temp -> attack = currentMonster -> attack;
				temp -> defence = currentMonster -> defence;
				temp -> speed = currentMonster -> speed;
				
				//add to front of list
				temp -> next = head;
				head = temp;
				
				//increase count and break
				count++;
				printf("\t%s \twas added to your roster.\n\n",temp -> name);
				break;
			}
			//continue cycling through if not at desired monster
			currentMonster = currentMonster -> next;
			i++;
		}
	}
	return head;
} //END OF: fillPlayerRoster




//FUNCTION: peekAllies  = = = = = = = = = = = = = = = = = = = = = = = = = = = =




//FUNCTION: isEmptyAlly = = = = = = = = = = = = = = = = = = = = = = = = = = = =




//FUNCTION: randomNum = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


//Function: switchMonster = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

monster * switchMonster(int index, monster *head)
{
	
	monster *temp = head;

	//Assuming that we don't consider 0 to be a position
	while(index != 0)
	{
		temp = temp->next;
		index--;
	}

	if(temp->health <= 0)
	{
		printf("Monster has no health and cannot be swapped in.\n");
		return NULL;
	}
	
	return temp;
} //End of: switchMonster
