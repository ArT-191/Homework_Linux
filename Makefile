CC = g++
all: main
main: hello.o
      ${CC} -o main main.o
main.o: main.cpp
      ${CC} -c main.cpp
clean:
      rm main.o main


