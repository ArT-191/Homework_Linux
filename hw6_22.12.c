#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int counter = 0;

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
  while (counter <= N) {
    if (isPrime(counter)) {
      printf("%d ", counter);
    }
    counter++;
  }
  return NULL;
}

int main() {

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

  return 0;
}
