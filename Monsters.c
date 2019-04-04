#include <stdio.h>
#include <stdlib.h>

//MAIN ========================================================================
int main()
{	
	//FUNCTION PROTOTYPES =====================================================
	Ally* insertAlly(Ally*); //add a new ally
	Ally* removeAlly(Ally*); //remove an existing ally
	Ally* peekAllies(Ally*); //view all allies
	int sizeAlly(Ally*); //view the number of allies
	int isEmptyAlly(Ally*); //see if ally linked list is empty
	int randomNum(); //returns a random number from the API
	
	//MONSTER STRUCTURES ======================================================
	typedef struct Ememy
	{
		char* name;
	} Enemy;
	
	typedef struct Ally
	{
		char* name;
		struct Ally* next;
	} Ally;
	
	//VARIABLES ===============================================================
	Enemy enemies[4] = {NULL}; //create enemy array
	Ally* allies = {NULL}; //create ally linked list
	Ally* current = {NULL}; //create current ally pointer
	
	//POPULATE VARIABLES ======================================================
	//populate Ememy array
	
	//EXECUTION START =========================================================
	printf("Welcome to our CNIT 315 Final Project!");
}

//insertAlly FUNCTION =========================================================

//removeAlly FUNCTION =========================================================

//peekAllies FUNCTION =========================================================

//sizeAlly FUNCTION ===========================================================

//isEmptyAlly FUNCTION ========================================================

//randomNum FUNCTION ==========================================================

