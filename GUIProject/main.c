#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


//GtkWidget *g_enemy_sel_list_box;
//GtkListStore *g_enemy_liststore;

//Label for fight screen
GtkWidget *g_lbl_user_name;
GtkWidget *g_lbl_enemy_name;
GtkWidget *g_lbl_user_decision;
GtkWidget *g_lbl_enemy_decision;
GtkWidget *g_lbl_result;
GtkWidget *g_lbl_user_hp;
GtkWidget *g_lbl_enemy_hp;
GtkWidget *g_prgbar_user_hp;
GtkWidget *g_prgbar_enemy_hp;

GtkWidget *g_lbl_endmessage;

typedef struct _Data Data;
struct _Data
{
    GtkWidget *up;   /* Up button */
    GtkWidget *down; /* Down button */
    GtkWidget *tree; /* Tree view */
};

// Dictionary for User Selection widgets
typedef struct {
    GtkWidget *w_comboboxtext_options;
    GtkWidget *w_lbl_monster1;
    GtkWidget *w_lbl_monster2;
    GtkWidget *w_lbl_monster3;
    GtkWidget *w_lbl_monster4;
    GtkWidget *w_lbl_monster5;
    GtkWidget *w_lbl_monster6;
} app_widgets;


//Create Builders and Widgets for each View

//Main
GtkBuilder      *builderM; 
GtkWidget       *windowM;

//User Selection
GtkBuilder      *builderS; 
GtkWidget       *windowS;

//Enemy Selection
GtkBuilder      *builderE; 
GtkWidget       *windowE;

//Battle
GtkBuilder      *builderB; 
GtkWidget       *windowB;

//Finish
GtkBuilder      *builderF; 
GtkWidget       *windowF;


enum {

  LIST_ITEM = 0,
  N_COLUMNS
};

typedef struct monster
{
	char name[64];
	int attack;
	int defense;
	int speed;
	int health;
	struct monster* next;
} monster;

//Global Monster Vars
int monsterFileCount = 0;
monster* availableMonsterList = NULL;
monster* enemyMonsterList = NULL;

monster user;
monster enemy;

bool win = true;
bool over = false;

//GtkWidget *window;
GtkWidget *list;

GtkWidget *vbox;
GtkWidget *fixed;
GtkWidget *label;
GtkWidget *button;
GtkTreeSelection *selection; 



//Global Function Prototypes
monster* fileIO (FILE* );
//void load_enemy();

void open_window_main();

int main(int argc, char *argv[])
{
  //GtkBuilder      *builderM; 
  //GtkWidget       *window;

  gtk_init(&argc, &argv);

  open_window_main();

  return 0;
}

void restart()
{
    //TODO: CLEAN PAST DATA

    gtk_widget_hide(windowF);
    gtk_widget_show(windowM);
}

void open_window_main()
{
    builderM = gtk_builder_new();
    gtk_builder_add_from_file (builderM, "window_main.glade", NULL);

    windowM = GTK_WIDGET(gtk_builder_get_object(builderM, "window_main"));
    gtk_builder_connect_signals(builderM, NULL);

    g_object_unref(builderM);

    gtk_widget_show(windowM);                
    gtk_main();
}

// called when window is closed
void on_destroy()
{  
    for (int i = 0; i < 10; i++)
    {
        gtk_main_quit();
    }  
    
}

void open_window_selection()
{
  gtk_widget_hide(windowM);

  app_widgets *dict = g_slice_new(app_widgets);

  builderS = gtk_builder_new();
  gtk_builder_add_from_file (builderS, "window_selection.glade", NULL);

  windowS = GTK_WIDGET(gtk_builder_get_object(builderS, "window_selection"));

  // get pointers for dictionary to pass as signals to builder
  dict->w_comboboxtext_options = GTK_WIDGET(gtk_builder_get_object(builderS, "comboboxtext_options"));
  dict->w_lbl_monster1 = GTK_WIDGET(gtk_builder_get_object(builderS, "lbl_monster1"));
  dict->w_lbl_monster2 = GTK_WIDGET(gtk_builder_get_object(builderS, "lbl_monster2"));
  dict->w_lbl_monster3 = GTK_WIDGET(gtk_builder_get_object(builderS, "lbl_monster3"));
  dict->w_lbl_monster4 = GTK_WIDGET(gtk_builder_get_object(builderS, "lbl_monster4"));
  dict->w_lbl_monster5 = GTK_WIDGET(gtk_builder_get_object(builderS, "lbl_monster5"));
  dict->w_lbl_monster6 = GTK_WIDGET(gtk_builder_get_object(builderS, "lbl_monster6"));

  gtk_builder_connect_signals(builderS, dict);
  g_object_unref(builderS);

	gtk_widget_show(windowS); 

  gtk_main();

  g_slice_free(app_widgets, dict);         

}

