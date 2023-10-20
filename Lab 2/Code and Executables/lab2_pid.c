#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  pid_t pid; 
       
  pid = fork();

  printf("pid result, %d", pid);

  if (pid < 0) 
    fprintf(stderr, "fail \n");
  else if (pid >0) {
    printf("Parent pid: %d\n",pid);
    printf("Parent getpid: %d\n",getpid());
  }
  else {
    printf("Child pid: %d\n",pid);
    printf("Child getpid: %d\n",getpid());
  }

  sleep(100);

  return 0;
}
