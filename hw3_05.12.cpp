#include <iostream>
#include <time.h>
#include <sys/wait.h>
#include <algorithm>
#include <unistd.h>
#include <numeric>
#include <vector>

int main(){
    int N;
    
    std::cout<<"Instert size of array"<<std::endl;
    std::cin>>N;
    
    std::vector<int> vec(N);

    srand(time(NULL));
    for(int i = 0; i < N; ++i){
	    int num = rand()%1000;
	    vec[i] = num;
    }
    
    for(int i = 0; i < N; ++i){
	std::cout<< vec[i] << " " ; 
    }
    
    std::cout<<std::endl;

    int M;
    
    std::cout<<"Insert count of parallel workers"<<std::endl;
    std::cin>>M;

    M = std::min(M, N);

    int pipefd[2];
    int pipefd2[2];

    pipe(pipefd); 
    pipe(pipefd2); 
    
    pid_t pid = getpid();


     int result{};
     for(int i = 0; i*(N/M) < N; ++i){
        
        pipe(pipefd);
        pipe(pipefd2);

        pid = fork();

     
        if(pid > 0) {/* Parent*/
        
           
            std::pair<int,int> i_j{i*(N/M), (N/M)*(i+1)};
            
            close(pipefd[0]);
            
            write(pipefd[1],&i_j,sizeof(i_j));
            
            close(pipefd[1]);

            close(pipefd2[1]);

            int child_result;

            read(pipefd2[0],&child_result,sizeof(int));
            
            result += child_result;
         
            close(pipefd2[0]);

            wait(NULL);


        }

        if(pid == 0) {/*Child */
            
            std::pair<int,int> i_j{};
           
            close(pipefd[1]);

            read(pipefd[0],&i_j,sizeof(i_j));
           
            int result = std::accumulate(vec.begin() + i_j.first, vec.begin() + i_j.second, 0);

            close(pipefd2[0]);

            write(pipefd2[1],&result,sizeof(int));
            
            close(pipefd2[1]);

            exit(0);

        }


    }
    std::cout<<result<<std::endl;

}
