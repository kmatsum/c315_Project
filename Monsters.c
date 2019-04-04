#include <stdio.h>
#include <stdlib.h>

//MAIN ========================================================================
int main()
{	
	//FUNCTION PROTOTYPES =====================================================
	void insertAlly(); //add a new ally
	void removeAlly(); //remove an existing ally
	void peekAllies(); //view all allies
	void sizeAlly(); //view the number of allies
	void isEmptyAlly(); //see if ally linked list is empty
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
	
	typedef struct AllyList
	{
		Ally* head;
	} AllyList;
	
	//VARIABLES ===============================================================
	Enemy enemies[4] = {NULL};
	AllyList* allies = (AllyList*)malloc(sizeof(AllyList));
	
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

