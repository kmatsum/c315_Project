#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Function from api is randomNumberAPICall().In order to compile correctly, enter in -lcurl after normal compilation  "gcc -o NAME c-monsters.c -lcurl"
//Uncomment below line to use the api
#include "api.h"

#define RESET "\033[0m"
#define BOLDRED "\033[1;31m"
#define CYAN "\033[0;36m"
#define BOLDCYAN "\033[1;36m"
#define CYANBLINK "\033[5;36m"


//Monster Structure = = = = = = = = = = = = = = = = = = = = = = = = = = = =
typedef struct monster {
	char name[64];
	int attack;
	int defense;
	int speed;
	int health;
	struct monster* next;
} monster;
//END OF: Monster Structure = = = = = = = = = = = = = = = = = = = = = = = =



	
//FUNCTION: main  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
int main () {	
	//FUNCTION PROTOTYPES = = = = = = = = = = = =
	void welcomeMessage (char*); //Welcome Message
	void pauseOutput (); //Pause Output
	
	monster* fillPlayerRoster (monster*); //add a monster to player roster
	
	int sizeList (monster*); //view the number of monsters
	int faintedMonster = 0;
	
	monster* fileIO (FILE*);
	void printList (monster*);
	void status(monster*, monster*);
  
	void calculateBattle (int, monster*, monster*);
	monster * switchMonster (int, monster*);
	//END OF: Function Prototypes = = = = = = = =
	
	//Variables = = = = = = = = = = = = = = = = =
	char playerName[20]; //create player name array 
	
	monster enemies[4]; //create enemy array
	monster* availableMonsterList = NULL; //List of ALL avilable monster for players to use
	monster* playerRoster = NULL; //create ally linked list
	monster* enemyLinkedList = NULL; //create enemy linked list
	monster* currentPlayerMonster = NULL; //create current ally pointer
	monster* currentEnemyMonster = NULL; //Create current ally pointer
	
	int currentEnemy; //index of current enemy
	FILE* MONSTERLIST = fopen("Monsters.txt", "r"); //Player Monster File Variable
	FILE* ENEMYLIST = fopen("Enemies.txt", "r"); //Enemy File Variable
	
	int playerRosterSize = 0;
	//END OF: Variables = = = = = = = = = = = = =
	
	
	
	//Populate Variables  = = = = = = = = = = = =
	//Populate Enemy array
	
	//Game Code = = = = = = = = = = = = = = = = =
	system("clear");
	welcomeMessage(playerName); //welcome user
	availableMonsterList = fileIO(MONSTERLIST); //import monsters to available monsters list
	enemyLinkedList = fileIO(ENEMYLIST); //import monsters to enemy list
	
	playerRoster = fillPlayerRoster(availableMonsterList); //add available monsters to roster
	system("clear");
	
	printf("\n============================================================\n\n");
	printf("The monsters you have added are...\n\n");
	printList(playerRoster); //print player selected monsters
	playerRosterSize = sizeList(playerRoster);
	printf("You have added a total of %d Monsters!\n", playerRosterSize);
	
	printf("\n============================================================\n\n");

	getchar();
	pauseOutput();
	
	printf("\n============================================================\n\n");
	printf("The monsters you are fighting are...\n\n");
	printList(enemyLinkedList); //print enemy monster list
	
	pauseOutput();
	
	printf("\n============================================================\n\n\n\n");
	
	//Battle Logic = = = = = = = = = = = = = = = 
	//set current monsters
	currentPlayerMonster = playerRoster;
	currentEnemyMonster = enemyLinkedList;
	printf("The battle has BEGUN!\n\n\n");
	
	//start while loop
	int battling = 1;
	int choice = 0;
	while (battling == 1) {		
		printf("\n============================================================\n\n");

		printf("Current battle contestants ...\n\n");
		status(currentPlayerMonster, currentEnemyMonster);
		
		printf("============================================================\n\n");
		
		printf("Please select an action:\n\t1) Attack\n\t2) Defend\n\t3) Switch Monsters\n\nCHOICE: ");
		scanf("%d",&choice);
		
		switch (choice) {
			//Attack
			case 1:
				calculateBattle(choice, currentPlayerMonster, currentEnemyMonster);

				break;
			//Defend
			case 2:
				calculateBattle(choice, currentPlayerMonster, currentEnemyMonster);

				break;
				
			case 3:
				system("clear");
				printf("\n============================================================\n\n");
				
				//Ask for input on which monster to choose from:
				printList(playerRoster);
				
				printf("Which monster would you like to switch out your curently battling monster with?\n");
				
				int switchIndex = 0;
				int inputCheck = 0;
				monster* tempSwitchMonster = NULL;
			
				scanf("%d", &switchIndex);
						
				tempSwitchMonster = switchMonster(switchIndex, playerRoster);
				
				while ( inputCheck == 0 ) {
					system("clear");
					if ( tempSwitchMonster == NULL ){
						printf("\n============================================================\n\n");
						printList(playerRoster);
						printf("Please select a valid monster...\n");
						scanf("%d", &switchIndex);
					} else if ( tempSwitchMonster -> health == 0 ) {
						printf("\n============================================================\n\n");
						printList(playerRoster);
						printf("That monster has 0 Health, it can't battle...\n");
						scanf("%d", &switchIndex);
					} else {
						inputCheck = 1;
					}
					tempSwitchMonster = switchMonster(switchIndex, playerRoster);
				} //END OF: While Loop
				
				if ( currentPlayerMonster == tempSwitchMonster ) {
					printf("\n============================================================\n\n");
					printf("You decided to not switch the Monster...\n\n\n\n\n");
				} else {
					printf("\n============================================================\n\n");
					printf("You switched your %s with your %s!\n\n\n\n\n", currentPlayerMonster -> name, tempSwitchMonster -> name);
					currentPlayerMonster = tempSwitchMonster;
				}
				
				break;
				
			default:
				printf("You have entered invalid input.\nPlease enter 1, 2, or 3.\n\n\n\n");
				break;
		} //END OF: Switch Statement
		
		if (currentPlayerMonster -> health == 0) {
				
				faintedMonster++;
				
				//You Lost
				if ( faintedMonster == playerRosterSize ) {
					printf("\n============================================================\n\n");
					printf(BOLDRED "██╗   ██╗ ██████╗ ██╗   ██╗    ██╗      ██████╗ ███████╗████████╗    ██╗\n╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║     ██╔═══██╗██╔════╝╚══██╔══╝    ██║\n ╚████╔╝ ██║   ██║██║   ██║    ██║     ██║   ██║███████╗   ██║       ██║\n  ╚██╔╝  ██║   ██║██║   ██║    ██║     ██║   ██║╚════██║   ██║       ╚═╝\n   ██║   ╚██████╔╝╚██████╔╝    ███████╗╚██████╔╝███████║   ██║       ██╗\n   ╚═╝    ╚═════╝  ╚═════╝     ╚══════╝ ╚═════╝ ╚══════╝   ╚═╝       ╚═╝" RESET);
					printf("\n\n============================================================\n\n");
					exit(0);
				}
				
				system("clear");
				printf("\n============================================================\n\n");
				
				printList(playerRoster);
				printf("Your monster fainted! Which monster would you like to switch out with?\n");
				
				int switchIndex = 0;
				int inputCheck = 0;
				
				monster* tempSwitchMonster = NULL;
			
				scanf("%d", &switchIndex);
				
				tempSwitchMonster = switchMonster(switchIndex, playerRoster);
				
				while ( inputCheck == 0 ) {
					system("clear");
					if ( tempSwitchMonster == NULL ){
						printf("\n============================================================\n\n");
						printList(playerRoster);
						printf("Please select a valid monster...\n");
						scanf("%d", &switchIndex);
					} else if ( tempSwitchMonster -> health == 0 ) {
						printf("\n============================================================\n\n");
						printList(playerRoster);
						printf("That monster has 0 Health, it can't battle...\n");
						scanf("%d", &switchIndex);
					} else {
						inputCheck = 1;
					}
					tempSwitchMonster = switchMonster(switchIndex, playerRoster);
				}
				
				if ( currentPlayerMonster == tempSwitchMonster ) {
					printf("\n============================================================\n\n");
					printf("You decided to not switch the Monster...\n\n\n\n\n");
				} else {
					printf("\n============================================================\n\n");
					printf("You switched your %s with your %s!\n\n\n\n\n", currentPlayerMonster -> name, tempSwitchMonster -> name);
					currentPlayerMonster = tempSwitchMonster;
				}
		} else if (currentEnemyMonster -> health == 0) {
			currentEnemyMonster = currentEnemyMonster -> next;
			if ( currentEnemyMonster == NULL ) {
				printf("There are no more monsters in the enemy roster!\n");
				
				//You Won
				printf("\n============================================================\n\n");
				printf(BOLDCYAN "██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗ ██████╗ ███╗   ██╗    ██╗\n╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██╔═══██╗████╗  ██║    ██║\n ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║   ██║██╔██╗ ██║    ██║\n  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║   ██║██║╚██╗██║    ╚═╝\n   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝╚██████╔╝██║ ╚████║    ██╗\n   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝    ╚═╝" RESET);
				printf("\n\n============================================================\n\n");
				
				battling = 0;
			} else {
				printf("Here comes a %s!\n", currentEnemyMonster -> name);
			}
		}
	}
} //END OF: main










