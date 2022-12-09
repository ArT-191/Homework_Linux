#include <iostream>
#include <pthread.h> 
#include <semaphore.h>

class Integer{
private:
    int value;
    sem_t* semaph; 
public:
    Integer(int val):value(val){
        this->semaph = new sem_t();
        sem_init(this->semaph, 0, 1);
    }   
    
    int get_value(){
        return this->value;
    }
    void set_value(int val){
        this->value = val;
    }
    void inc(){
        sem_wait(this->semaph);
        this->value++;
        sem_post(this->semaph);
    }
    ~Integer() {
        sem_destroy(this->semaph);
        delete this->semaph;
    }
};

void* inc(void* arg){
    Integer* integ = (Integer*) arg;
    int inc_num = 10000;
    for (int i = 0; i < inc_num; i++){
       integ->inc(); 
    }
    return NULL;
}

int main () {
    int start = clock();
    int thread_num = 56;
    Integer* integ = new Integer(0);
    pthread_t* thrds = new pthread_t[thread_num];
    
    for (int i = 0; i < thread_num; i++){
        if (pthread_create(&thrds[i], NULL, inc, (void*)integ) != 0){
            return 1;
        }
    }
    
    for (int i = 0; i < thread_num; i++){
        if (pthread_join(thrds[i], NULL) != 0){
            return 2;
        }
    }
    std::cout << integ->get_value() << "\n";
    
    delete [] thrds;
    delete integ;
   
    FILE * fd;
    
    std::string pathname = "time.txt";
    int end = clock();
    std::string result = "Semaphore time is " + std::to_string(((float)end - start)/CLOCKS_PER_SEC) + " senconds";
    fd = fopen(pathname.c_str(),"a"); 

    fprintf(fd,"%s\n",result.c_str());
    fclose(fd);
    
    return 0;
}


