
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

bool Gcalc::identifyFirstExpression(const Tokens& expression,Graph& g) const{
    Tokens subexpression_temp;
    Tokens subexpression_first;
    Tokens subexpression_second;
    std::string operator_token;
    Graph g1;
    if (expression.size()==0){
        return false;
    }

    //negation is an opener
    if (expression[0]=="!"){
        Tokens after_neg_trim=negTrim(expression);
        if (after_neg_trim[0]=="!"){
            //adds "(" after ! and ")" before next binary operator;
            after_neg_trim=isolateNeg(after_neg_trim);
            subexpression_first=inRange(after_neg_trim,1,after_neg_trim.size());
            g1=makeGraph(subexpression_first);
        }
        else{
            g1=makeGraph(after_neg_trim);
        }
        g=!g1;
        return true;
    }
    //some kind of parantheses is opener
    bool balanced;
    if (expression[0]=="("){
        subexpression_temp=findClosingParantheses(expression,SMOOTH,&balanced);        
        if (!balanced){
            return false;
        }
        subexpression_first=inRange(subexpression_temp,1,subexpression_temp.size()-1);
        g1=makeGraph(subexpression_first);
    }
    if (expression[0]=="{"){
        subexpression_temp=findClosingParantheses(expression,CURLY,&balanced);        
        subexpression_first=subexpression_temp;
        if (!balanced){
            return false;
        }
        if (!validGraphInitialization(subexpression_first,g1)){
            throw IllegalAssignmentException(TokensToString(subexpression_first));
        }          
    }
    //first expression is supposed to be regular
    if (expression[0]!="{"&&expression[0]!="("){
        subexpression_temp=inRange(expression,0,1);
        g1=makeGraph(subexpression_temp);        
    }

    //subexpression with parantheses is all the expression
    if (subexpression_temp.size()==expression.size()){
        g=makeGraph(subexpression_first);
        return true;
    }

    operator_token=expression[subexpression_temp.size()];
    if (!isBinaryOp(operator_token)){
        return false;
    }

    

}

bool Gcalc::complexGraphExpression(const Tokens& expression, Graph& g) const{
    //expression starts with parantheses
    Tokens subexpression_temp;
    Tokens subexpression_first;
    Tokens subexpression_second;
    std::string operator_token;
    Graph g1;
    Graph g2;
    if (expression.size()==0){
        return false;
    }
    //negation is an opener
    if (expression[0]=="!"){
        Tokens after_neg_trim=negTrim(expression);
        if (after_neg_trim[0]=="!"){
            //adds "(" after ! and ")" before next binary operator;
            after_neg_trim=isolateNeg(after_neg_trim);
            subexpression_first=inRange(after_neg_trim,1,after_neg_trim.size());
            g1=makeGraph(subexpression_first);
        }
        else{
            g1=makeGraph(after_neg_trim);
        }
        g=!g1;
        return true;
    }
    //some kind of parantheses is opener
    bool balanced;
    if (expression[0]=="("){
        subexpression_temp=findClosingParantheses(expression,SMOOTH,&balanced);        
        if (!balanced){
            return false;
        }
        subexpression_first=inRange(subexpression_temp,1,subexpression_temp.size()-1);
        g1=makeGraph(subexpression_first);
    }
    if (expression[0]=="{"){
        subexpression_temp=findClosingParantheses(expression,CURLY,&balanced);        
        subexpression_first=subexpression_temp;
        if (!balanced){
            return false;
        }
        if (!validGraphInitialization(subexpression_first,g1)){
            throw IllegalAssignmentException(TokensToString(subexpression_first));
        }          
    }
    //first expression is supposed to be regular
    if (expression[0]!="{"&&expression[0]!="("){
        subexpression_temp=inRange(expression,0,1);
        g1=makeGraph(subexpression_temp);        
    }

    //subexpression with parantheses is all the expression
    if (subexpression_temp.size()==expression.size()){
        g=makeGraph(subexpression_first);
        return true;
    }

    operator_token=expression[subexpression_temp.size()];
    if (!isBinaryOp(operator_token)){
        return false;
    }

    //lookForNextExpression(inRange(expression,subexpression_temp.size(),expression.size()));

    if (expression.size()-subexpression_temp.size()==1){
        return false;//can't be only two tokens in a complex which is not '!'
    }

    // problem!!!
    subexpression_second=inRange(expression,subexpression_temp.size()+1,expression.size());
    g2=makeGraph(subexpression_second);

    if (operator_token=="+"){
        g=g1+g2;        
        return true;
    }
    if (operator_token=="-"){
        g=g1-g2;
        return true;
    }
    if (operator_token=="*"){
        g=g1*g2;
        return true;
    }
    if (operator_token=="^"){
        g=g1^g2;
        return true;
    }
    return false;
    
}
