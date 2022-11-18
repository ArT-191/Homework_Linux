#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main(){

   int pipefds1[2], pipefds2[2];
   int returnstatus1, returnstatus2;
   char readmessage[20];
   returnstatus1 = pipe(pipefds1);
    
   if (returnstatus1 == -1) {
      printf("Unable to create pipe 1 \n");
      return 1;
   }
   returnstatus2 = pipe(pipefds2);
   
   if (returnstatus2 == -1) {
      printf("Unable to create pipe 2 \n");
      return 1;
   }
pid_t child_a, child_b;

child_a = fork();

if (child_a == 0) {  /* Child A */
      close(pipefds1[0]);
      close(pipefds2[1]); 
      pid_t pid_A = getpid();
      write(pipefds1[1], &pid_A, sizeof(pid_t));

      pid_t pid_B;
      read(pipefds2[0], &pid_B, sizeof(pid_t));
      std::cout<<pid_A<<std::endl;


} else {
    child_b = fork();

    if (child_b == 0) { /* Child B */
      close(pipefds1[1]);
      close(pipefds2[0]);
      pid_t pid_B = getpid();
      write(pipefds2[1], &pid_B, sizeof(pid_t));

      pid_t pid_A;
      read(pipefds1[0], &pid_A, sizeof(pid_t)); 
        std::cout<<pid_B<<std::endl;


    } else { /* Parent*/
	 wait(NULL);
	 wait(NULL);

    }
}

}