void open_window_enemy_selection() 
{
  gtk_widget_hide(windowS);

  builderE = gtk_builder_new();
  gtk_builder_add_from_file (builderE, "window_enemy_selection.glade", NULL);

  windowE = GTK_WIDGET(gtk_builder_get_object(builderE, "window_enemy_selection"));
  gtk_builder_connect_signals(builderE, NULL);

  g_object_unref(builderE);
	gtk_widget_show(windowE);

  gtk_main();

}

void open_window_battle()
{
  gtk_widget_hide(windowE);

	builderB = gtk_builder_new();
	gtk_builder_add_from_file (builderB, "window_battle.glade", NULL);

	windowB = GTK_WIDGET(gtk_builder_get_object(builderB, "window_battle"));
	gtk_builder_connect_signals(builderB, NULL);

	//User
	g_lbl_user_name = GTK_WIDGET(gtk_builder_get_object(builderB, "lbl_user_name"));
  g_lbl_user_decision = GTK_WIDGET(gtk_builder_get_object(builderB, "lbl_user_decision"));
  g_lbl_user_hp = GTK_WIDGET(gtk_builder_get_object(builderB, "lbl_user_hp"));
  g_prgbar_user_hp = GTK_WIDGET(gtk_builder_get_object(builderB, "prgbar_user_hp"));

  //Enemy
  g_lbl_enemy_name = GTK_WIDGET(gtk_builder_get_object(builderB, "lbl_enemy_name"));
	g_lbl_enemy_decision = GTK_WIDGET(gtk_builder_get_object(builderB, "lbl_enemy_decision"));
  g_lbl_enemy_hp = GTK_WIDGET(gtk_builder_get_object(builderB, "lbl_enemy_hp"));
  g_prgbar_enemy_hp = GTK_WIDGET(gtk_builder_get_object(builderB, "prgbar_enemy_hp"));

	g_lbl_result = GTK_WIDGET(gtk_builder_get_object(builderB, "lbl_result"));


  strcpy(user.name, "Charizard");
  user.attack = 30;
  user.defense = 20;
  user.speed = 10;
  user.health = 100;

  strcpy(enemy.name, "Nidoqueen");
  enemy.attack = 40;
  enemy.defense = 20;
  enemy.speed = 10;
  enemy.health = 100;

	//Pull in current monsters into battle
  gtk_label_set_text(GTK_LABEL(g_lbl_user_name), user.name);
	gtk_label_set_text(GTK_LABEL(g_lbl_enemy_name), enemy.name);

  updateUserHp(&user);
  updateEnemyHp(&enemy);
  
	g_object_unref(builderB);
	gtk_widget_show(windowB);
  gtk_main();
            
}

//Battle actions: attack, defend, enemy move

