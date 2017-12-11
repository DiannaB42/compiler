#include <iostream>
#include <string>
#include <list>
#include <fstream>

#include "tokenizer.h"
#include "parser.h"


using namespace std;

std::ostream& printList (std::ostream&, std::list<std::string>);

int main(){
  std::list<std::string> tokenList = tokenize();
  //printList(std::cout, tokenList);
  std::list<std::string>::iterator it = tokenList.begin();
  Parser* parser = new Parser(tokenList);
  parser->program();
  return 0;
}

//printList prints the tokenList to the output sent to it
std::ostream& printList (std::ostream& output, std::list<std::string> tokenList){
   for (std::list<std::string>::iterator it = tokenList.begin(); it != tokenList.end(); ++it){
    output << *it <<std::endl;
  }
  output << "\n";
  return output;
}