//FUNCTION: pauseOutput = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void pauseOutput() {
	printf (CYANBLINK "Press ENTER to Continue!\n" RESET);
	fflush(stdout);
	getchar();
	system("clear");
}//END Of: pauseOutput



//FUNCTION: welcomeMessage  = = = = = = = = = = = = = = = = = = = = = = = = = =
void welcomeMessage(char* playerName) {
	printf (BOLDCYAN " ▄         ▄ ▄▄▄▄▄▄▄▄▄▄▄ ▄           ▄▄▄▄▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄▄▄▄▄ ▄▄       ▄▄ ▄▄▄▄▄▄▄▄▄▄▄\n▐░▌       ▐░▐░░░░░░░░░░░▐░▌         ▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░▌     ▐░░▐░░░░░░░░░░░▌\n▐░▌       ▐░▐░█▀▀▀▀▀▀▀▀▀▐░▌         ▐░█▀▀▀▀▀▀▀▀▀▐░█▀▀▀▀▀▀▀█░▐░▌░▌   ▐░▐░▐░█▀▀▀▀▀▀▀▀▀ \n▐░▌       ▐░▐░▌         ▐░▌         ▐░▌         ▐░▌       ▐░▐░▌▐░▌ ▐░▌▐░▐░▌\n▐░▌   ▄   ▐░▐░█▄▄▄▄▄▄▄▄▄▐░▌         ▐░▌         ▐░▌       ▐░▐░▌ ▐░▐░▌ ▐░▐░█▄▄▄▄▄▄▄▄▄ \n▐░▌  ▐░▌  ▐░▐░░░░░░░░░░░▐░▌         ▐░▌         ▐░▌       ▐░▐░▌  ▐░▌  ▐░▐░░░░░░░░░░░▌\n▐░▌ ▐░▌░▌ ▐░▐░█▀▀▀▀▀▀▀▀▀▐░▌         ▐░▌         ▐░▌       ▐░▐░▌   ▀   ▐░▐░█▀▀▀▀▀▀▀▀▀\n▐░▌▐░▌ ▐░▌▐░▐░▌         ▐░▌         ▐░▌         ▐░▌       ▐░▐░▌       ▐░▐░▌\n▐░▌░▌   ▐░▐░▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄▄▄▐░█▄▄▄▄▄▄▄█░▐░▌       ▐░▐░█▄▄▄▄▄▄▄▄▄\n▐░░▌     ▐░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░░░░░░░░░░░▐░▌       ▐░▐░░░░░░░░░░░▌\n ▀▀       ▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀▀▀▀▀▀▀▀▀▀▀ ▀         ▀ ▀▀▀▀▀▀▀▀▀▀▀\n\n\n ▄▄▄▄▄▄▄▄▄▄▄ ▄▄▄▄▄▄▄▄▄▄▄\n▐░░░░░░░░░░░▐░░░░░░░░░░░▌\n ▀▀▀▀█░█▀▀▀▀▐░█▀▀▀▀▀▀▀█░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░▌       ▐░▌\n     ▐░▌    ▐░█▄▄▄▄▄▄▄█░▌\n     ▐░▌    ▐░░░░░░░░░░░▌\n      ▀      ▀▀▀▀▀▀▀▀▀▀▀\n\n\n" RESET);
	printf (BOLDRED "███▄ ▄███▓ ▒█████   ███▄    █   ██████ ▄▄▄█████▓▓█████  ██▀███    ██████\n▓██▒▀█▀ ██▒▒██▒  ██▒ ██ ▀█   █ ▒██    ▒ ▓  ██▒ ▓▒▓█   ▀ ▓██ ▒ ██▒▒██    ▒\n▓██    ▓██░▒██░  ██▒▓██  ▀█ ██▒░ ▓██▄   ▒ ▓██░ ▒░▒███   ▓██ ░▄█ ▒░ ▓██▄\n▒██    ▒██ ▒██   ██░▓██▒  ▐▌██▒  ▒   ██▒░ ▓██▓ ░ ▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒\n▒██▒   ░██▒░ ████▓▒░▒██░   ▓██░▒██████▒▒  ▒██▒ ░ ░▒████▒░██▓ ▒██▒▒██████▒▒\n░ ▒░   ░  ░░ ▒░▒░▒░ ░ ▒░   ▒ ▒ ▒ ▒▓▒ ▒ ░  ▒ ░░   ░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░\n░  ░      ░  ░ ▒ ▒░ ░ ░░   ░ ▒░░ ░▒  ░ ░    ░     ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░\n░      ░   ░ ░ ░ ▒     ░   ░ ░ ░  ░  ░    ░         ░     ░░   ░ ░  ░  ░\n       ░       ░ ░           ░       ░              ░  ░   ░           ░\n" RESET);

	printf(CYAN "Please enter your name: \n" RESET);
	scanf(" %[^\n]s ", playerName);
	
	system("clear");
	
	printf(BOLDCYAN "Welcome %s!\n" RESET, playerName);
	getchar();
	pauseOutput();
} //END OF: welcomeMessage



