#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*************************************************************/
typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;
extern int debugMode;
/*************************************************************/
typedef struct nodeStruct {
    int burgers;   //for burgers
    int salads;    //for salads
    char *name;    //for name
    boolean inRestaurant;   //checks to see if the person is in restaurant
    struct nodeStruct *next;  //for next field
} list;

/*************************************************************/
//functions in linkedList.c
void initList(list** iList, char* name, int burgers, int salads, boolean inRestaurant);
void debugInformation(list* List);
void addToList(list **List,  char* name, int burgers, int salads, boolean inRestaurant);
boolean doesNameExist(list *List, char *name);
boolean updateStatus(list **List, char *name);
char* retrieveAndRemove(list** List, int burger, int salad);
int countOrdersAhead(list* List, char* name);
int displayWaitingTime(list *List, char *name);
int displayListInformation(list *List);
void displayOrdersAhead(list *List, char *name);

/*************************************************************/
//functions in main.c
void clearToEoln();
int getNextNWSChar ();
int getPosInt ();
char *getName();
void printCommands();

/*************************************************************/
//functions givenFunctions
void doAdd (list **List);
void doCallAhead (list **List);
void doWaiting (list **List);
void doRetrieve (list **List);
void doList (list *List);
void doDisplay (list *List);
void doEstimateTime(list *List);

/*************************************************************/
