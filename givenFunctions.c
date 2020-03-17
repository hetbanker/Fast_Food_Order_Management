#include "header.h"
int debugMode;
/****************************************************************/
void doAdd (list **List)
{
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0)
    {
        printf ("Error: Add command requires an integer value of at least 0\n");
        printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }
    
    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0)
    {
        printf ("Error: Add command requires an integer value of at least 0\n");
        printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }
    
    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }
    // add code to perform this operation here
    if(doesNameExist(*List, name))
    {
        printf("Error: the name already exists. Please pick a different name.\n");
        
    }
    
    else
    {
        printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
        //add to the name to list
        addToList(List, name, NumBurgers, NumSalads, TRUE);
    }
    
}
/****************************************************************/
void doCallAhead (list **List)
{
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 0\n");
        printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }
    
    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 0\n");
        printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }
    
    // add code to perform this operation here
    //checks to see if the name already exists in the list
    if(doesNameExist(*List, name))
    {
        printf("Error: the name already exists. Please pick a different name.\n");
    }
    else
    {
        printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);
        //add the name to the list
        addToList(List, name, NumBurgers, NumSalads, FALSE);
    }
    
}
/****************************************************************/
void doWaiting (list **List)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Waiting command requires a name to be given\n");
        printf ("Waiting command is of form: w <name>\n");
        printf ("  where: <name> is the name of the group that is now waiting\n");
        return;
    }

    // add code to perform this operation here
    //checks to see if the name already exists in the list
    if(!doesNameExist(*List, name))
    {
        printf("There is no one in the list of that name.\n");
    }
    else
    {
        //checks to see if there a call ahead order in the list
        if (!updateStatus(List, name))
        {
            printf("There is no call ahead order.\n");
        }
        else
        {
            printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);
        }
    }
    //delete the name from the list
    free(name);
}
/****************************************************************/
void doRetrieve (list **List)
{
    /* get info of prepared food ready on the counter from input */
    int PreparedBurgers = getPosInt();
    if (PreparedBurgers < 0)
    {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
        printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
        printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
        return;
    }
    
    int PreparedSalads = getPosInt();
    if (PreparedSalads < 0)
    {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
        printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
        printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
        return;
    }
    
    clearToEoln();
    printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers ,PreparedSalads);
    
    // add code to perform this operation here
    char *name = retrieveAndRemove(List, PreparedBurgers, PreparedSalads);
    //checks to see if name isnt null
    if (name != NULL)
    {
        printf("Removing : %s \n", name);
        free(name); //delete the name from the list
    }
    else
    {
        printf("There is no one in the list that can get the order.\n");
    }
    
}
/****************************************************************/
void doList (list *List)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: l <name>\n");
        printf ("  where: <name> is the name of the order to inquire about\n");
        return;
    }
    
    printf ("Order for \"%s\" is behind the following orders\n", name);
    
    // add code to perform this operation here
    if(!doesNameExist(List, name))
    {
        printf("Error: the name doesn't exist in the list.\n");
    }
    else
    {
        //displat the number of orders in the list
        displayOrdersAhead(List, name);
        printf("There are %d orders ahead of %s\n", countOrdersAhead(List, name),name);
    }
    //delete the list
    free(name);
}

/****************************************************************/
void doDisplay (list *List)
{
    clearToEoln();
    printf ("\nDisplay information about all orders:\n");
    printf ("******************************************************************\n");
    
    // add code to perform this operation here
    printf("Total number of orders in the list: %d\n", displayListInformation(List));
    printf ("******************************************************************\n");
}

/****************************************************************/
void doEstimateTime(list *List)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: t <name>\n");
        printf ("  where: <name> is the name of the order to inquire about\n");
        return;
    }
    
    // add code to perform this operation here
    //if the name is already in the list the print the following messege
    if(!doesNameExist(List, name))
    {
        printf("Error: the name doesn't exist in the list.\n");
    }
    //otherwise display the waiting time for orders
    else
    {
        //displayOrdersAhead(List, name);
        printf("Total estimated time for the %s is %d minutes:\n", name, displayWaitingTime(List, name));
    }
    
}
/****************************************************************/
