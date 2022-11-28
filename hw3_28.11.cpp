#include <iostream>
#include <time.h>
#include <sys/wait.h>
#include <algorithm>
#include <unistd.h>
#include <numeric>
#include <stdlib.h>


int main(){
int N;
std::cout<<"Instert size of array"<<std::endl;
std::cin>>N;
int arr[N];
srand(time(NULL));
for(int i = 0; i < N; ++i){
	int num = rand();
	arr[i] = num;
}
for(int i = 0; i < N; ++i){
	std::cout<< arr[i] << " " <<std::endl ; 
}

int M;
std::cout<<"Insert count of parallel workers"<<std::endl;
std::cin>>M;

	int pipefd_i[2] ,pipefd_j[2];
	
	pid_t pid = fork();

		if(pid < 0){ 
			return 1;
		}

		if(pid > 0){ //Parent
		
			int i{};
			int j = (N/M) + i;
			close(pipefd_i[1]);
			close(pipefd_j[1]);

			write(pipefd_i[1], &i ,sizeof(int));
			write(pipefd_j[1], &j, sizeof(int));
			
		}

		else{//Child

			int i{};
			int j = (N/M) + i;

			close(pipefd_i[0]);
			close(pipefd_j[0]);

			read(pipefd_i[0], &i, sizeof(int));
			read(pipefd_j[0], &j, sizeof(int));
			
			for(i = 0 ; i < j; ++i){
				int init = 0;
				int j = (N/M) + i;
				unsigned int result = std::accumulate(arr + i,arr + j, init);
				
				i == j;
				
				std::cout<<result<<std::endl;

			}
			


		}

		
       
		return 0;
}



//std::min((N/M)+i,N);
