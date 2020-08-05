
#include "Gcalc.h"
#include "calc_parser.h"

Gcalc::Gcalc(Mode mode):mode(mode){}
void Gcalc::start(){
    std::string command;
    if (mode==menual){
        while(true){
            std::cout<<"Gcalc> ";
            std::getline(std::cin,command);
            try{
                parse_command(command);
            }
            catch(std::exception& e){
                print(e.what());
            }
        }
    }
    else{
        while(std::getline(std::cin,command)){
            try{
                parse_command(command);
            }
            catch(std::exception& e){
                print(e.what());
            }
        }
    }
}
void Gcalc::parse_command(const std::string& command){
    Tokens tokens=stringToTokens(command); 
    //empty command
    if(tokens.size()==0){
        return;
    }
    //single word commands
    if(tokens.size()==1){
        if(!(tokens[0]=="quit")){
            quit();
            return;
        }
        if(!tokens[0].compare("who")){
            who();
            return;
        }
        if(!tokens[0].compare("reset")){
            reset();
            return;
        }
        else{
            throw UnrecognizedCommandException(command);
        }
    }
    //for now..
    else{
        if(validGraphName(tokens[0]) && tokens[1].compare("=")){
            Tokens expressions(tokens.begin()+2,tokens.end());
            try{
                assignment_op(tokens[0],expressions);            
            }
            catch(std::exception& e){
                print(e.what());
            }
        }
        throw UnrecognizedCommandException(command);
    }
}
Graph Gcalc::makeGraph(const Tokens& graph_expression){
    //regular assignment
    if (graph_expression.size()==1 ){
        if(validVertexName(graph_expression[0])){
            auto res = variables.find(graph_expression[0]);
            if (res==variables.end()){
                throw UndefinedVariableException(graph_expression[0]);
            }
            return res->second;
        }
        else{
            throw IllegalAssignmentException(graph_expression[0]);
        }
    }
    //check regular initialization
    Graph g;
    if (validGraphInitialization(graph_expression,g)){
        return g;
    }
}

void Gcalc::assignment_op(const std::string& graph_name,const Tokens& graph_expression){
    try{
        Graph g=makeGraph(graph_expression);
        variables[graph_name]=g;
    }
    catch(std::exception& e){
        print(e.what());
    }
}
void Gcalc::who(){
    return;
}
void Gcalc::quit(){
    exit(1);
}
void Gcalc::reset(){
    variables=SymbolTable();
}
