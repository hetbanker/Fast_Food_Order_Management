#include "header.h"
int debugMode;
/***************************************************************/
//Initializes the list
void initList(list** iList, char* name, int burgers, int salads, boolean inRestaurant)
{
    //allocate node
    *iList = (list*) malloc(sizeof(list));
    
    //access the elemeents from the struct
    (*iList)->name = name;    //get the name form the struct
    (*iList)->salads = salads;  //get the salad info from the struct
    (*iList)->burgers = burgers;   //get the burger info from the struct
    (*iList)->inRestaurant = inRestaurant;  //get the restautant info from the struct
    (*iList)->next = NULL;
}
/***************************************************************/
//debug information for all the functions
void debugInformation(list* List)
{
    //orinting the debug information, name and amount of burgers and salad
    printf("debug information: name: %s , burgers %d , salads %d, in restaurant: %d\n", List->name, List->burgers, List->salads, List->inRestaurant);
}

/***************************************************************/
//this function adds to the list
void addToList(list **List,  char* name, int burgers, int salads, boolean inRestaurant)
{
    list *front = *List;
    list *back = NULL;
    
    //go until the fron doesnt equal to null
    while (front != NULL)
    {
        //for the debug mode
        if(debugMode)
        {
            debugInformation(front);
        }
        //make the back equal to front
        back=front;
        //go thru the list
        front=front->next;
    }
    
    //creating a list
    list *newList;
    //intialize the list, access the elements from the list
    initList(&newList, name, burgers, salads, inRestaurant);
    
    //if the list is empty then then make the new list as head
    if(back==NULL)
    {
        *List=newList;
    }
    else
    {
        back->next=newList;
    }
}

/***************************************************************/
//this fucntion returns true or false, if the name exists then return false otherwise return false
boolean doesNameExist(list *List, char *name)
{
    //go until the list is empty
    while(List != NULL)
    {
        //print out debug info
        if(debugMode)
        {
            debugInformation(List);
        }
        
        //checks to see if the name matches the person already in the list
        if(strcmp(List->name, name) == 0) return TRUE;
    
        //go thru the list
        List = List->next;
    }
    return FALSE;  //otherwise return false
}
/***************************************************************/
//this function checks the status of the restaurant
boolean updateStatus(list **List, char *name)
{
    //intitialize the list here
    list *front= *List;
    
    //go until the list is empty
    while(front != NULL)
    {
        //if the debug mode is on the print out the debug information
        if(debugMode)
        {
            debugInformation(front);
        }
        //checks to see if the name already exists in the list
        if(strcmp(front->name, name) == 0)
        {
            //if ther person isnt in the list
            if (front->inRestaurant == FALSE)
            {
                //then make the in restarutant status to be true and return true
                front->inRestaurant = TRUE;
                return TRUE;
            }
            //othereise return false
            else return FALSE;
        }
        //goes to the next value in the list
        front=front->next;
    }
    //return false otherwise
    return FALSE;
}
/*************************************************************************************/
//this function removes the order which has less burgers and less salads and in the restaurant
char* retrieveAndRemove(list** List, int burger, int salad)
{
    //intiazlizing the list here
    list* front = *List;
    list* back = NULL;
    //if there is no one who has order less than the previously ordered made then return null
    char* name = NULL;
    
    //go until the list is empty
    while(front != NULL)
    {
        //for debug mode to turn on
        if(debugMode)
        {
            debugInformation(front);
        }
        //checks to see if the order has less burgers, salands and the person is in the restaurant
        if(front->burgers<=burger && front->salads<=salad && front->inRestaurant==TRUE)
        {
            //checks to see if the back is null
            if(back==NULL)
            {
                *List=front->next;
                name=front->name;
                free(front);   //deallocate some memory
                return name;
            }
            //otherwise make the backs next equal to fronts next
            else
            {
                back->next = front->next;
                name=front->name;
                free(front);  //deallocate some memory
                return name;
            }
        }
        //make the back equal to front
        back=front;
        
        //go thru the list
        front=front->next;
    }
    //if the is no one in the list then return null or return persons name
    return name;
}
/***************************************************************/
//number of orders are in the list
int countOrdersAhead(list* List, char* name)
{
    //intialize the order counter and set it = to 0
    int orderCounter = 0;
    //go until the list is empty
    while (List!=NULL)
    {
        //for debugmode
        if(debugMode)
        {
            debugInformation(List);
        }
        //if the name in the list are the same then print error
        if(strcmp(List->name, name) == 0) break;
        
        //go thru the whole list
        List=List->next;
        //increment the order couter by 1
        orderCounter++;
    }
    //return an interger, number of orders ahead
    return orderCounter;
}
/***************************************************************/
//this function displays the time
int displayWaitingTime(list *List, char *name)
{
    //intialize the burder, salad and totalWaitingTime to be zero
    int burger = 0;
    int salad = 0;
    int totalWaitingTime=0;
    
    //go until the list isnt empty
    while(List!=NULL)
    {
        //if the debug mode is on then print out the debug info
        if (debugMode)
        {
            debugInformation(List); //call the debug info
        }
        
        //if the name is the same then break out and print an error
        if(strcmp(List->name, name)==0) break;
        
        //add the total number of burgers and salads in the list
        burger=burger+List->burgers;
        salad=salad+List->salads;
        //go thru the entire list
        List=List->next; //go to the next value
    }
    
    //total waiting time of both burgers and salads
    totalWaitingTime = burger*10 + salad*5;
    return totalWaitingTime; //return the total waiting time
}
/***************************************************************/
//this function displays all the orders ahead of the person
void displayOrdersAhead(list *List, char *name)
{
    //go until the list isnt empty
    while (List != NULL)
    {
        //print out the debug info
        if(debugMode)
        {
            debugInformation(List);
        }
        //if the list has the same name then break out
        if (strcmp(List->name, name) == 0) break;
        //otherwise print the info for the person and their order
        else
        {
            printf("Person: %s, Burgers: %d, Salads: %d \n",List->name, List->burgers, List->salads);
        }
        List=List->next;  //go to the next value in the list
    }
}
/***************************************************************/
//this function displays all the orders currently in the list and returns the total number of orders
int displayListInformation(list *List)
{
    //intialize the totalOrder to zero
    int totalOrders=0;
    //go until the list is empty
    while (List != NULL)
    {
        //if the debug mode is on then turn on the debug mode
        if(debugMode)
        {
            //calls the debug function and prints the debug information
            debugInformation(List);
        }
        
        //printing out debug info
        printf("Name: %s, Burgers: %d, Salads: %d, In restaurant %d: \n", List->name, List->burgers, List->salads, List->inRestaurant);
        List = List->next; //go to the next value
        totalOrders++;  //increment the order counter
    }
    return totalOrders;  //return the number of orders in the list
}
/***************************************************************/

