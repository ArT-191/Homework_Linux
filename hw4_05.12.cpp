#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <fcntl.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


enum Operators {s,m,ss} ;//Creating operators

struct thread_data { //Keeping data of threads
    Operators op;
    int number2;
    int number1;        
};


void *routine(void *input) {
   

  thread_data *my_data=(thread_data *)input;

  my_data = (struct thread_data *) input;
  int num1 = my_data->number1;
  int num2 = my_data->number2;
  Operators oper = my_data->op;
 
  int result;
  switch(oper){
    case s:
    {
      result = num1 + num2;
      
    } break;
      
    case m:
    {
      result = num1 * num2;
      
    } break;
    case ss:
    {
      result = (num1) * (num1) + (num2) * (num2);
      
    } break;
    
   
  }  
  static unsigned int index = 0;

  pthread_t id = pthread_self();//Threads ID
   
   ++index;
  
  std::string pathname = "out_" + std::to_string (index) + ".txt"; 
 
  std::string _result = "=" +  std::to_string (result); // Connecting strings because, "fprintf" takes not more than 8 arguments
  FILE * fd;
  static const char * const operators_to_string[] = { 
  /*It was necessary to,write "enum" in file,
	but that's not possible ,                                                       
  that's why i convert my enum named "Operators" to string*/
    [s] = "s",
	  [m] = "m",                                            
	  [ss] = "s",

  };
 
  fd = fopen(pathname.c_str(),"w+"); // Creates an empty file for both reading and writing

  fprintf(fd,"%d %s %d %s",num1, operators_to_string[oper], num2, _result.c_str());//Writing variables in file
  
  
  
  exit(0);
  return NULL;
}

   std::istream& operator>>(std::istream& is, Operators& operators){ //overloading operator ">>"
    std::string _operators;
    is >> _operators;

    if (_operators == "s")
        operators = s;
    else if (_operators == "m")
        operators = m;
    else if (_operators == "ss")
        operators = ss;

    return is;
}

int main() {
  int N;
  int num1,num2;
  Operators oper;
  std::cin>>N;

  std::vector<pthread_t> th(N); // keeping threads in vector
  
  std::vector<thread_data> arguments;
  for (int i = 0; i < N; ++i){

    std::cin>>num1>>num2>>oper; // for example 12 12 ss
    
    thread_data data;
    data.number1 = num1;
    data.number2 = num2;
    data.op = oper; 
    arguments.push_back(data);
    
  }
      
    for (int i = 0; i < N; i++) {
        if (pthread_create(&th[i], NULL, &routine, (void*)&arguments[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
       
    }
    for (int i  = 0; i < N; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
      
    }
   
   
}