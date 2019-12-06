#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LINE_LEN 1024
#define MAX_COMMAND_LINE_ARGS 128

char prompt[] = "shell > ";
char delimiters[] = " \t\r\n";
char **environ;

int main() {
    // Stores the string typed into the command line.
    char command_line[MAX_COMMAND_LINE_LEN];

    // Stores the tokenized command line input.
    char *arguments[MAX_COMMAND_LINE_ARGS];
  
  // Stores the child process ID returned from fork.	
   pid_t pid;
   
    
    while (true) {
        // Print the shell prompt.
        printf("%s", prompt);
        fflush(stdout);
        
        // Read input from stdin and store it in command_line. If there's an
        // error, exit immediately. (If you want to learn more about this line,
        // you can Google "man fgets")
        if ((fgets(command_line, MAX_COMMAND_LINE_LEN, stdin) == NULL) && ferror(stdin)) {
            fprintf(stderr, "fgets error");
            exit(0);
        }
        
        // If the user input was EOF (ctrl+d), exit the shell.
        if (feof(stdin)) {
            printf("\n");
            fflush(stdout);
            fflush(stderr);
            return 0;
        }

        // Tokenize the command line input (split it on whitespace)
        
        int i = 0;
        char *command;
        char *args;
          
        command = strtok(command_line,delimiters);
        args = strtok(NULL,delimiters);
        while (args != NULL){
          arguments[i] = args;
          i+=1;
          args = strtok(NULL,delimiters);
      }
      
        // Create a child process which will execute the command line input.
        if (pid < 0){
            perror("There is error in forking\n");  
          return -1;
        }
      
        else if (pid == 0){
          printf("It is a child process\n");
          if (execve(command, arguments, environ) < 0 ){
            perror("It gives execution error\n");   
            return -1; 
          }
          return -1;
        }
        
     
        // 3. The parent process should wait for the child to complete

        else {
          printf("It is a parent process\n");
          wait(NULL);
        }
    }
    
    // This should never be reached.
    return -1;
}
