#include <stdio.h>
#include <stdlib.h>



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
	Enemy enemies[4] = {NULL}; //create enemy array
	Ally* allies = {NULL}; //create ally linked list
	Ally* current = {NULL}; //create current ally pointer
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


