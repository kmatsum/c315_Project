#include <stdio.h>
#include <stdlib.h>



//Monster Structure = = = = = = = = = = = = = = = = = = = = = = = = = = = =
typedef struct Monster
{
	char* name;
	int health;
	struct Ally* Monster;
} Monster;
//END OF: Monster Structure = = = = = = = = = = = = = = = = = = = = = = = =


	
//FUNCTION: main  = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
int main()
{	
	//FUNCTION PROTOTYPES = = = = = = = = = = = = = = = = = = = = = = = = = = =
	Monster* insertAlly(Monster*); //add a new ally
	Monster* removeAlly(Monster*); //remove a preexisting ally
	Monster* peekAllies(Monster*); //view all allies
	
	int sizeAlly(Monster*); //view the number of allies
	int isEmptyAlly(Monster*); //see if ally linked list is empty
	int randomNum(); //returns a random number from the API
	//END OF: Function Prototypes = = = = = = = = = = = = = = = = = = = = = = =
	
	
	
	//Variables = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	Enemy enemies[4] = {NULL}; //create enemy array
	Monster* allies = {NULL}; //create ally linked list
	Monster* currentAlly = {NULL}; //create current ally pointer
	int currentEnemy = {NULL}; //index of current enemy
	//END OF: Variables = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	
	
	
	//Populate Variables  = = = = = = = = = = = = = = = = = = = = = = = = = = =
	//populate Ememy array
	
	//Game Code = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
	printf("Welcome to our CNIT 315 Final Project!");
	
	//END OF: Game Code
	
} //END OF: main

//FUNCTION: insertAlly  = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: removeAlly  = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: peekAllies  = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: sizeAlly  = = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: isEmptyAlly = = = = = = = = = = = = = = = = = = = = = = = = = = = =



//FUNCTION: randomNum = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


