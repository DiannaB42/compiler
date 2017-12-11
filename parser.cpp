#include "parser.h"

Parser::Parser(std::list<std::string> tokenList){
  list=tokenList;
}

Parser::~Parser(){

}


//checks that the character is a digit
bool Parser::digit(char num){
  switch(num){
   case '0':
   case '1':
   case '2':
   case '3':
   case '4':
   case '5':
   case '6':
   case '7':
   case '8':
   case '9':
     return true;
     break;
   default:
     return false;
  }
}

//nonZeroDigit checks that the character is a 1-9. Currently not used
//This logic handled by literal()
bool Parser::nonZeroDigit(char num){
  switch(num){
   case '1':
   case '2':
   case '3':
   case '4':
   case '5':
   case '6':
   case '7':
   case '8':
   case '9':
     return true;
     break;
   default:
   return false;
  }
}


//checks that the character is a number defined as either a 0 or
//starting with 1-9 and having a finite number of digits after it
//returns true if it is and false if not
bool Parser::literal (std::string number){
  size_t length, index;
  if (number == ""){
    std::cout << "Error: Call to literal with empty string\n";
    return false;
  }
  char num = number[0];
  switch (num){
    case '0':
      if(number.length() == 1)
       	return true;
      else{
	std::cout << "Error: " << number << " not a valid literal. Must not start with 0\n";
        return false; 
	}
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      length = number.length();
      index = 1;
      while(length > index){
	if( digit(number[index]) == false){
	  std::cout <<"Error: " << number[index] << " not a valid digit in literal " << number << "\n";
	  return false;
	}
        index++;
      }
      return true;
      break;
    default:
      return false;
  }
}

//checks that the character is a upper or lowercase letter
//in the alphabet or an _. Returns true if it is. False if not
bool Parser::letter(char let){
  switch(let){
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '_':
      return true;
      break;
    default:
      return false;
  }
}


//checks that the string starts with a letter and contains
//letters and numbers only. Returns false if it does not and
//true if it does
bool Parser::identifier(std::string id){
  size_t index = 0, length = id.length();
  if(length > 0){
    if(letter(id[0]) == false){
      std::cout << "Error: " << id[0] <<" not a letter that can begin identifier in "<< id <<"\n";
      return false;
    }
    else{
      index++;
      while( index < length){
        if(letter(id[index]) == false && digit(id[index]) ==false){
	  std::cout << "Error: Incorrect identifier " << id << ". Contains non letter and number character\n";
          return false;
        }
	index++;
      }
    }
    return true;
  }
  std::cout << "Error: Empty identifier not allower\n";
  return false;
}

//factor checks that the string is a correct factor expression
bool Parser::factor(std::list<std::string>::iterator& fact, node* loc){
  std::string temp, lex;
  if(fact == list.end()){
    std::cout << "Error: Sent empty list to factor\n";
    return false;
  }
  lex = *fact;
  std::cout << "checking factor " << *fact << "\n";
  switch (lex[0]){
    case ')':
      std::cout << "Returning with ) from factor\n";
      return true;
      break;
    case ';':
      std::cout << "Returning with ; from factor\n";
      return true;
      break;
    case '-':
    case '+':
      if(lex.length() != 1){
        std::cout << "Error: Unknown value encountered after " << lex << " in factor "<< *fact;
        return false;
      }
      ++fact;
      if(*fact == ")"){
        std::cout << "No value after +/- before hitting )\n";
        return false;
      }
      if(factor(fact, loc) == true){
        return true;
      }
      break;
    case '(':
      std::cout << "Removing (\n";
      ++fact;
      if( *fact == ")"){
	std::cout << "Error: No value inside ()\n";
        return false;
      }
      if(exp(fact, loc) == true){
        temp =*( fact);
        if( temp[0] == ')'){
	  if(temp.length() == 1){
            std::cout << "Removing )\n";
	    ++fact;
	    return true;
	  }
	  std::cout << "Error: Unknown value after ( in " << temp<< "\n";
        }
 	else{
	  std::cout << "Error: No matching ) found when expected. Got " << temp << " instead\n";
	}
      }
      return false;
      break;
    default:
      std::cout << "Entering default case with "<< *fact << " \n\n";
      temp = *fact;
      if(digit(temp[0])== true){
	if(literal(temp) == true){
	  if(++fact != list.end()){
	    std::cout << "Returning from factor fine \n\n";
	    return true;
	  }
	  return true;
	}
      }
      else if (letter(temp[0]) == true){
        if( identifier(temp) == true){
          if(symbols.find(temp) == symbols.end()){
            std::cout << "Error: Uninitialized variable " << temp << "\n";
            return false;
          } 
	    if(++fact != list.end()){
	      std::cout << "Returning from factor fine \n\n";
	      return true;
	    }
	    return true;
	  }
      }
      std::cout << "Error: Factor " << *fact << " not a literal or identifier\n"; 
      return false;
  }
  return false;
}


