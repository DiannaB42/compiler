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
	if( word != "")
	  tokenList.push_back(word);
	wordStart = index + 1;
      }
      index++;
    }
    word = line.substr(wordStart, (index -wordStart));
    if(word != "")
      tokenList.push_back(word);
    std::getline(input, line);
    length = line.length();
    index = wordStart = 0;
  }
  input.close();
  for(std::list<std::string>::iterator it = tokenList.begin(); it != tokenList.end(); ++it){
    std::cout << " " << *it;
  }
  std::cout << '\n';

  return 0;
}
