
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
            std::string command_filtered = command.substr(0,command.size()-1);
            try{
                parse_command(command_filtered);
            }
            catch(ParserException& e){
                print(e.what());
            }
            catch(std::exception& e){
                std::cout<<"Error: "<<e.what()<<std::endl;
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
        if(tokens[0]=="quit"){
            quit();
            return;
        }
        if(tokens[0]=="who"){
            who();
            return;
        }
        if(tokens[0]=="reset"){
            reset();
            return;
        }
        else{
            throw UnrecognizedCommandException(command);
        }
    }
    //try save
    if(tokens[0]=="save"){
        if(tokens[1]=="(" && tokens[tokens.size()-1]==")"){
            Tokens print_expressions(tokens.begin()+2,tokens.end()-1);
            save_op(print_expressions);
            return;
        }
        else{
            throw UnrecognizedCommandException(command);
        }


    }
    //try delete
    if(tokens[0]=="delete"){
        if(tokens.size()==4 && tokens[1]=="(" && tokens[3]==")" ){
            if (variables.erase(tokens[2])){
                return;
            }
            else{
                //doesn't really check if its even a variable.. but its just not something to delete
                throw UndefinedVariableException(tokens[2]);
                return;
            }
        }
        else{
            throw UnrecognizedCommandException(command);
            return;
        }
    }

    //try print
    if(tokens[0]=="print"){
        if(tokens[1]=="(" && tokens[tokens.size()-1]==")"){
            Tokens print_expressions(tokens.begin()+2,tokens.end()-1);
            print_op(print_expressions);
            return;
        }
        else{
            throw UnrecognizedCommandException(command);
        }
    }
    //try assignment
    if(validGraphName(tokens[0]) && tokens[1]=="=" && tokens.size()>=3){
        Tokens assign_expressions(tokens.begin()+2,tokens.end());
        try{
            assignment_op(tokens[0],assign_expressions);            
            return;
        }
        catch(ParserException& e){
            print(e.what());
            return;
        }
        catch(std::exception& e){
            std::cout<<"Error: "<<e.what()<<std::endl;
            return;
        }
    }
    //try save 

    throw UnrecognizedCommandException(command);
}
Graph Gcalc::makeGraph(const Tokens& graph_expression) const{
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
            throw IllegalAssignmentException(TokensToString(graph_expression));
        }
    }
    //check regular initialization
    Graph g;
    if (validGraphInitialization(graph_expression,g)){
        return g;
    }
    //check load(G)
    if(validGraphLoad(graph_expression,g)){
        return g;
    }

    //complex expression
    if (complexGraphExpression(graph_expression,g)){
        return g;
    }
    else{
        throw IllegalGraphExpression(TokensToString(graph_expression));
    }
}

void Gcalc::assignment_op(const std::string& graph_name,const Tokens& graph_expression){
    Graph g;
    try{
        g = makeGraph(graph_expression);
    }
    catch(...){
        throw;
    }
    variables[graph_name]=g;
}
void Gcalc::who() const{
    for(auto it=variables.begin();it!=variables.end();it++){
        print(it->first);
    }
}
void Gcalc::quit(){
    exit(1);
}
void Gcalc::reset(){
    variables=SymbolTable();
}

//see if what's inside the parantheses is legal expression and print it if so
void Gcalc::print_op(const Tokens& expressions)const{
    Graph g;
    try{
        g=makeGraph(expressions);
    }
    catch(std::exception& e){
        print(e.what());
        return;
    }
    g.printGraph();
}
void Gcalc::save_op(const Tokens& expression) const{
    Graph g;
    std::string filename = expression[expression.size()-1];
    if (expression[expression.size()-2]!=","){
        throw IllegalSaveExpression(TokensToString(expression));
    }
    Tokens graph_expression=inRange(expression,0,expression.size()-2);
    try{
        g=makeGraph(graph_expression);
    }
    catch(...){
        throw;
    }
    std::ofstream file(filename,std::ios_base::binary);        
    if (file.is_open()){
        graphToBinaryFile(g,file);       
    }
    else{
        throw CantWriteToFileException(filename);
    }
}
