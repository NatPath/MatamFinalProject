#ifndef _G_CALC_H_
#define _G_CALC_H_

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include "my_utils.h"
#include "Graph.h"
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
    public:
    Gcalc(Mode mode);
    void start();
    void parse_command(std::string command);
    void addGraph(Graph g);

};

#endif

