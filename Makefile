main: main.o tokenizer.o parser.o 
	g++ -std=c++11 -o main main.o tokenizer.o parser.o
main.o: main.cpp tokenizer.h parser.h
	g++ -std=c++11 -c main.cpp -o main.o
tokenizer.o: tokenizer.h tokenizer.cpp
	g++ -std=c++11 -c tokenizer.cpp -o tokenizer.o
parser.o: parser.h parser.cpp 
	g++ -std=c++11 -c parser.cpp  -o parser.o 
clean:
	rm -f *.o