void calculateBattle (int playerSelection, monster* currentPlayer, monster* currentEnemy) 
{
	//Set monster to have a 50/50 chance of attacking or defending
	int monsterChoice = ( rand() % 2 );
	int damage = 0;

  char userDecisionText[150] = "";
  char enemyDecisionText[150] = "";
  char result[150] = "";

  switch (playerSelection) {
  //Attacking
  case 1:
    //If the monster is defending
    if ( monsterChoice == 1 ) {
      sprintf(userDecisionText, "Your %s attacked the %s for %d!", currentPlayer -> name, currentEnemy -> name, currentPlayer -> attack);
      
      sprintf(enemyDecisionText,"The %s defended for %d!", currentEnemy -> name, currentEnemy -> defense);
      
      damage = ( currentPlayer -> attack - currentEnemy -> defense );
      
      if ( damage <= 0 ) {
        sprintf(result, "The %s blocked all your %s's attack.", currentEnemy -> name, currentPlayer -> name);
      } else {
        currentEnemy -> health -= damage;
        
        sprintf(result, "The %s was damaged %d HP!", currentEnemy -> name, damage);
        
        
        //Is enemy dead?
        if ( currentEnemy -> health <= 0 ) {
          currentEnemy -> health = 0;
          
          printf("The enemy has no more HP! The %s fainted...", currentEnemy -> name);
        } 
      }
    } else {
      //Check who attacks first
      if (currentPlayer -> speed >= currentEnemy -> speed) {
        damage = currentPlayer -> attack;
        currentEnemy -> health -= damage;
        
        sprintf(userDecisionText, "The %s took a full blow! Hit for %d!", currentEnemy -> name, damage);
        
        
        //Is enemy dead?
        if ( currentEnemy -> health <= 0 ) {
          currentEnemy -> health = 0;
          
          sprintf(result, "The enemy has no more HP! The %s fainted...", currentEnemy -> name);
        } else {
          damage = currentEnemy -> attack;
          currentPlayer -> health -= damage;
          
          sprintf(enemyDecisionText, "Your %s also took a full blow! Hit for %d!", currentPlayer -> name, damage);
          
          //Is the Player Dead?
          if ( currentPlayer -> health <= 0 ) {
            currentPlayer -> health = 0;
            
            sprintf(result, "Your %s has no more HP and fainted!", currentPlayer -> name);
          } 
        }
      } else { //If the enemy has higher Speed
        damage = currentEnemy -> attack;
        currentPlayer -> health -= damage;
        
        sprintf(enemyDecisionText, "Your %s took a full blow! Hit for %d!", currentPlayer -> name, damage);

        //Is player dead?
        if (currentPlayer -> health <= 0) {
          currentPlayer -> health = 0;
          
          sprintf(result, "Your %s has no more HP! The %s fainted...", currentPlayer -> name, currentPlayer -> name);
          return;
        } else {
          damage = currentPlayer -> attack;
          currentEnemy -> health -= damage;
          
          sprintf(userDecisionText, "The %s also took a full blow! Hit for %d!", currentEnemy -> name, damage);
          
          //Is enemy dead?
          if ( currentEnemy -> health <= 0 ) {
            currentEnemy -> health = 0;
            
            sprintf(result, "The enemy has no more HP! The %s fainted...", currentEnemy -> name);
          } 
        }
      }
    }   
    break;    
  // Defending
  case 2:
    if ( monsterChoice == 1 ) {
      
      sprintf(result, "Both monsters took a defensive stance! Nothing occured!");
    } else {
      
      sprintf(enemyDecisionText, "The enemy %s attacked the %s for %d!", currentEnemy -> name, currentPlayer -> name, currentEnemy -> attack);
      
      sprintf(userDecisionText, "Your %s defended for %d!", currentPlayer -> name, currentPlayer -> defense);
      
      damage = ( currentEnemy -> attack - currentPlayer -> defense );
      
      if ( damage <= 0 ) {
        sprintf(result, "Your %s blocked all of the %s's attack.", currentPlayer -> name, currentEnemy -> name);
      } else {
        currentPlayer -> health -= damage;
        
        sprintf(result, "The %s was damaged %d HP!", currentPlayer -> name, damage);
        
        if ( currentPlayer -> health <= 0 ) {
          currentPlayer -> health = 0;
          
          sprintf(result, "Your %s has no more HP and fainted!", currentPlayer -> name);
        } 
      }
    }
    break;
  
  default:
    damage = currentEnemy -> attack;
    currentPlayer -> health -= damage;
    sprintf(enemyDecisionText, "The %s attacked for %d!", currentEnemy -> name, damage);
    sprintf(userDecisionText, "Your %s was damaged %d HP!", currentPlayer -> name, damage);
    break;
	}

  gtk_label_set_text(GTK_LABEL(g_lbl_user_decision), userDecisionText);
  gtk_label_set_text(GTK_LABEL(g_lbl_enemy_decision), enemyDecisionText);
  gtk_label_set_text(GTK_LABEL(g_lbl_result), result);

  checkHealth(currentPlayer, currentEnemy);
}

void on_btn_attack_clicked()
{
  calculateBattle (1, &user, &enemy);
}

void on_btn_defend_clicked()
{
  calculateBattle(2, &user, &enemy);
}


void updateUserHp(monster* currentPlayer)
{
  char userHealth[4];
  sprintf(userHealth, "%d", currentPlayer -> health);
  gtk_label_set_text(GTK_LABEL(g_lbl_user_hp), userHealth);
  double progressFraction = currentPlayer -> health / 100.0;
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(g_prgbar_user_hp), progressFraction);
}

