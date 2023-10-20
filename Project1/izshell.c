#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64
#define DELIM_TOKENS " \t\r\n\a"

int tokenCount = 0;

char *read_line(void) {
    // Initialize the current line and the buffer size
    // These will be updated by the `getline` function
    char *currentLine = NULL;
    ssize_t bufferSize = 0;

    // According to the manual for this function, getline will return the number of characters read,
    // but doesn't include the terminating byte at the end. If it returns -1, then there was an error.
    // If it returns 0, then it reached the end of the file.
    // If it returns a positive number, then it read that many characters.

    // We do this check to determine if we should exit the program or not, or if we should keep reading lines.

    if (getline(&currentLine, &bufferSize, stdin) == -1) {
        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }

    // At this point, we can be sure there are no errors, and we have not reached the end of the line, so therefore,
    // we should keep reading lines.

    return currentLine;
}

char **split_line(char *line) {
    // Create a variable for the buffer size and a variable to track the current position in the line.
    int bufferSize = TOKEN_BUFFER_SIZE;
    int currentPosition = 0;

    // Create memory space to store the tokens, of the size bufferSize * the size of a char pointer.
    char **tokens = malloc(bufferSize * sizeof(char*));
    char *currentToken;

    // If there is no memory or another error occured, we should notify the user and then we should exit the program
    if (!tokens) {
        fprintf(stderr, "izshell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Using this method, we split the line into tokens. This function below breaks a string into a series of tokesn using the specified delimiters.
    // In our case, we have defined the delimiter tokens above as a definition.

    currentToken = strtok(line, DELIM_TOKENS);

    // If there are actually tokens, then we should start processing the tokens to add to the buffer of tokens.

    tokenCount = 0;

    while (currentToken != NULL) {
        // The current token is added to the buffer of tokens, and then we increment the current position.
        tokens[currentPosition] = currentToken;
        currentPosition++;
        tokenCount += 1;

        // Check to see if the currentPosition variable exceeds the buffer size. If so, we ran out of room for the tokens, so we need to reallocate more memory.
        // In the example below 
        if (currentPosition >= bufferSize) {
            // Double the buffer size
            bufferSize += TOKEN_BUFFER_SIZE;
            // Reallocate the buffer of tokens to the new buffer size
            tokens = realloc(tokens, bufferSize * sizeof(char*));

            // If there was an error doing so, for example the computer ran out of memory, it should error out and exit the program.
            if (!tokens) {
                fprintf(stderr, "izshell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        // At this point in the program, we can assume that the there is room in the buffer to add a new token, so we can add the next token to the buffer.
        // Store the value of the next token in the currentToken variable.
        currentToken = strtok(NULL, DELIM_TOKENS);
    }

    // Null terminate the tokens array. Execvp requires the last element in the array to be NULL.
    tokens[currentPosition] = NULL;

    // We can now return the list of tokens to be executed.
    return tokens;
}

int launch_process(char **args) {
    // Declare ids for the processId and the process that will be waiting for the child process to finish.
    pid_t processId, waitProcessId;

    // Declare a variable to track the status of the process
    int processStatus;

    // Fork the process
    processId = fork();

    // If we are in the child process, then we should execute the command
    if (processId == 0) {
        // This is just like in the Minecraft API where you ask if args.length == 0, then the user must provide more commands. I have had experience implementing
        // this in the Minecraft API, so I am using that experience to help me here!

        // Execute the command like so.

        // Ex args = ['ls', '-l', '/']
        // execvp(args[0], args) -> execvp('ls', ['ls', '-l', '/'])

        if (execvp(args[0], args) == -1) {

            // If there is an error, it should print it to the user.

            perror("izshell");
        }



        exit(EXIT_FAILURE);
    } else if (processId < 0) {
        // there was an error forking the process

        perror("izshell");
    } else {

        // If we made it here, it means that the child process has been forked successfully, and now we have to wait for it to finish!

        // get size of args
        
        printf("token count: %d\n", tokenCount);
    
        char *lastArg = args[tokenCount - 1];

        int background = 0;


        if (strcmp(lastArg, "&") == 0) {
            // the last argument is an ampersand, so we should not wait for the child process to finish
            background = 1;
        }

        // parent process, time to wait for the child process to finish. we track the parent with the waitProcessId variable
        // do this until the child process is finished, this is tracked in the processId and processStatus variables

        if (background == 1) {
            printf("background process\n");
            return 1;
        } else {
            do {
                waitProcessId = waitpid(processId, &processStatus, WUNTRACED);
            } while ((background != 1) && !WIFEXITED(processStatus) && !WIFSIGNALED(processStatus));
        }

    }
}

int execute(char **args) {
    if (args[0] == NULL) {
        // There was no arguments provided to the command
        return 1;
    }

    // Custom Commands such as exit

    if (strcmp(args[0], "exit") == 0) {
        return 0;
    }

    return launch_process(args);
}

void shell_loop() {
    // Initialize the current line and the arguments
    char *currentLine;
    char **args;

    // Initialize a variable to track the status of the program
    int programStatus;

    do {
        // Print the shell prompt to the user with colors and pwd
        printf("\033[1;32mizshell\033[0m:\033[1;34m%s\033[0m$ ", getcwd(NULL, 1024));

        // Read the current line and split it into arguments
        currentLine = read_line();
        args = split_line(currentLine);

        // Once we have the args split up, we can pass them to our execute function
        programStatus = execute(args);

        // Clean up memory once the program is done
        free(currentLine);
        free(args);

    } while (programStatus); // Do this while the program status hasn't exited yet.
}

int iz_exit(char **args) { return 0; }

int main(int argc, char **argv) {

  shell_loop();

  return EXIT_SUCCESS;
}