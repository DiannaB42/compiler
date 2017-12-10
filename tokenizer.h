#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include <string>
#include <list>
class Token{
private:
  std::string word;
  std::string type;
public:
  Token(std::string);
  ~Token();
  std::string getType(){return type;}
  std::string getWord(){return word;}
};
std::vector <Token> tokenize();

bool digit(char);
bool nonZeroDigit(char);
bool literal(std::string);
bool letter(char);
bool identifier(std::string);

#endif
