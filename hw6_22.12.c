#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 0;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
int isPrime(int n) {
  if (n <= 1)
    return 0;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

void *thread(void *arg) {
  int N = *((int *)arg);
  
  	while (counter < N) {
		
		pthread_mutex_lock(&counter_mutex);	
    	int increment = counter++;
  		pthread_mutex_unlock(&counter_mutex);
    			
			if (isPrime(counter)) 
      			printf("%d ", counter);
    		
			}	
  }
  return NULL;
}

int main() {
  pthread_mutex_init(&counter_mutex,NULL);
  int N;
  printf("Enter N: ");
  scanf("%d", &N);

  pthread_t thread1, thread2;
    
  if(pthread_create(&thread1, NULL, thread, &N) != 0 )
    return 1; 
  if(pthread_create(&thread2, NULL, thread, &N) != 0)
      return 2;

  if(pthread_join(thread1, NULL) != 0)
      return 3;
  if(pthread_join(thread2, NULL) != 0)
      return 4;
  pthread_mutex_destroy(&counter_mutex);

  return 0;
}
