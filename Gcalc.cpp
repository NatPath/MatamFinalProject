
#include "Gcalc.h"
#include "calc_parser.h"

bool getlineWrap(std::string& command){
    std::cout<<"Gcalc> ";
    if(std::getline(std::cin,command)){
        return true;
    }
    else{
        return false;
    }
}
Gcalc::Gcalc(Mode mode):mode(mode),quit_flag(false){}
void Gcalc::start(){
    std::string command;
    if (mode==menual){
        while(getlineWrap(command)){
            try{
                parse_command(command);
                if (quit_flag){
                    break;
                }
            }
            catch(std::exception& e){
                print(e.what());
            }
        }
    }
    else{
        while(std::getline(std::cin,command)){
            //std::string command_filtered = command.substr(0,command.size()-1);
            try{
                parse_command(command);
                if (quit_flag){
                    break;
                }
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
    quit_flag=true;
    //exit(1);
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

bool Gcalc::identifyFirstExpression(const Tokens& expression,Graph& g,Tokens::const_iterator& it) const{
    Tokens subexpression_temp;
    Tokens first_expression;
    std::string operator_token;
    if (expression.size()==0){
        return false;
    }

    //some kind of parantheses is opener
    bool balanced;
    if (expression[0]=="("){
        subexpression_temp=findClosingParantheses(expression,SMOOTH,it,&balanced);        
        if (!balanced){
            return false;
        }
        first_expression=inRange(subexpression_temp,1,subexpression_temp.size()-1);
        g=makeGraph(first_expression);
        return true;
    }

    if (expression[0]=="{"){
        first_expression=findClosingParantheses(expression,CURLY,it,&balanced);        
        if (!balanced){
            return false;
        }
        if (!validGraphInitialization(first_expression,g)){
            throw IllegalAssignmentException(TokensToString(first_expression));
        }          
        else{
            
            return true;
        }
    }
    //negation is an opener
    first_expression=findNextBinaryOperator(expression,it);
    //int count_steps=0;//to determine how to increment the iterator
    if (expression[0]=="!"){
        Tokens after_neg_trim=negTrim(first_expression);
                
        if (after_neg_trim[0]=="!"){
            first_expression=inRange(after_neg_trim,1,after_neg_trim.size());
            g=!(makeGraph(first_expression));
        }
        else{
            g=makeGraph(after_neg_trim);
        }

        return true;
    }
    if(expression[0]=="load"){
        if (validGraphLoad(first_expression,g)){
            return true;
        }
        else{
            return false;
        }
    }

    //first expression is supposed to be regular
    subexpression_temp=inRange(expression,0,1);
    it=expression.begin()+1;
    g=makeGraph(subexpression_temp);        
    return true;
}

bool Gcalc::complexGraphExpression(const Tokens& expression, Graph& g) const{
    //expression starts with parantheses
    Tokens subexpression_temp;
    Tokens subexpression_first;
    Tokens subexpression_second;
    std::string operator_token;
    Graph g1;
    Graph g2;
    Tokens future_expressions;

    Tokens::const_iterator it= expression.begin();
    if (!identifyFirstExpression(expression,g1,it)){
        return false;
    }
    if (it==expression.end()){
        g=g1;
        return true;
    }
    operator_token=*it;
    Tokens::const_iterator jt=it;
    while (it!=expression.end()){
        it++;
        operator_token=*jt;
        if (!isBinaryOp(operator_token)){
            return false;
        }
        future_expressions=inRange(expression,it-expression.begin(),expression.size());
        jt=future_expressions.begin();
        if (!identifyFirstExpression(future_expressions,g2,jt)){
            return false;
        }
        it+=jt-future_expressions.begin();
        g1=applyBinaryOp(g1,g2,operator_token);
    }
    g=g1;
    return true;
}