void updateEnemyHp(monster* currentEnemy)
{
  char enemyHealth[4];
  sprintf(enemyHealth, "%d", currentEnemy -> health);
  gtk_label_set_text(GTK_LABEL(g_lbl_enemy_hp), enemyHealth);
  double progressFraction = currentEnemy -> health / 100.0;
  gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(g_prgbar_enemy_hp), progressFraction);
}

void checkHealth(monster* currentPlayer, monster* currentEnemy)
{
  updateUserHp(currentPlayer);
  updateEnemyHp(currentEnemy);

  if (currentEnemy -> health <= 0)
  {
    win = true;
    over = true;
  }
  else if (currentPlayer -> health <= 0)
  {
    win = false;
    over = true;
  }  
}

// Check if the battle is over
void battle_over()
{
  if (over)
  {
    end_battle();
  }
  else
  {
    gtk_label_set_text(GTK_LABEL(g_lbl_result), "Please finish the battle before clicking 'Battle Over'");
    return;
  }
  
  
}

// Add monsters selected to label list
// Cannot detect button to label mapping so have to multiple by number of selection choices
void on_btn_select1_clicked(GtkButton *button, app_widgets *app_wdgts)
{
	gchar *item_text = 0;	// selected item text from text combo box
	
	// get selected item text from GtkComboBoxText object
	item_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(app_wdgts->w_comboboxtext_options));
	if (item_text == NULL) {
		// return if no text found in combo box
		return;
	}
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_monster1), item_text);
	// free up dynamically allocated memory
	g_free(item_text);
  gtk_widget_set_sensitive (button, FALSE);
}
void on_btn_select2_clicked(GtkButton *button, app_widgets *app_wdgts)
{
	gchar *item_text = 0;	
	item_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(app_wdgts->w_comboboxtext_options));
	if (item_text == NULL) {
		return;
	}
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_monster2), item_text);
	g_free(item_text);
  gtk_widget_set_sensitive (button, FALSE);
}
void on_btn_select3_clicked(GtkButton *button, app_widgets *app_wdgts)
{
	gchar *item_text = 0;	
	item_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(app_wdgts->w_comboboxtext_options));
	if (item_text == NULL) {
		return;
	}
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_monster3), item_text);
	g_free(item_text);
  gtk_widget_set_sensitive (button, FALSE);
}
void on_btn_select4_clicked(GtkButton *button, app_widgets *app_wdgts)
{
	gchar *item_text = 0;	
	item_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(app_wdgts->w_comboboxtext_options));
	if (item_text == NULL) {
		return;
	}
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_monster4), item_text);
	g_free(item_text);
  gtk_widget_set_sensitive (button, FALSE);
}
void on_btn_select5_clicked(GtkButton *button, app_widgets *app_wdgts)
{
	gchar *item_text = 0;	
	item_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(app_wdgts->w_comboboxtext_options));
	if (item_text == NULL) {
		return;
	}
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_monster5), item_text);
	g_free(item_text);
  gtk_widget_set_sensitive (button, FALSE);
}
void on_btn_select6_clicked(GtkButton *button, app_widgets *app_wdgts)
{
	gchar *item_text = 0;	
	item_text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(app_wdgts->w_comboboxtext_options));
	if (item_text == NULL) {
		return;
	}
	gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_monster6), item_text);
	g_free(item_text);
  gtk_widget_set_sensitive (button, FALSE);
}

void open_window_finish()
{
  gtk_widget_hide(windowB);

  builderF = gtk_builder_new();
  gtk_builder_add_from_file (builderF, "window_finish.glade", NULL);

  windowF = GTK_WIDGET(gtk_builder_get_object(builderF, "window_finish"));
  gtk_builder_connect_signals(builderF, NULL);

  g_lbl_endmessage = GTK_WIDGET(gtk_builder_get_object(builderF, "lbl_endmessage"));

  g_object_unref(builderF);

  // Use global variable to see if won or loss
  if (win)
  {
      gtk_label_set_text(GTK_LABEL(g_lbl_endmessage), "Congratulations,\n You Won!");
  }
  else
  {
      gtk_label_set_text(GTK_LABEL(g_lbl_endmessage), "Sorry,\n You Lost!");
  }
  
  
  gtk_widget_show(windowF);                
}

