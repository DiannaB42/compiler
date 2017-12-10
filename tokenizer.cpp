#include <iostream>
#include <fstream>
#include "tokenizer.h"

Token::~Token(){

}
 
Token::Token(std::string wd){
  std::cout << "Checking that can make token with " << wd <<"\n\n";
  size_t index;
  word = wd;
  if(wd.length() == 0){
    type ="error";
    return;
  }
  if(wd.length() == 1){
    switch( wd[index]){
      case '+':
      case '-':
      case '*':
      case '=':
      case ';':
      case '(':
      case ')':
        type = "special";
        break;
      default:
        break;
    }
  } 
  if(digit(wd[index]) == true){
    if(wd.length() == 1){
      type = "literal";
    }
    else if ( literal(wd) == true){
      type = "literal";
    }/*
    else{
      type = "error";
    }
  }
  else if (letter(wd[index])== true){
    if(identifier(wd) == true){
      type = "identifier";
    }
    else {
      type = "error";
    }*/
  }
}

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

//tokenizer reads a file called file1.txt and adds all words to a list.
//A word is defined as being separated from other characters by either a
//space or a new line. Special charcters such as ; ( ) + - = * also seperate
//words
std::vector<Token> tokenize(){
  std::vector <Token> tokenList;
  std::fstream input;
  Token* token;
  input.open("file.txt");
  size_t length, index = 0, wordStart = 0;
  char letter;
  std::string word;
  std::string line;
  std::getline(input, line);
  length = line.length();
  while(input){
    while(length > index){
      letter = line[index];
      if( letter == ' '){
	word = line.substr(wordStart, (index - wordStart));
	if( word != "" ){
          std::cout << word << "\n";
	  token = new Token(word);
          tokenList.push_back(*token);
        }
	wordStart = index + 1;
      }
      else{
        while( letter ==';'|| letter == '=' ||letter == '+'||letter =='-'|| letter == '*' || letter == '(' || letter == ')'){
	word = line.substr(wordStart, (index - wordStart));
        if ( word != ""){
          std::cout << word << "\n";
          token = new Token(word);
          tokenList.push_back( *token);
        }
	if(length > index){
	  word = line.substr(index, 1);
          std::cout << word << "\n";
          token = new Token(word);
	  tokenList.push_back(*token);
	  index++;
	}
	if(length > index){
	  if(line[index] == ' '){
            wordStart = index + 1;
	  }
	  else {
	    wordStart = index;
	  }
	}
	else{
	  wordStart = index;
	}
	letter = line[index];
      }
      }
      index++;
    }
    word = line.substr(wordStart, (index - wordStart));
    if(word != ""){
      std::cout << word << "\n";
      token = new Token(word);
      tokenList.push_back(*token);
    }
    std::getline(input, line);
    length = line.length();
    index = wordStart = 0;
  }
  input.close();
  return tokenList;
}

