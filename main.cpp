#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>

#include "tokenizer.h"
//#include "parser.h"


using namespace std;

std::ostream& printList (std::ostream&, std::list<Token>);

int main(){
  std::vector<Token> tokenList = tokenize();
  std::vector<Token>::iterator location;
//  printList(std::cout, tokenList);
//  std::cout << literal("123a") << "\n\n";
//  std::cout << "0 returned "<< literal("0") <<"\n\n";
//  std::cout << "002 returned " << literal("002")<<"\n\n";
//  std::cout << "a returned " << letter('a') << "\n\n";
//  std::cout << "0adb returned " << identifier("0adb") << "\n\n";
//  std::cout << "abd0 returned " << identifier("abd0") << "\n\n"; 
//  std::cout <<"0a classified as identfier " <<identifier("0a") << "\n"; 
//  std::cout <<"0a classified as literal " <<literal("0a") << "\n"; 
//  location = tokenList.begin();
//  std::cout << exp(location, tokenList) << "\n";
  return 0;
}

//printList prints the tokenList to the output sent to it
std::ostream& printList (std::ostream& output, std::vector<Token> tokenList){
  // for (std::list<std::string>::iterator it = tokenList.begin(); it != tokenList.end(); ++it){
  //  output << it->word <<std::endl;
  //}
  //output << "\n";
  return output;
}