//FUNCTION: FileIO  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
monster* fileIO (FILE* MONSTERLIST) {
	//Variables
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
	sscanf( line, " %[^\r]s", head -> name ); //Store first line into the first node of the linked list
	
	getline(&line, &bufsize, MONSTERLIST); //Read next line (All other interger stats)
	sscanf(line, "%d\t%d\t%d", &(head -> attack), &(head -> defense), &(head -> speed)); //This uses the scanf function to read the input buffer as integers using %d

	head -> health = 100;
	
	getline(&line, &bufsize, MONSTERLIST); //Read the empty line in the text file
	
	
	
	//While Loop to keep adding monsters to the Linked List...
	while (!feof(MONSTERLIST)) { //While NOT end of file
		
		//Create a Temporary node
		monster* temp = (monster*)malloc(sizeof(monster));
		
		getline(&line, &bufsize, MONSTERLIST); //Read the first line (Name)
		sscanf( line, " %[^\r]s", temp -> name ); //Store first line into the first node of the linked list
		
		getline(&line, &bufsize, MONSTERLIST); //Read next line (All other interger stats)
		sscanf(line, "%d\t%d\t%d", &(temp -> attack), &(temp -> defense), &(temp -> speed));  //This uses the scanf function to read the input buffer as integers using %d
		
		temp -> health = 100;
		
		getline(&line, &bufsize, MONSTERLIST); //Read the empty line in the text file
		
		//Add temp to the linked list...
		current -> next = temp;
		current = temp;
	}
	
	//Return the head of the entire monstersLinkedList
	return head;
} //END OF: FileIO




