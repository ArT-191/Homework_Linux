output: hw1_22.11.o
	g++ hw1_22.11.o -o output
 
main.o: hw1_22.11.cpp
	g++ -c hw1_22.11.cpp

clean:
	rm *.o output

 

