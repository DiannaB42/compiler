#include <iostream>
#include <fstream>
#include <string>
#include <list>



int main(){
  std::fstream input;
  input.open("file1.txt");
  size_t length, index = 0, wordStart = 0;
  char letter;
  std::string word;
  std::list<std::string> tokenList;
  std::string line;
  std::getline(input, line);
  length = line.length();
  while(input){
    while(length > index){
      letter = line[index];
      if( letter == ' '){
	word = line.substr(wordStart, (index - wordStart));
	tokenList.push_back(word);
	wordStart = index + 1;

      }
      index++;
    }
    std::getline(input, line);
    length = line.length();
    index = wordStart = 0;
  }
  input.close();
return 0;
}