//FUNCTION: printList = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void printList(monster* n) {
	int index = 1;
	while(n != NULL) {
		if( n->health == 0) {
			printf(BOLDRED"%d --- \t", index);
			printf("Name: %s\n", n -> name);
			printf("\tHealth: %d\n", n -> health);
			printf("\tAttack: %d\n", n -> attack);
			printf("\tDefense: %d\n", n -> defense);
			printf("\tSpeed: %d\n" RESET, n -> speed);
			printf("\n");
			index ++;
			n = n -> next;
		}
		else {
			printf("%d --- \t", index);
			printf("Name: %s\n", n -> name);
			printf("\tHealth: %d\n", n -> health);
			printf("\tAttack: %d\n", n -> attack);
			printf("\tDefense: %d\n", n -> defense);
			printf("\tSpeed: %d\n", n -> speed);
			printf("\n");
			index ++;
			n = n -> next;
		}
	}
	
	printf("============================================================\n\n");
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
	monster* currentMonster = NULL;
	monster* currentPlayerRoster = head; //set current player roster to head
	int index; //variable to store user index choice
	int count = 0; //variable to keep track of number of added monsters
	int listSize = sizeList(importedMonsters);
	
	while (1 == 1) {
		if (count != 0) {
			system("clear");
		}
		
		printf("\n============================================================\n\n");
		printf("The available monsters are...\n\n");	

		printList(importedMonsters);
		
		printf("Please enter the numbers of the Monsters to add to your roster.\n");
		printf("You may choose between 1 and 6 Monsters.\n");
		printf("Enter '0' when you are done.\n\n");
		
		if (currentMonster != NULL) {
			printf("Selection #%d:\n\t%s was added to your roster.\n\n", count, currentMonster -> name);
		} else {
			printf("\n\n\n");
		}
		
		//reset monster list
		currentMonster = importedMonsters;
		
		//read and check user input
		int checking = 1;
		int done = 0;
		
		while (checking == 1) {
			
			//check for max of 6 monsters
			if (count == 6) {
				system("clear");
				printf("\nYou have reached the maximum of 6 monsters.\n");
				done = 1;
				break;
			}
			
			//read user input
			printf("Index: ");
			scanf(" %d",&index);
			
			//break if 0 was entered to quit
			if (index == 0) {
				//return if 0 monsters have been entered
				if (count == 0) {
					system("clear");
					printf("\n============================================================\n\n");
					
					printf("The available monsters are...\n\n");
					
					printList(importedMonsters);
					
					printf("Please enter the numbers of the Monsters to add to your roster.\n");
					printf("You may choose between 1 and 6 Monsters.\n");
					printf("Enter '0' when you are done.\n\n");
					printf("\n\tYou have not added any Monsters!\n\n");
				} else {
					done = 1;
					break;
				}
			}
			
			//check for invalid input
			if (!(index <= listSize)) {
				system("clear");
				printf("\n============================================================\n\n");
				printList(importedMonsters);
				printf("You have entered an invalid index.\n");
				printf("Please enter a number between 1 and %d.", listSize);
				printf("\nEnter 0 if you are done adding monsters.\n\n");
			}
			
			if (!((index == 0) || (count == 6) || (index > listSize))) {
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
				temp -> defense = currentMonster -> defense;
				temp -> speed = currentMonster -> speed;
				temp -> health = currentMonster -> health;
				
				//if the first one
				if (currentPlayerRoster == NULL){
					currentPlayerRoster = temp;
					head = currentPlayerRoster;
				}
				else{
					//add to end of list
					currentPlayerRoster -> next = temp;
					currentPlayerRoster = currentPlayerRoster -> next;
				}
				
				//increase count and break
				count++;
				break;
			}
			//continue cycling through if not at desired monster
			currentMonster = currentMonster -> next;
			i++;
		}
	}
	return head;
} //END OF: fillPlayerRoster



