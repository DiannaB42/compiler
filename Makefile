main: main.o tokenizer.o parser.o
	g++ -std=c++11 -o main main.o tokenizer.o parser.o
main.o: main.cpp tokenizer.h parser.h
	g++ -c main.cpp -o main.o
tokenizer.o: tokenizer.h tokenizer.cpp
	g++ -c tokenizer.cpp -o tokenizer.o
parser.o: parser.h parser.cpp
	g++ -c parser.cpp -o parser.o
clean:
	rm -f *.o
