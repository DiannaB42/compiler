main: main.o tokenizer.o
	g++ -std=c++11 -o main main.o tokenizer.o
main.o: main.cpp tokenizer.h
	g++ -c main.cpp -o main.o
tokenizer.o: tokenizer.h tokenizer.cpp
	g++  -c tokenizer.cpp -o tokenizer.o
