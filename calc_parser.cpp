#include <stack>
#include "calc_parser.h"
#include "exceptions.h"

bool validGraphName(const std::string& graph_name){
    std::regex reg ("[a-zA-Z]+[a-zA-Z0-9]*");
    bool res = std::regex_match(graph_name,reg);
    if (!res){
        throw ParserException("Graph name is illegal");
    }
    return res;

}
bool validVertexName(const std::string& vertex_name){
    std::regex contains_only_reg ("[[:alnum:]\\[\\];]*");
    bool contains_only = std::regex_match(vertex_name,contains_only_reg);
    if (!contains_only){
        return false;
    }
    bool parenthesesBalanced=checkParenthesesBalance(vertex_name);
    if (!parenthesesBalanced){
        return false;
    }

    return contains_only&&parenthesesBalanced;
}
//checks if parantheses are balanced and semi colomn are only inside brackets
bool checkParenthesesBalance(const std::string& str){
    int count=0;
    for (char c: str){
        if (c==';'&&count==0){
            return false;
        }
        if (c=='['){
            count++;
        }
        else if (c==']'){
            count--;
            if (count<0){
                return false;
            }
        }
    }
    return count==0;
}

bool validEdgeName(const Tokens& edge_name){
    return (edge_name.size()==5 &&
         edge_name[0]=="<"&&
         edge_name[4]==">"&&
         edge_name[2]==","&&
         validVertexName(edge_name[1])&&
         validVertexName(edge_name[3])&&
         edge_name[1]!=edge_name[3]);
}

Tokens& filterTokensByRegex(Tokens& tokens,std::regex& reg){
    for (auto it=tokens.begin();it != tokens.end();){
        if (std::regex_match(*it,reg)){
            it=tokens.erase(it);
        }
        else{
            it++;
        }
    }
    return tokens;
    
}
//each spot there is a delim in the original string, put spaces around it
std::string insertSpaces(const std::string& str,const std::string delim){
    std::string res;
    for(auto it=str.begin();it!=str.end();it++){
        //if character is in delim, push it with spaces around it
        if (delim.find(*it)!=std::string::npos){
            res+=' ';res+=*it; res+=' ';
        }                
        //else , just push it
        else{
            res+=*it;
        }
    }    
    return res;
}

Tokens stringToTokens(const std::string& str){
    const std::string delims= "+-*^!,<>(){}|=";
    std::string str_spaces_inserted=insertCharByDelim(str,delims,'\0');
    std::stringstream ss(str_spaces_inserted);
    std::string tmp;
    Tokens words;
    while(getline(ss,tmp,('\0'))){
        words.push_back(tmp);
    }
    //remove spaces
    return filterSpacesPreAndPostFixFromTokens(words);
}
const std::string TokensToString(const Tokens& tokens){
    std::string res;
    for (auto it=tokens.begin(); it!=tokens.end(); it++){
        res+=*it;
    }
    return res;
}

