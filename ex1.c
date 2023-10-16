/* A Unix C Program */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
  #include <sys/wait.h>

int value = 10;

int main() {

    pid_t pid;
    pid = fork();

    if (pid > 0) { /* parent process */
        wait(NULL);
        printf("PARENT: value = %d\n", value);
    } else if (pid == 0) { /* child process */
        value += 10;
        printf("Child: value = %d\n", value);
    }
    
    pid = fork();

    if (pid > 0) { /* parent process */
        wait(NULL);
        printf("PARENT: value = %d\n", value);
    } else if (pid == 0) { /* child process */
        value += 10;
        printf("Child: value = %d\n", value);
    }
}