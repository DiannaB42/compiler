#include "parser.h"
#include "tokenizer.h"


//factor checks that the string is a correct factor expression
bool factor(std::list<Token>::iterator& fact, std::list<Token>& list){
  std::string temp, lex;
  if(fact == list.end()){
    std::cout << "Error: Sent empty list to factor\n";
    return false;
  }
  lex = *fact;
  std::cout << "checking factor " << *fact << "\n";
  switch (lex[0]){
    case '-':
    case '+':
      if(lex.length() != 1){
        std::cout << "Error: Unknown value encountered after " << lex << " in factor "<< *fact;
        return false;
      }
      if(factor(++fact, list) == true){
        return true;
      }
      break;
    case '(':
      std::cout << "Removing (\n";
      if(exp(++fact,list) == true){
        temp =*(fact);
        if( temp[0] == ')'){
	  if(temp.length() == 1){
	    ++fact;
	    std::cout << "Removing )\n";
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
      if( temp[0] ==')'){
	std::cout << "Returning from )\n";
	return true;
      }
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


bool isEnd(std::list<Token>::iterator it, std::list<Token>& list){
  it++;
  if(it == list.end())
    return true;
  else
    return false;
}

bool term(std::list<std::string>::iterator& trm, std::list<std::string>& list){
  std::string currentTerm;`
  std::cout << "checking term " << *trm << "\n";
  if(factor(trm, list) == false){
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
      case '*':
        std::cout << "Removing * and attempting to test next\n";
        return term(++trm, list);
        break;
      default:
        if(factor(trm,list) == true){
          return true;
         }
        std::cout << "Error: Unknown term " << currentTerm << " encountered\n";
        return false;
    }
  }
}


bool exp(std::list<Token>::iterator& expr, std::list<Token>& list){
  std::string currentExp;
  bool recur;
  if(term(expr, list) == false){
    return false;
  }
  else{
    if(expr == list.end()){
      return true;
    }
    else{
      currentExp = *expr;
      switch(currentExp[0]){
        case '+':
        case '-':
          recur = exp(++expr,list);
	  return recur;
          break;
        default:
	  std::cout << "Error: Unknown expression " << currentExp<< "\n";
          return false;
      }
    }
  }
}

bool assignment(std::list<Token>::iterator& it, std::list<Token>& list){
  if( it == list.end()){
    std::cout << "Error: Sent an empty assignment statement\n";
    return false;
  }
  std::string current = *it;
  if( identifier(current) == true){
    it++;
    if(it == list.end()){
      std::cout << "Error: no assignment after identifier " << current << "\n";
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
    if(it == list.end()){
      std::cout << "Error: no expression after = \n";
      return false;
    }
    if(exp(it, list) == false){
      std::cout << "Error: Invalid expression in assignment statement\n";
      return false;
    }
    it++;
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
  }
}