//Events from buttons from glade
void on_btn_start_clicked()
{
  open_window_selection();
}

void on_btn_user_finalized_clicked()
{
  open_window_enemy_selection();
}

void on_btn_enemy_fight_clicked()
{
  open_window_battle();
}

void on_btn_over_clicked()
{
  battle_over();
}

void end_battle()
{
  open_window_finish();
}








// Below does not work with GTK. It works in the console version but as soon as 
// gtk_init() is called, you will have segmentation faults.


monster* fileIO (FILE* MONSTERLIST) {
  // Minimize
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

    //getline(&line, &bufsize, MONSTERLIST); //Read the first line (Name)
    //sscanf( line, " %[^\r]s", head -> name ); //Store first line into the first node of the linked list
    
    //getline(&line, &bufsize, MONSTERLIST); //Read next line (All other interger stats)
    //sscanf(line, "%d\t%d\t%d", &(head -> attack), &(head -> defense), &(head -> speed)); //This uses the scanf function to read the input buffer as integers using %d

    getline(&line, &bufsize, MONSTERLIST);
    sscanf(line, "%s\t%d\t%d\t%d", head -> name, &(head -> attack), &(head -> defense), &(head -> speed));

    head -> health = 100;
    
    //getline(&line, &bufsize, MONSTERLIST); //Read the empty line in the text file
    monsterFileCount ++;
    
    int i = 0;

    //fscanf (MONSTERLIST, "%d", &i);

    //While Loop to keep adding monsters to the Linked List...
    while (!feof(MONSTERLIST)) { //While NOT end of file
      
      
      //Create a Temporary node
      monster* tempMons = (monster*)malloc(sizeof(monster));

      //getline(&line, &bufsize, MONSTERLIST); //Read the first line (Name)
      //sscanf( line, "%[^\r]s", tempMons -> name ); //Store first line into the first node of the linked list
      
      getline(&line, &bufsize, MONSTERLIST); //Read next line (All other interger stats)
      sscanf(line, "%s\t%d\t%d\t%d", tempMons -> name, &(tempMons -> attack), &(tempMons -> defense), &(tempMons -> speed));  //This uses the scanf function to read the input buffer as integers using %d
      
      //fscanf(MONSTERLIST, "%[^\r]s %d %d %d", tempMons -> name, &(tempMons -> attack), &(tempMons -> defense), &(tempMons -> speed));

      tempMons -> health = 100;
      
      //getline(&line, &bufsize, MONSTERLIST); //Read the empty line in the text file
      
      printf("\nTemp name %s!!!!!\n", tempMons->name);

      //Add temp to the linked list...
      current -> next = tempMons;
      current = tempMons;
      monsterFileCount++;

      free(tempMons);
          
    }

    fclose(MONSTERLIST);
    
    //Return the head of the entire monstersLinkedList
    return head;
}











// Code that caused bugs or was superseceded. Contains reading files, listboxes, treeviews, and 
// attempting to have dynamic data on with the windows.


/*
void enemyMove()
{
  bool enemyDecision = false;
	char enemyDecisionText[100];
	if (enemyDecision)
	{
		enemyAttack();
	}
	else
	{
    enemyDefend();
	}	
}

  bool enemyDecision = false;
	char enemyDecisionText[100];

  int defend = enemy.defense;
  char buffer[3];
  sprintf(buffer, "%d", defend);


  strcpy(enemyDecisionText, "The enemy has decided to defend. They blocked for: ");
  strcat(enemyDecisionText, buffer);	

  gtk_label_set_text(GTK_LABEL(g_lbl_enemy_decision), enemyDecisionText);
}
*/

/*
// Read passed label when button click
void read_label (GtkButton *button, gpointer   user_data)
{
  printf("\n  HERE read label:   \n");
  printf(  gtk_label_get_text(GTK_LABEL(user_data)));
  printf("\n  HERE DONE read label text.   \n");

}
*/

/*
void init_list(GtkWidget *list) {

  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkListStore *store;

  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes("List Items",  renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_column_set_title(column, "Title Enemy Name");

  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list),  GTK_TREE_MODEL(store));

  g_object_unref(store);
}*/


