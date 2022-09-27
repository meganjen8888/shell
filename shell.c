//starter code

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 80 /* 80 chars per line, per command, should be enough. */
 
/**
 * setup() reads in the next command line, separating it into distinct tokens
 * using whitespace as delimiters. setup() sets the args parameter as a
 * null-terminated string.
 */
void setup(char inputBuffer[], char *args[],int *background)
{
    //introducing all the integer variables
    int length, /* # of characters in the command line */
        i,      /* loop index for accessing inputBuffer array */
        start,  /* index where beginning of next command parameter is */
        ct;     /* index of where to place the next parameter into args[] */
   
    ct = 0; //ct variable is called 0
    /* read what the user enters on the command line */
    length = read(STDIN_FILENO, inputBuffer, MAX_LINE); 
    //read() reads data previously written to a file. 
    //in this line, STDIN_FILENO is the file descriptor.
    //inputBuffer is what they read data from.
    //cnt is the length of the buffer.
    start = -1; //next command parameter is set to -1
    if (length == 0) //i think that's the length of the user input
        //printf("test"); //that would probably exit straightaway
        exit(0);            /* ^d was entered, end of user command stream */
    if (length < 0){
        perror("error reading the command");
        exit(-1);           /* terminate with error code of -1 */
    }
    /* examine every character in the inputBuffer */
        if ((strncmp(inputBuffer, "exit", 4))==0) {
            //printf("test");
            exit(0); //ok cool
    }
    char *temp = malloc(strlen(inputBuffer));
    if (strncmp("yell", inputBuffer, strlen(inputBuffer))) {
        printf("%s", strncpy(temp, inputBuffer+5, strlen(inputBuffer)));//now to make it caps
    }
    for (i=0;i<length;i++) {
        switch (inputBuffer[i]){
          case ' ':
          case '\t' :               /* argument separators */
            if(start != -1){
                    args[ct] = &inputBuffer[start];    /* set up pointer */
                    //printf("test");
                    //okay, WHAT? so i entered this line to test it out, and seems like it does listen
                    //when i type it after a command.
                ct++;
            }
            inputBuffer[i] = '\0'; /* add a null char; make a C string */
            start = -1;
            break;
          case '\n':                 /* should be the final char examined */
            if (start != -1){
                    args[ct] = &inputBuffer[start];    
                ct++;
            }
                inputBuffer[i] = '\0';
                args[ct] = NULL; /* no more arguments to this command */
            break;
          default :             /* some other character */
            if (start == -1)
                start = i;
            if (inputBuffer[i] == '&'){
                *background  = 1;
                start = -1;
                inputBuffer[i] = '\0';
            }
          }
     }   
     args[ct] = NULL; /* just in case the input line was > 80 */ 
}
int main(void)
{
    printf("Welcome to mjshell. My pid is %d", getpid());
    printf(".\n");
char inputBuffer[MAX_LINE];      /* buffer to hold the command entered */
    int background;              /* equals 1 if a command is followed by '&' */
    char *args[(MAX_LINE/2)+1];  /* command line (of 80) has max of 40 arguments */
    int number_of_commands=1;

    while (1){            /* Program terminates normally inside setup */
       background = 0;
       printf("mjshell[%d", number_of_commands);
       printf("]:\n");//apparently without the \n thing it doesn't print mjshell
       setup(inputBuffer,args,&background);       /* get next command */
       number_of_commands++;
      /* the steps are:
       (0) if built-in command, handle internally
       (1) if not, fork a child process using fork()
       (2) the child process will invoke execvp()
       (3) if background == 0, the parent will wait,
            otherwise returns to the setup() function. */
    }
}