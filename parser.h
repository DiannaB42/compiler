#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <list>


bool isEnd 	(std::list<Token>::iterator,  std::list<Token>&);
bool factor	(std::list<Token>::iterator&, std::list<Token>&);
bool term  	(std::list<Token>::iterator&, std::list<Token>&);
bool exp   	(std::list<Token>::iterator&, std::list<Token>&);
bool assignment	(std::list<Token>::iterator&, std::list<Token>&);


#endif
