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
    SymbolTable variables;
    Mode mode; 
    bool quit_flag;
    public:
    Gcalc(Mode mode);
    void start();
    void parse_command(const std::string& command);
    void addGraph(Graph g);
    Graph makeGraph(const Tokens& expression) const;
    //commands
    void who() const;
    void reset();
    void quit();
    void save();
    //void delete_op(const std::string& graph_name);
    void assignment_op(const std::string& graph_name,const Tokens& expressions);
    void print_op(const Tokens& expression) const;
    void save_op(const Tokens& expression) const;
    void load_op(const std::string& expression);

    bool complexGraphExpression(const Tokens& expression, Graph& g) const;
    bool identifyFirstExpression(const Tokens& expression, Graph& g) const;



};

#endif

