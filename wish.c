/* -- When a command is entered in the shell, a child process is called, executes
the process, and then waits for more input

-- An interactive loop
-- Interactive mode and batch mode
-- In interactive mode a prompt is printed, and no prompt printed in batch mode

-- to parse inputs, strsep()
-- to execute commands, fork(), execv(), wait()/waitpid()

-- to implement cd, use chdir()

1. break up the user input into tokens
2. check which command to run and the path 

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    size_t buffer_size = 32;
    char* buffer = NULL;
    ssize_t chars_read;
    while (1) {
        // prompt user input
        printf("wish> ");
        // get user input
        chars_read = getline(&buffer,&buffer_size,stdin);
        char* found;

        // while ((found = strsep(&buffer, " ")) != NULL) {
        //     if (strcmp(found, "exit") == 0) {
        //         printf("Exiting shell...\n");
        //         exit(0);
        //     } else {
        //         printf("Found this word: %s\n", found);
        //     }
        // }

        // split the input string 
        char* token;
        token = strtok(buffer, " ");
        int i = 0;
        while (token != NULL) {
            argv[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        argv[i] = NULL;
        
        
        printf("Array index 0: %s", argv[0]);
        printf("Array index 1: %s", argv[1]);


        // printf("user input: %s", buffer);
        // // exit the shell when user inputs exit or ctrl+d
        // if (strcmp(buffer,"exit\n") == 0 || chars_read == -1) {
        //     printf("Exiting shell...\n");
        //     exit(0);
        // }
        // if (strcmp(buffer, "cd") == 0) {

        // }
    }

    return 0;
};