bool Parser::isEnd(std::list<std::string>::iterator it){
  it++;
  if(it == list.end())
    return true;
  else
    return false;
}

bool Parser::term(std::list<std::string>::iterator& trm, node* loc){
  std::string currentTerm;
  std::cout << "checking term " << *trm << "\n";
  if(factor(trm, loc) == false){
    return false;
  }
  std::cout << "Made it back fine \n\n";
  if(trm == list.end()){
    return true;
  }
  else{
    currentTerm = *trm;
    if( currentTerm == ""){
      std::cout << "Error: Empty string sent to term\n";
      return false;
    }
    switch(currentTerm[0]){
      case ')':
        std::cout << "Returning ) from term\n";
        return true;
        break;
      case '*':
        std::cout << "Removing * and attempting to test next\n";
        ++trm;
        if(*trm == ")"){
          std::cout << "Error: No value after * before hitting )\n";
	  return false;
        }
        return term(trm, loc);
        break;
      default:
        return true;
    }
  }
}


bool Parser::exp(std::list<std::string>::iterator& expr, node* loc){
  std::string currentExp;
  bool recur;
  if(term(expr, loc) == false){
    return false;
  }
  else{
    if(expr == list.end()){
      return true;
    }
    else{
      currentExp = *expr;
      switch(currentExp[0]){
        case ')':
          std::cout << "Returning ) from expression\n";
          return true;
          break;
        case ';':
          std::cout << "Returning ; from expression\n";
          return true;
          break;
        case '+':
        case '-':
          ++expr;
          if(*expr == ")"){
            std::cout << "Error: no value after +/- before hitting )\n";
            return false;
          }
          recur = exp(expr, loc);
	  return recur;
          break;
        default:
	  std::cout << "Error: Unknown expression " << currentExp<< "\n";
          return false;
      }
    }
  }
}

bool Parser::assignment(std::list<std::string>::iterator& it){
  //btree expression;
  node* loc = NULL;
  if(*it == "%"){
    std::cout << "Error: Sent an empty assignment statement\n";
    return false;
  }
  std::string current = *it;
  std::string id;
  int value = 0;
  if( identifier(current) != true){
    return false;
  }
  id = *it;
  it++;
  if(*it == "%"){
    std::cout << "Error: no assignment after identifier " << current << "\n";
    return false;
  }
  if(*it == ";"){
    std::cout << "Error: no assignment before ;\n";
    return false;
  }
  current = *it;
  if(current[0] != '='){
    std::cout << "Error: No = after identifier\n";
    return false;
  }
  if(current.length() != 1){
    std::cout << "Error: extra character after = in " << current <<"\n";
    return false;
  }
  it++;
  if(*it == "%"){
    std::cout << "Error: no expression after = \n";
    return false;
  }
  if(exp(it, loc) == false){
    std::cout << "Error: Invalid expression in assignment statement\n";
    return false;
  }
  std::cout << "made it back to assignment\n";
  if(it == list.end()){
    std::cout << "Error: Reached end of file before getting ; \n";
    return false;
  }
  current = *it;
  if( current[0]!= ';'){
    std::cout << "Error: Expected ; but received " << current << "\n";
    return false;
  }
  if(current.length() != 1){
    std::cout << "Error: Unknown character after ; in " << current << "\n";
    return false;
  }
  if(insertSymbol(id, value) == false){
    std::cout << "Unable to insert symbol " << id <<", " << value << " into symbol table\n";
    return false;
  }
  return true;
}

bool Parser::program(){
  std::list<std::string>::iterator it = list.begin();
  std::unordered_map<std::string, int> symbols;
  //std::list<std::string>::iterator end = list.end();
  while(*it != "%" ){
    if(assignment(it) == false){
      std::cout << "Invalid assignment\n";
      return false;
    }
    std::cout << "iterator points to " << *it << "\n";
    it++;
  }
  printSymbols();
  return true;
}

bool Parser::insertSymbol(std::string id, int value){
  bool insert;
  if(symbols.find(id) == symbols.end()){
    symbols.erase(id);
    insert = symbols.insert({id, value}).second;
  }
  else{
    insert = symbols.insert({id, value}).second;
  }
  return insert;
}

void Parser::printSymbols(){
  for (auto it= symbols.begin(); it != symbols.end(); ++it){
    std::cout << it->first << " = " << it->second << "\n";
  }
}
