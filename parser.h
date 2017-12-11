#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

struct node
{
  int key_value;
  node *left;
  node *right;
};

class Tree
{
    public:
        Tree();
        ~Tree();
        int calculate();
        void insert(int key, node* parent, int side);
        void destroy_tree();
        node *root;
    private:
        int calculate(node*);
        void destroy_tree(node *leaf);
};


class Parser{
public:
Parser(std::list<std::string>);
~Parser();
bool isEnd(std::list<std::string>::iterator);
bool digit(char);
bool nonZeroDigit(char);
bool literal(std::string);
bool letter(char);
bool identifier(std::string);
bool factor(std::list<std::string>::iterator&, node*);
bool term(std::list<std::string>::iterator&, node*);
bool exp(std::list<std::string>::iterator&, node*);
bool assignment(std::list<std::string>::iterator&);
bool program();
bool insertSymbol(std::string, int);
void printSymbols();
private:
std::list<std::string> list;
std::unordered_map<std::string, int> symbols;
Tree* evaluation;
};

#endif
