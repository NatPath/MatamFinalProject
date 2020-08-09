#ifndef _G_CALC_H_
#define _G_CALC_H_

#include <iostream>
#include <map>
#include <string>
#include <utility>

#include "my_utils.h"
#include "MyGraph.h"

//represents the memory of Gcalc
typedef std::map<std::string,Graph> SymbolTable;
//enum for mode of action
enum Mode {menual,batch};
class Gcalc{
    SymbolTable variables; // the memory of the program, contains all the variables as strings and links them to a Graph
    Mode mode; // mode of Gcalc 
    bool quit_flag; // gets quit_flag when quit() is called.
    public:
    Gcalc(Mode mode);
    //starts Gcalc operations, getting input lines from user one by one in a loop
    void start();
    private:
    //starts proccessing the command, sending it to calc_parser for Tokenization etc..
    void parse_command(const std::string& command);
    //adds a graph to the calculator
    void addGraph(Graph g);
    //Gets an expression , if it is a valid graph expression returns a fitting graph, throws exceptions if it isn't
    Graph makeGraph(const Tokens& expression) const;
    //Prints all the graph variables stored
    void who() const;
    //resets the calculator, deletes all the variables
    void reset();
    //raises the quit_flag to ending user input
    void quit();
    //Makes a new variable with the name of graph_name to be the value of the expression, if expression is illegal throws an informative error
    void assignment_op(const std::string& graph_name,const Tokens& expressions);
    //gets an expression of graph (can be a complex expression) and prints it if it is valid.
    void print_op(const Tokens& expression) const;
    //gets an expression , checks if it is a valid save expression( consisting Graph expression and a filename)
    void save_op(const Tokens& expression) const;
    //gets an expression, checks if it is a valid load expression, if the file given in the expression is valid grap, stores it in memory
    void load_op(const std::string& expression);
    /**
     * returns if the expression given is a valid complex graph expression
     * A complex expression is an expression which consists more than one graph or inside parantheses 
     * updates g  argument to the expression if it is valid and returns ture;
     * otherwise returns false
     * */
    bool complexGraphExpression(const Tokens& expression, Graph& g) const;
    
    /**
     * Identifies the first substring which makes a legitimate graph, if it exists.
     * assign g to be the graph of the first expression
     * assign it to be an iterator to the token after the first expression ends ( if all the expression is first , returns to expression.end())
     * */
    bool identifyFirstExpression(const Tokens& expression, Graph& g,Tokens::const_iterator& it) const;

};

#endif

