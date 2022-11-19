#include <iostream> 
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t pid = fork();

  
  if (pid == 0) { /* Child */

      kill(getppid(), SIGKILL);

 } else { /* Parent */

      wait(NULL);

  }
}