void calculateBattle (int playerSelection, monster* currentPlayer, monster* currentEnemy) {
	//Set monster to have a 50/50 chance of attacking or defending
	int monsterChoice = ( randomNumberAPICall() % 2 );
	int damage = 0;

	system("clear");
	
	printf("\n============================================================\n\n");

	
	switch (playerSelection) {
		//Attacking
		case 1:
			//If the monster is defending
			if ( monsterChoice == 1 ) {
				printf("Your %s attacked the %s for %d!\n", currentPlayer -> name, currentEnemy -> name, currentPlayer -> attack);
				
				printf("The %s defended for %d!\n", currentEnemy -> name, currentEnemy -> defense);
				
				damage = ( currentPlayer -> attack - currentEnemy -> defense );
				
				if ( damage <= 0 ) {
					printf("The %s blocked all your %s's attack.\n\n\n", currentEnemy -> name, currentPlayer -> name);
				} else {
					currentEnemy -> health -= damage;
					
					printf("The %s was damaged %d HP!\n", currentEnemy -> name, damage);
					
					//Is enemy dead?
					if ( currentEnemy -> health <= 0 ) {
						currentEnemy -> health = 0;
						
						printf("The enemy has no more HP! The %s fainted...\n", currentEnemy -> name);
					} else {
						printf("\n\n");
					}
				}
			} else {
				//Check who attacks first
				if (currentPlayer -> speed >= currentEnemy -> speed) {
					damage = currentPlayer -> attack;
					currentEnemy -> health -= damage;
					
					printf("The %s took a full blow! Hit for %d!\n", currentEnemy -> name, damage);
					
					//Is enemy dead?
					if ( currentEnemy -> health <= 0 ) {
						currentEnemy -> health = 0;
						
						printf("\nThe enemy has no more HP! The %s fainted...\n\n", currentEnemy -> name);
					} else {
						damage = currentEnemy -> attack;
						currentPlayer -> health -= damage;
						
						printf("Your %s also took a full blow! Hit for %d!\n", currentPlayer -> name, damage);
						
						//Is the Player Dead?
						if ( currentPlayer -> health <= 0 ) {
							currentPlayer -> health = 0;
							
							printf("Your %s has no more HP and fainted!\n\n", currentPlayer -> name);
						} else {
							
							printf("\n\n\n");
						}
					}
				} else { //If the enemy has higher Speed
					damage = currentEnemy -> attack;
					currentPlayer -> health -= damage;
					
					printf("Your %s took a full blow! Hit for %d!\n", currentPlayer -> name, damage);

					//Is player dead?
					if (currentPlayer -> health <= 0) {
						currentPlayer -> health = 0;
						
						printf("Your %s has no more HP! The %s fainted...\n\n\n", currentPlayer -> name, currentPlayer -> name);
						return;
					} else {
						damage = currentPlayer -> attack;
						currentEnemy -> health -= damage;
						
						printf("The %s also took a full blow! Hit for %d!\n", currentEnemy -> name, damage);
						
						//Is enemy dead?
						if ( currentEnemy -> health <= 0 ) {
							currentEnemy -> health = 0;
							
							printf("The enemy has no more HP! The %s fainted...\n\n", currentEnemy -> name);
						} else {
							printf("\n\n\n");
						}
					}
				}
			}
			break;
			
		case 2:
			if ( monsterChoice == 1 ) {
				
				printf("Both monsters took a defensive stance! Nothing occured!\n\n\n\n\n");
			} else {
				
				printf("The %s attacked the %s for %d!\n", currentEnemy -> name, currentPlayer -> name, currentEnemy -> attack);
				
				printf("The %s defended for %d!\n", currentPlayer -> name, currentPlayer -> defense);
				
				damage = ( currentEnemy -> attack - currentPlayer -> defense );
				
				if ( damage <= 0 ) {
					printf("Your %s blocked all of the %s's attack.\n\n\n", currentPlayer -> name, currentEnemy -> name);
				} else {
					currentPlayer -> health -= damage;
					
					printf("The %s was damaged %d HP!\n", currentPlayer -> name, damage);
					
					if ( currentPlayer -> health <= 0 ) {
						currentPlayer -> health = 0;
						
						printf("Your %s has no more HP and fainted!\n", currentPlayer -> name);
					} else {
						printf("\n\n");
					}
				}
			}
			break;
		
		default:
			damage = currentEnemy -> attack;
			currentPlayer -> health -= damage;
			printf("The %s attacked for %d!\n", currentEnemy -> name, damage);
			printf("Your %s was damaged %d HP!\n", currentPlayer -> name, damage);
			break;
	}
}


//Function: switchMonster = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
monster* switchMonster (int index, monster* head) {
	
	monster* temp = head;

	//Assuming that we don't consider 0 to be a position
	while ( !(index == 1 ) ) {
		if (temp == NULL) {
			return NULL;
		}
		temp = temp->next;
		index--;
	}
	
	return temp;
} //End of: switchMonster



//FUNCTION: Status
void status(monster* ally, monster* enemy) {
    printf("Your monster: %s\n", ally -> name);
		printf("\tHealth: %d\n", ally -> health);
		printf("\tSpeed: %d\n", ally -> speed);
		
		printf("\n\tV.S.\n\n");
		
		printf("Enemy monster: %s\n", enemy -> name);
		printf("\tHealth: %d\n", enemy -> health);
		printf("\tSpeed: %d\n", enemy -> speed);
		printf("\n");
}
