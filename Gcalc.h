#ifndef _G_CALC_H_
#define _G_CALC_H_

#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "my_utils.h"
#include "MyGraph.h"

typedef std::map<std::string,Graph> SymbolTable;
enum Mode {menual,batch};
enum Command {ASSIGN_OP,
              PRINT_OP,
              DELETE_OP,
              WHO_OP,
              RESET_OP,
              QUIT_OP,
              SAVE_OP
              };
class Gcalc{
    SymbolTable variables; // the memory of the program, contains all the variables as strings and links them to a Graph
    Mode mode; // mode of Gcalc 
    bool quit_flag; // gets quit_flag when quit() is called.
    public:
    Gcalc(Mode mode);
    //starts Gcalc operations, getting input lines from user one by one in a loop
    void start();
    //starts proccessing the command, sending it to calc_parser for Tokenization etc..
    void parse_command(const std::string& command);
    //adds a graph to the calculator
    void addGraph(Graph g);
    //tries making a Graph out of Tokens expression, throws exceptions 
    Graph makeGraph(const Tokens& expression) const;
    //commands
    void who() const;
    //resets the calculator, deletes all the variables
    void reset();
    //raises the quit_flag to ending user input
    void quit();
    //Makes a new variable with the name of graph_name to be the value of the expression, if expression is illegal throws an informative error
    void assignment_op(const std::string& graph_name,const Tokens& expressions);
    //gets an expression of graph (can be a complex expression) and prints it if it is valid.
    void print_op(const Tokens& expression) const;
    void save_op(const Tokens& expression) const;
    void load_op(const std::string& expression);

    bool complexGraphExpression(const Tokens& expression, Graph& g) const;
    bool identifyFirstExpression(const Tokens& expression, Graph& g,Tokens::const_iterator& it) const;



};

#endif

