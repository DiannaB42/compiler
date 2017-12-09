#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "tokenizer.h"
using namespace std;

int main(){
  std::list<std::string> tokenList = tokenize();
   for (std::list<std::string>::iterator it = tokenList.begin(); it != tokenList.end(); ++it){
    std::cout << std::endl << *it;
  }
  std::list <std::string>::iterator it =tokenList.begin();
return 0;
}