/*
// void open_window_enemy_selection()
// {

//     gtk_widget_hide(windowS);

//     builderE = gtk_builder_new();
//     gtk_builder_add_from_file (builderE, "window_enemy_selection.glade", NULL);

//     windowE = GTK_WIDGET(gtk_builder_get_object(builderE, "window_enemy_selection"));
//     gtk_builder_connect_signals(builderE, NULL);


//     g_enemy_sel_list_box = GTK_WIDGET(gtk_builder_get_object(builderE, "user_treeview"));
    



//     //init_list(g_enemy_sel_list_box);
  
//     add_to_list(g_enemy_sel_list_box, "Aliens");
//     add_to_list(g_enemy_sel_list_box, "Leon");
//     add_to_list(g_enemy_sel_list_box, "The Verdict");
//     add_to_list(g_enemy_sel_list_box, "North Face");
//     add_to_list(g_enemy_sel_list_box, "Der Untergang");





//     // monster * current = (monster*)malloc(sizeof(monster*));
//     // FILE* ENEMYMONSTERLIST = fopen("Enemies.txt", "r"); //Player Monster File Variable
// 	// enemyMonsterList = fileIO(ENEMYMONSTERLIST);

//     // int monsterFileCheck = 0;
//     // while(monsterFileCheck != monsterFileCount)
//     // {
// 	//     if(monsterFileCheck == 0)
// 	//     {
// 	// 	    current = enemyMonsterList;
// 	//     }
// 	//     //if(true)
//     //     //{
//     //         //GtkWidget *item;

//     //         //item = gtk_list_item_new
//     //         //(current->name);

//     //         //gtk_container_add(GTK_CONTAINER(g_enemy_sel_list_box), item);

//     //         //gtk_widget_show(item);
//     //     //}
// 	//     current = current->next;
// 	//     monsterFileCheck++;	
//     // }

//     g_object_unref(builderE);

//     gtk_widget_show(windowE);                
// }


void load_enemy()
{

    monster * current = (monster*)malloc(sizeof(monster*));
    FILE* ENEMYMONSTERLIST = fopen("Enemies.txt", "r"); //Player Monster File Variable
	enemyMonsterList = fileIO(ENEMYMONSTERLIST);

    int monsterFileCheck = 0;
    while(monsterFileCheck != monsterFileCount)
    {
	    if(monsterFileCheck == 0)
	    {
		    current = enemyMonsterList;
	    }
	    add_to_list(list, current->name);
	    current = current->next;
	    monsterFileCheck++;	
    }
}
*/
/*
void load_user()
{

    monster * current = (monster*)malloc(sizeof(monster*));
    FILE* MONSTERLIST = fopen("Monsters.txt", "r"); //Player Monster File Variable
	availableMonsterList = fileIO(MONSTERLIST);

}
*/


//     ///////////////////////////////GtkWidget *window;
//     GtkWidget *view;

//     //GtkWidget *window;
//     GtkWidget *halign;
//     //GtkWidget *btn;


// //printf("HERE!!!!!!!   01111");

//     ///////////////////////window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
//     gtk_widget_hide(windowM);

//     Data data;

//     builderS = gtk_builder_new();

//     gtk_builder_add_from_file (builderS, "window_selection2.glade", NULL);
//     windowS = GTK_WIDGET(gtk_builder_get_object(builderS, "window_selection"));
   

//     gtk_window_set_position(GTK_WINDOW(windowS), GTK_WIN_POS_CENTER);
//     gtk_container_set_border_width(GTK_CONTAINER(windowS), 10);
//     gtk_window_set_default_size(GTK_WINDOW(windowS), 670, 550);

//     g_signal_connect(windowS, "delete_event", gtk_main_quit, NULL); /* dirty */




//     view = create_view_and_model();

//     data.down = NULL;
//     data.up = NULL;
//     data.tree = view;

//     gtk_builder_connect_signals(builderS, &data);

//     fixed = gtk_fixed_new();
//     gtk_fixed_put (GTK_FIXED(fixed), view, 14, 44);

//     //gtk_container_add(GTK_CONTAINER(windowS), view);

//      //selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(view));

//      //gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);

//      //g_signal_connect(selection, "changed", G_CALLBACK(on_changed), label);

//      g_signal_connect(G_OBJECT (windowS), "destroy", G_CALLBACK(on_destroy), NULL);

//     //button = gtk_button_new();
//     button = gtk_button_new_with_label("Continue");
//     gtk_widget_set_size_request(button, 130, 100);
  



//     //gtk_button_set_label (button, "Continue");
    