//a function which parses the 
bool validGraphInitialization(const Tokens& expression,Graph& graph){
    Edges edges;
    Vertices vertices;
    std::set<std::string> passed_edgers;
    if (expression.size()==0){
        return false;
    }
    if (expression[0]=="{" && expression.back()=="}"){
        //corner cases of empty graph
        if (expression.size()==3 && expression[1]=="|"){
            graph=Graph();
            return true;
        }
        if (expression.size()==2){
            graph=Graph();
            return true;
        }
        //
        //find '|'
        auto pipe = std::find(expression.begin(),expression.end()-1,"|");
        bool expecting_column=false;
        //all elements left of pipe should behave
        for (auto it=expression.begin()+1;it!=pipe;it++,expecting_column=!expecting_column){
            if (expecting_column){
                if(*it!=","){
                    return false;
                }
                continue;
            }
            if (validVertexName(*it)&&!setContains(vertices,*it)){
                vertices.insert(*it);
            }
            else{
                return false;
            }
        }        

        //checks if there is a column right before the pipe(unwanted)
        if(expecting_column){
            //pipe is either non apearant in the expression OR the last
            if (pipe==expression.end()-1||pipe==expression.end()-2){
                graph.setEdges(edges);
                graph.setVertices(vertices);
                return true;
            }
        }
        else{
            return false;
        }
        //all elements right of pipe should behave
        if ((expression.end()-pipe)%6!=1){
            return false;
        }
        expecting_column=false;
        //iterates the edges part of the expression
        for(auto it=pipe+1;it!=expression.end()-1;expecting_column=!expecting_column){
            if (expecting_column){
                if(*it!=","){
                    return false;
                }
                it++;
                continue;
            }
            int start=it-expression.begin();
            Tokens edgers;
            try{
                edgers=inRange(expression,start,start+5);
            }
            catch(OutOfRange e){
                return false;
            }
            if (validEdgeName(edgers)){
                Vertex first=edgers[1];
                Vertex second=edgers[3];
                Edge new_edge(first,second);
                if (setContains(edges,new_edge)){
                    return false;
                }
                else{
                    edges.insert(new_edge);
                }
            }
            it+=5;
        }
        if (check_graph_validity(vertices,edges)){
            graph.setEdges(edges);
            graph.setVertices(vertices);
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
    //shouldn't get here
    return false;
}
//returns sub of tokens containing only the first balanced parantheses expression. jt will be set to one after the closing parantheses
Tokens findClosingParantheses(const Tokens& expression,ParanthesesTypes ptype,Tokens::const_iterator& jt,bool* balanced){
    std::string closing_p;
    std::string opening_p;
    Tokens subexpression;
    switch (ptype){
        case SMOOTH:
        closing_p=")";
        opening_p="(";
        break;
        case CURLY:
        closing_p="}";
        opening_p="{";
        break;
    }
    subexpression.push_back(expression[0]);
    int count=1;

    for (auto it=expression.begin()+1;it!=expression.end();it++){
        subexpression.push_back(*it);
        if (*it == closing_p){
            count--;
        }        
        if (*it == opening_p){
            count++;
        }
        if (count==0){
            if (balanced){
                *balanced=true;
            }
            jt=it+1;
            return subexpression;
        }
    }
    if (balanced){
        *balanced=false;
    }
    jt=expression.end();
    return subexpression;
}

Tokens::const_iterator findFirstApearanceOf(const Tokens& expression,const std::string& str){
    for (auto it = expression.begin();it!=expression.end();it++){
        if (*it==str){
            return it;
        }        
    }
    return expression.end();
}

bool validGraphLoad(const Tokens& expression,Graph& g){
    if(expression.size()<=3){
        return false;
    }
    //first coming closing parantheses is at the end of the expression
    Tokens::const_iterator it = findFirstApearanceOf(expression,")");
    if (it!=expression.end()-1){
        return false;
    }
    if (expression[0]=="load" && expression[1]=="(" && *(expression.end()-1)==")"){
        std::string filename=TokensToString(Tokens(expression.begin()+2,expression.end()-1));      
        checkParenthesesBalance(filename);
        if (filename.find('(')!=std::string::npos||filename.find(')')!=std::string::npos||filename.find(',')!=std::string::npos){
            throw FileDoesntExist(filename);
        }
        std::ifstream file(filename,std::ios_base::binary);        
        if (file.is_open()){
            std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(file),{});
            g=binaryToGraph(buffer);
            return true;
        }
        else{
            throw FileDoesntExist(filename);
        }
    }
    else{
        return false;
    }
}

Graph binaryToGraph(std::vector<unsigned char>& file){
    Graph res_graph;
    size_t vector_size= file.size();
    //atleast 8 bytes for describing how many vertices and edges,
    if (vector_size<8){
        throw FileDataIsNotAGraph();
    }
    //binary operation on first 8 bytes, grabing the information about how many vertices and edges
    unsigned int num_vertices= file[3]<<24 | file[2]<<16 | file[1]<<8 | file[0];
    unsigned int num_edges=file[7]<<24|file[6]<<18|file[5]<<8|file[4];
    //a state machine (FSM) to parse the binary into a graph
    //code duplication in this piece is intentional, allows logic readability
    enum STATE{VERTEX_BEGIN,VERTEX_CHAR,EDGE_BEGIN1,EDGE_CHAR1,EDGE_BEGIN2,EDGE_CHAR2};
    if (num_vertices==0 && num_edges==0 && vector_size==2){
        return Graph();
    }
    Edges edges;
    Vertices vertices;
    std::string current_word="";
    Edge current_edge;
    unsigned int current_word_length;
    STATE state=VERTEX_BEGIN;
    for (auto it=file.begin()+8;it!=file.end();){
        switch(state){
            ////////////////////
            case VERTEX_BEGIN:
            if (file.end()-it<4){
                throw FileDataIsNotAGraph();
            }
            current_word_length=*it++|*it++<<8|*it++<<16|*it++<<24;

            //next state
            state=VERTEX_CHAR;
            
            break;

            ///////////////////
            case VERTEX_CHAR:        
            current_word+=*it;//add character
            it++;
            //next state
            if (current_word.length()==current_word_length){
                vertices.insert(current_word);
                current_word="";                
                if(vertices.size()==num_vertices){
                    state=EDGE_BEGIN1;
                }
                else{
                    state=VERTEX_BEGIN;
                }
            }          
            else{
                state=VERTEX_CHAR;
            }
            break;

            /////////////////
            case EDGE_BEGIN1:
            //the begining of the edge is supposed to be atleast 4 bytes long
            if (file.end()-it<4){
                throw FileDataIsNotAGraph();
            }
            current_word_length=*it++|*it++<<8|*it++<<16|*it++<<24;
            //next state
            state=EDGE_CHAR1;
            break;

            /////////////////
            case EDGE_CHAR1:
            current_word+=*it;//add character
            it++;
            //next state
            if (current_word.length()==current_word_length){
                current_edge.first=current_word;
                current_word="";                
                state=EDGE_BEGIN2;
            }          
            else{
                state=EDGE_CHAR1;
            }
            break;

            /////////////////
            case EDGE_BEGIN2:

            if (file.end()-it<4){
                throw FileDataIsNotAGraph();
            }
            current_word_length=*it++|*it++<<8|*it++<<16|*it++<<24;
            //next state
            state=EDGE_CHAR2;

            /////////////////
            case EDGE_CHAR2:
            current_word+=*it++;            
            //next state
            if (current_word.length()==current_word_length){
                current_edge.second=current_word;
                current_word="";                
                edges.insert(current_edge);
                state=EDGE_BEGIN1;
            }          
            else{
                state=EDGE_CHAR2;
            }
            break;
        }
    }
    //checks if the specifications of the graph are true and the graph created is legal
    if (vertices.size()==num_vertices && edges.size()==num_edges &&
     legalVertices(vertices)&&check_graph_validity(vertices,edges)){
         res_graph.setEdges(edges);        
         res_graph.setVertices(vertices);
         return res_graph;
     }
     else{
         throw FileDataIsNotAGraph();
     }
}

bool legalVertices(const Vertices& vertices){
    for (auto it=vertices.begin();it!=vertices.end();it++){
        if (!validVertexName(*it)){
            return false;
        }                
    }
    return true;
}
Tokens negTrim(const Tokens& expression){
    unsigned int count=0;
    for (auto it=expression.begin();it!=expression.end()&&*it=="!";it++){
        count++;                
    }
    if (count==expression.size()){
        throw IllegalGraphExpression(TokensToString(expression));
    }
    if (count%2==0){
        return inRange(expression,count,expression.size());
    }
    else{
        return inRange(expression,count-1,expression.size());
    }
}

bool isBinaryOp(std::string str){
    return str=="+" || str=="-" || str=="*" ||str=="^";
}
Tokens isolateNeg(const Tokens& expression,unsigned int& place){
    Tokens res;
    res.push_back("!");
    res.push_back("(");
    bool look_for_binary_op=true;
    for (auto it = expression.begin()+1;it!=expression.end();it++){
        if (look_for_binary_op && isBinaryOp(*it)){
            res.push_back(")");
            res.push_back(*it);        
            look_for_binary_op=false;
        }
        else{
            res.push_back(*it);
        }
    }
    if (look_for_binary_op){
        res.push_back(")");
    }
    return res;
}
Tokens findNextBinaryOperator(const Tokens& expression,Tokens::const_iterator& ret_it ){
    Tokens res;
    for (auto it = expression.begin();it!=expression.end();it++){
        if (isBinaryOp(*it)){
            ret_it=it;
            return res;
        }
        else{
            res.push_back(*it);
        }
    }
    ret_it=expression.end();
    return res;
}
///////////////
//each spot there is a delim in the original string, put spaces around it
std::string insertCharByDelim(const std::string& str,const std::string delim,char char_to_insert){
    std::string res;
    for(auto it=str.begin();it!=str.end();it++){
        //if character is in delim, push it with spaces around it
        if (delim.find(*it)!=std::string::npos){
            res+=char_to_insert;res+=*it; res+=char_to_insert;
        }                
        //else , just push it
        else{
            res+=*it;
        }
    }    
    return res;
}

//Filter spaces from beginning and ending of a string
std::string filterSpacesFromString(const std::string& unfiltered_string){
    std::string res_string = unfiltered_string;
    std::regex space_beginning("^[\\s]+");
    std::regex space_ending("[\\s]+$");
    std::smatch beginning_match;
    std::smatch ending_match;
    std::regex_search(unfiltered_string,beginning_match,space_beginning);
    std::regex_search(unfiltered_string,ending_match,space_ending);                
    //res_string=unfiltered_string.substr(beginning_match[0].pos(),ending_match.);
    res_string=std::regex_replace(unfiltered_string,space_beginning,"");
    res_string=std::regex_replace(res_string,space_ending,"");
    return res_string;

}
//Filter Tokens spaces from beginning and ending
Tokens filterSpacesPreAndPostFixFromTokens(const Tokens& unfiltered_tokens){
    Tokens res;        
    std::string string_after_filter;
    for (auto it = unfiltered_tokens.begin();it!=unfiltered_tokens.end();it++){
        string_after_filter=filterSpacesFromString(*it);
        if(string_after_filter!=""){
            res.push_back(string_after_filter);
        }
    }
    return res;    
}

Tokens::const_iterator lastSemiColumn(const Tokens& save_expression){
    if( save_expression.size()==0){
        throw ParserException("save expression is empty");
    }
    for (auto it =save_expression.end()-1;it!=save_expression.begin();it--){
        if (*it==","){
            return it;
        }
    }            
    return save_expression.begin();
}

/////////////////////////////////////////////////
/////// FUNCTIONS GRAVEYARD ///////////////////
///////////////////////////////////////////////
/////////////// RIP //////////////////////////
////////////////////////////////////////////
/*
Tokens stringToTokens(const std::string& str){
    const std::string delims= "+-*^!,<>(){}|=";
    std::string str_spaces_inserted=insertCharByDelim(str,delims,'\0');
    std::stringstream ss(str_spaces_inserted);
    std::string tmp;
    Tokens words;
    while(getline(ss,tmp,('\0'))){
        words.push_back(tmp);
    }
    //remove spaces
    std::regex only_null("[\\0]*");
    return filterTokensByRegex(words,only_null);
}
bool fileNameFix(Tokens& filename_before_fix,const std::string& command){
    std::string
}
bool parseFileCommand(const Tokens& tokens,Tokens& res_tokens, const std::string& command){
    Tokens filename;
    Tokens graph_expression;
    Graph res_graph;
    Tokens::const_iterator i;
    if (tokens.size()>=6&&tokens[0]=="save"&&tokens[1]=="("&& *tokens.end()==")"){
        //search for where the filename starts 
        for (auto it = tokens.end();it!=tokens.begin();it--){
            if (*it==","){
                i=it;
                break;
            }            
        } 
        filename=inRange(tokens,i,tokens.end());
        graph_expression=(tokens,tokens.begin()+2,i);
        try{
            res_graph=makeGraph(graph_expression);
        }
        catch{
            throw IllegalGraphExpression(TokensToString(graph_expression));
        }
        try{
            fileNameFix(filename,command);
        }
    }
}

Tokens fileNameIdentifier(const std::string& str){
    Tokens res_tokens;
    std::string temp_str =str;
    std::regex save("save\\([.]*,[^()<+,]*\\)");        
    std::regex load("load\\(");
    std::string allegady_filename;
    std::string subString;
    std::cmatch match_save_start;
    int it_position=0;
    std::string::const_iterator it=str.begin();
    //look for saves
    while (it!=str.end()){
        if( std::regex_search(temp_str,m,save)){
        }
    }
}
*/