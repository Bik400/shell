#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        // batch mode
        printf("Batch mode\n");
    } else {
    size_t buffer_size = 0;
    char* buffer = NULL;
    char* buffer_copy = NULL;
    ssize_t chars_read;
    char error_message[30] = "An error has occurred\n";
    int count = 0;
    char** input;
    while (1) {
        // prompt user input
        printf("wish> ");
        // get user input
        chars_read = getline(&buffer,&buffer_size,stdin);
        buffer_copy = malloc(sizeof(char) * chars_read);

         // check if user inputted ctrl+d or EOF
        if (chars_read == -1) {
            printf("Exiting the shell...");
            exit(0);
        }

         if (buffer_copy == NULL) {
            printf("Error allocating memory\n");
            exit(1);
        } else {
            strcpy(buffer_copy, buffer);
        }


        char* token = strtok(buffer, " \n");
        int num_of_tokens = 0;
        int i = 0;
        printf("Splitting the input into tokens\n");
        while (token != NULL) {
            num_of_tokens++;
            token = strtok(NULL, " \n");
            count++;
        }
        num_of_tokens++;
        input = malloc(sizeof(char*) * num_of_tokens);
        token = strtok(buffer_copy, " \n");

        for (i = 0; token != NULL; i++) {
            input[i] = malloc(sizeof(char) * strlen(token));
            strcpy(input[i], token);
            token = strtok(NULL, " \n");
        }
        input[i] = NULL;
        
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
            if (chdir(input[1]) == 0) {
                printf("Directory changed\n");
            } else {
                write(STDERR_FILENO, error_message, strlen(error_message));
            }
        }

        // check if the user inputted path
    

        // execute a command
        // execv("/bin/ls", input);
        // perror("execv");

        char* command = input[0];
        char* full_path = strcat("/bin/", command);
        printf("path: %s\n", full_path);
        if (strcmp(command, "cd") != 0 && strcmp(command,"path") != 0) {
            printf("command: %s\n",  command);
            if (execv(full_path, input) == -1) {
                write(STDERR_FILENO, error_message, strlen(error_message)); 
                printf("Third error\n");
                printf("Error Number: %d\n", errno);
            }
        } else {
            printf("command was not run\n");
        }
        
       


        
    }
    }

    return 0;
};
