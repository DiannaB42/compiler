#include <iostream>
#include <fstream>
#include "tokenizer.h"

//tokenizer reads a file called file1.txt and adds all words to a list.
//A word is defined as being separated from other characters by either a
//space or a new line. 
std::list<std::string> tokenize(){
  std::list <std::string> tokenList;  
  std::fstream input;
  input.open("file1.txt");
  size_t length, index = 0, wordStart = 0;
  char letter;
  std::string word;
  std::string line;
  std::getline(input, line);
  length = line.length();
  while(input){
    while(length > index){
      letter = line[index];
      if( letter == ' '){
	word = line.substr(wordStart, (index - wordStart));
	if( word != "")
	  tokenList.push_back(word);
	wordStart = index + 1;
      }
      index++;
    }
    word = line.substr(wordStart, (index -wordStart));
    if(word != ""){
      tokenList.push_back(word);
    }
    std::getline(input, line);
    length = line.length();
    index = wordStart = 0;
  }
  input.close();
  return tokenList;
}

