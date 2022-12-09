#include <iostream>
#include <pthread.h> 

class Integer{
private:
    int value;
    pthread_mutex_t* mutex;
public:
    Integer(int val):value(val){
        this->mutex = new pthread_mutex_t();
        pthread_mutex_init(this->mutex,NULL);
    }   
    
    int get_value(){
        return this->value;
    }
    void set_value(int val){
        this->value = val;
    }
    void inc(){
       pthread_mutex_lock(this->mutex);
        this->value++;
        pthread_mutex_unlock(this->mutex);
    }
    ~Integer() {
         pthread_mutex_destroy(this->mutex);
        delete this->mutex;
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
    std::string result = "Mutex time is " + std::to_string(((float)end - start)/CLOCKS_PER_SEC) + " seconds";
    fd = fopen(pathname.c_str(),"a"); 

    fprintf(fd,"%s\n",result.c_str());
    
    fclose(fd);
    
    return 0;
}


