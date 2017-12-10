#include "parser.h"

//checks that the character is a digit
bool digit(char num){
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
bool nonZeroDigit(char num){
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
bool literal (std::string number){
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
bool letter(char let){
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
bool identifier(std::string id){
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
bool factor(std::list<std::string>::iterator& fact, std::list<std::string>& list){
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
      if(exp(++fact,list) == true){
        temp =*( ++fact);
        if( temp[0] == ')'){
	  if(temp.length() == 1){
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


bool isEnd(std::list<std::string>::iterator it, std::list<std::string>& list){
  it++;
  if(it == list.end())
    return true;
  else
    return false;
}

bool term(std::list<std::string>::iterator trm, std::list<std::string>& list){
  std::string currentTerm;
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


bool exp(std::list<std::string>::iterator expr, std::list<std::string>& list){
  std::string currentExp;
  bool recur;
  if(term(expr, list) == false){
    return false;
  }
  else{
    if(++expr == list.end()){
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
