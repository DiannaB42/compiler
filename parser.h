#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <list>


bool isEnd(std::list<std::string>::iterator, std::list<std::string>&);
bool digit(char);
bool nonZeroDigit(char);
bool literal(std::string);
bool letter(char);
bool identifier(std::string);
bool factor(std::list<std::string>::iterator&, std::list<std::string>&);
bool term(std::list<std::string>::iterator&, std::list<std::string>&);
bool exp(std::list<std::string>::iterator&, std::list<std::string>&);
bool program(std::list<std::string>::iterator&, std::list<std::string>&);


#endif
