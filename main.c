#include "header.h"
int debugMode;
/***************************************************************/
/* forward definition of functions */
void clearToEoln();

/* Read in until the first Non-White-Space character is Read */
/* The white space characters are:
 *      space, tab \t, newline \n, vertical tab \v,
 *      form feed \f, and carriage return \r
 */
/***************************************************************/
int getNextNWSChar ()
{
    int ch;
    
    ch = getc(stdin);
    if (ch == EOF || ch == '\n')
        return ch;
    while (isspace (ch))
    {
        ch = getc(stdin);
        if (ch == EOF || ch == '\n')
            return ch;
    }
    return ch;
}

/***************************************************************/
/* read in the next Positive Integer or error:    */
/*    we can count zero as a positive number */
int getPosInt ()
{
    int value = -1;
    
    /* clear white space characters */
    int ch;
    ch = getc(stdin);
    while (!isdigit(ch))
    {
        if ('\n' == ch)  /* error \n ==> no integer given */
            return -1;
        if (!isspace(ch)) /* error non white space ==> integer not given next */
        {
            clearToEoln();
            return -1;
        }
        ch = getc(stdin);
    }
    
    value = ch - '0';
    ch = getc(stdin);
    while (isdigit(ch))
    {
        value = value * 10 + ch - '0';
        ch = getc(stdin);
    }
    
    ungetc (ch, stdin);  /* put the last read character back in input stream */
    
    /* Integer value less than 0 is an error in this program */
    if (0 > value)
        clearToEoln();
    
    return value;
}

/***************************************************************/

/* read in the name until the end of the input */
char *getName()
{
    /* skip over the white space characters */
    int ch;
    ch = getc(stdin);
    while (isspace(ch))
    {
        if ('\n' == ch)  /* error \n ==> no integer given */
            return NULL;
        ch = getc(stdin);
    }
    
    char *word;
    int size;
    size = 10;
    word = (char *) malloc (sizeof(char) * size);
    
    // read in character-by-character until the newline is encountered
    int count = 0;
    
    while (ch != '\n')
    {
        if (count+1 >= size)
        {
            // to grow an array to make it "dynamically sized" using malloc
            char* temp;
            int i;
            size = size * 2;
            temp = (char *) malloc (sizeof(char) * size);
            
            // copy the characters to the new array
            for (i = 0 ; i < count ; i++)
                temp[i] = word[i];
            
            free (word);
            word = temp;
        }
        
        word[count] = ch;
        count++;
        word[count] = '\0';
        
        // read next character
        ch = getc(stdin);
    }
    
    if (count > 30)
    {
        count = 30;
        word[count] = '\0';
    }
    
    /* clear ending white space characters */
    while (isspace (word[count-1]))
    {
        count--;
        word[count] = '\0';
    }
    
    return word;
}

/***************************************************************/
/* Clear input until next End of Line Character - \n */
void clearToEoln()
{
    int ch;
    
    do {
        ch = getc(stdin);
    }
    while ((ch != '\n') && (ch != EOF));
}

/***************************************************************/
/* Print out a list of the commands for this program */
void printCommands()
{
    printf ("The commands for this program are:\n\n");
    printf ("q - to quit the program\n");
    printf ("? - to list the accepted commands\n");
    printf ("a <# burgers> <# salads> <name> - to add your order to the order list\n");
    printf ("c <# burgers> <# salads> <name> - to add a call-ahead order to the order list\n");
    printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
    printf ("r <# burgers> <# salads> - to retrieve the first waiting group whose order matches the items on the counter\n");
    printf ("l <name> - list how many orders are ahead of the named order\n");
    printf ("d - display the order list information\n");
    printf ("t <name> - display an estimated wait time for the given order name\n");
    
    /* clear input to End of Line */
    clearToEoln();
}

/***************************************************************/
int main (int argc, char **argv)
{
    int i;
    for (i=0; i< argc;i++)
    {
        if (strcmp (argv[i], "-d") == 0)
            debugMode = TRUE;
    }
    list* List = NULL;
    //char *input;
    int ch;
    
    
    printf ("Starting Fast Food Order Management Program\n\n");
    printf ("Enter command: ");
    
    while ((ch = getNextNWSChar ()) != EOF)
    {
        /* check for the various commands */
        if ('q' == ch)
        {
            printf ("Quitting Program\n");
            //clearList(&List);
            return (0);
        }
        else if ('?' == ch)
        {
            printCommands();
        }
        else if('a' == ch)
        {
            doAdd(&List);
        }
        else if('c' == ch)
        {
            doCallAhead(&List);
        }
        else if('w' == ch)
        {
            doWaiting(&List);
        }
        else if('r' == ch)
        {
            doRetrieve(&List);
        }
        else if('l' == ch)
        {
            doList(List);
        }
        else if('d' == ch)
        {
            doDisplay(List);
        }
        
        else if('t' == ch)
        {
            doEstimateTime(List);
        }
        
        else if('\n' == ch)
        {
            /* nothing entered on input line     *
             * do nothing, but don't give error  */
        }
        else
        {
            printf ("%c - in not a valid command\n", ch);
            printf ("For a list of valid commands, type ?\n");
            clearToEoln();
        }
        
        printf ("\nEnter command: ");
    }
    
    //clearList(&List);
    printf ("Quiting Program - EOF reached\n");
    return 1;
}
/***************************************************************/