//     g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(cb_move), NULL);
//     //g_signal_connect(selection, "clicked", G_CALLBACK(on_changed), button);
    
//     g_signal_connect(G_OBJECT(windowS), "destroy",  G_CALLBACK(gtk_main_quit), NULL);

//     gtk_fixed_put (GTK_FIXED(fixed), button, 514, 244);

//     gtk_container_add(GTK_CONTAINER(windowS), fixed);


    // g_object_unref(builderS);

    // gtk_widget_show_all(windowS);


/*
int open_window_enemy_selection() 
{
  //gtk_init(&argc, &argv);

  gtk_widget_hide(windowS);

  builderE = gtk_builder_new();
  gtk_builder_add_from_file (builderE, "window_enemy_selection2.glade", NULL);

  windowE = GTK_WIDGET(gtk_builder_get_object(builderE, "window_enemy_selection"));

  //window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  list = gtk_tree_view_new();

  //gtk_window_set_title(GTK_WINDOW(windowE), "List view");
  gtk_window_set_position(GTK_WINDOW(windowE), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(windowE), 10);
  gtk_window_set_default_size(GTK_WINDOW(windowE), 670, 550);

  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

  //vbox = gtk_vbox_new(FALSE, 0);

  fixed = gtk_fixed_new();

  gtk_fixed_put (GTK_FIXED(fixed), list, 14, 44);

  //gtk_box_pack_start(GTK_BOX(vbox), list, TRUE, TRUE, 5);

  label = gtk_label_new("");
  //gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 5);
  gtk_fixed_put (GTK_FIXED(fixed), label, 300, 120);

  gtk_container_add(GTK_CONTAINER(windowE), fixed);

  init_list(list);

  monster * current = (monster*)malloc(sizeof(monster*));
  FILE* ENEMYMONSTERLIST = fopen("Enemies.txt", "r"); //Player Monster File Variable
  enemyMonsterList = fileIO(ENEMYMONSTERLIST);

  int monsterFileCheck = 0;
  while(monsterFileCheck != monsterFileCount)
  {
    if(monsterFileCheck == 0)
    {
      current = enemyMonsterList;
    }
      add_to_list(list, current->name);

    current = current->next;
    monsterFileCheck++;	
  }


  //add_to_list(list, "Aliens");
  //add_to_list(list, "Leon");
  //add_to_list(list, "The Verdict");
  //add_to_list(list, "North Face");
  //add_to_list(list, "Der Untergang");

  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  gtk_tree_selection_set_mode(selection, GTK_SELECTION_MULTIPLE);

  gtk_builder_connect_signals(builderE, NULL);

  //g_signal_connect(selection, "changed", G_CALLBACK(on_changed), label);

  g_signal_connect(G_OBJECT (windowE), "destroy", G_CALLBACK(on_destroy), NULL);


  g_object_unref(builderE);
  gtk_widget_show_all(windowE);

  //gtk_main();

}
*/

/*
void enemyAttack()
{
  
  char userDecisionText[100];

  int userAttack = user.attack;
  int enemyDefense = enemy.defense;

  if (userAttack > enemyDefense)
  {
    enemy.health -= userAttack - enemyDefense;
  }
    
  sprintf(userDecisionText, "You have decided to attack. You did damage: %d", userAttack);

  gtk_label_set_text(GTK_LABEL(g_lbl_user_decision), userDecisionText);

  enemyMove();
  checkHealth();
  
  bool enemyDecision = false;
	char enemyDecisionText[100];

  int attack = enemy.attack;
  char buffer[3];
  sprintf(buffer, "%d", attack);

  strcpy(enemyDecisionText, "The enemy has decided to attack. They did damage: ");
  strcat(enemyDecisionText, buffer);

  gtk_label_set_text(GTK_LABEL(g_lbl_enemy_decision), enemyDecisionText);
}

void enemyDefend()
{

  char userDecisionText[100];

  int userDefense = user.defense;
  int enemyAttack = enemy.attack;

  if (userDefense < enemyAttack)
  {
    user.health -= enemyAttack - userDefense;
  }

	char buffer[3];
  sprintf(buffer, "%d", userDefense);

  strcpy(userDecisionText, "You have decided to defend. You blocked damage: ");
  strcat(userDecisionText, buffer);

  gtk_label_set_text(GTK_LABEL(g_lbl_user_decision), userDecisionText);

  enemyMove();
  checkHealth();

  */