#include <stdio.h>
#include <unistd.h>

int main()
{
  
  pid_t pid1, pid2, pid3;

    pid1 = fork();

    printf("process1: %d\n", pid1);

    pid2 = fork();

    printf("process2: %d\n", pid2);

    pid3 = fork();

    printf("process3: %d\n", pid3);

    printf("%s\n", "Hello world");

    sleep(100);

    return 0;
}

