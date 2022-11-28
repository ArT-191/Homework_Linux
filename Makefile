output1: hw1_22.11.o
	g++ hw1_22.11.o -o output1
 
hw1_22.11.o: hw1_22.11.cpp
	g++ -c hw1_22.11.cpp

output2: hw2_22.11.o
	g++ hw2_22.11.o -o output2
 
hw2_22.11.o:  hw2_22.11.cpp
	g++ -c hw2_22.11.cpp

output3: hw3_05.12.o
	g++ hw3_05.12.o -o output3

hw3_05.12.o: hw3_05.12.cpp
	g++ -c hw3_05.12.cpp

clean:
	rm *.o output1 output2 output3
