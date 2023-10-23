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

to-do:
- if there is an argument when there the file is run then run in batch mode 
  else run in interactive mode
- figure out what command is being called
- if it's a built-in function then execute it without a child process
- create a child process
- execute the command that is entered
- wait for the command to finish

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    size_t buffer_size = 32;
    char* buffer = NULL;
    ssize_t chars_read;
    char error_message[30] = "An error has occurred\n";
    while (1) {
        // prompt user input
        printf("wish> ");
        // get user input
        chars_read = getline(&buffer,&buffer_size,stdin);

        //split the input string 
        char* token;
        token = strtok(buffer, " ");
        int i = 0;
        char* input[30];
        int count = 0;
        // char* input = (char *) malloc(sizeof(char) * 10);
        printf("Splitting the input into tokens\n");
        while (token != NULL) {
            input[i] = token;
            token = strtok(NULL, " ");
            i++;
            count++;
        }
        printf("Total commands inputted: %d\n", count);
        input[i] = NULL;

        // int input_size = sizeof(input) / sizeof(input[0]);
        // check if user inputted ctrl+d or EOF
        if (chars_read == -1) {
            printf("Exiting the shell...");
            exit(0);
        }

        // check if the user inputted exit
        // error-check: check if an argument was passed when using exit
        if (strcmp(input[0], "exit\n") == 0) {
            printf("Exiting the shell...");
            exit(0);
        }

        // loop through the user input
        printf("Looping through user input\n");
        int j = 0;
        while (input[j] != NULL) {
            printf("Array index %d: %s\n", j, input[j]);    
            j++;
        }
        
        // check if the user inputted cd
        char* cd_command = "cd";
        if (strcmp(input[0], cd_command) == 0 && count != 2) {
            write(STDERR_FILENO, error_message, strlen(error_message)); 
            printf("First error\n");
        } else if (strcmp(input[0], cd_command) == 0 && count == 2) {
            if (chdir(input[1]) == -1) {
                write(STDERR_FILENO, error_message, strlen(error_message));
                printf("Second error\n");
            } else {
                printf("Directory changed\n");
            }
        }

        // check if the user inputted path
    

        // execute a command
        execv("/bin/ls", input);
        perror("execv");




        // char* command = input[0];
        // char* full_path = strcat("/bin/", command);
        // printf("path: %s\n", full_path);
        // if (strcmp(command, "cd") != 0 && strcmp(command,"path") != 0) {
        //     printf("command: %s\n",  command);
        //     if (execv("/bin/ls", input) == -1) {
        //         write(STDERR_FILENO, error_message, strlen(error_message)); 
        //         printf("Third error\n");
        //         printf("Error Number: %d\n", errno);
        //     }
        // } else {
        //     printf("command was not run\n");
        // }
        
       


        
    }

    return 0;
};
