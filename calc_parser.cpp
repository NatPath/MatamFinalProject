#include "calc_parser.h"
#include <stack>

bool validGraphName(std::string graph_name){
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
        std::cout<<"Contains an illegal Character"<<std::endl;
        print("contains illegal character");
        throw ParserException("Vertex name Contains an illegal Character");
    }
    bool parenthesesBalanced=checkParenthesesBalance(vertex_name);
    //std::regex semicol_in_the_middle_reg ("([^;]*(\\[[^\\]]*\\])*[^;]*)*");
    if (!parenthesesBalanced){
        throw ParserException("Vertex name's Parentheses rules are not met (might be regarding semicolumn)");
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

Edge validEdgeName(const Tokens& edge_name){
    Vertex v;
    Edge res;
    if (edge_name.size()==5 &&
         edge_name[0]=="<"&&
         edge_name[4]==">"&&
         edge_name[2]==","&&
         validVertexName(edge_name[1])&&
         validVertexName(edge_name[3])){
             res=Edge(edge_name[1],edge_name[3]);
    }
    else{
        throw IllegalEdgeNameException(TokensToString(edge_name));
    }
    if (edge_name[0]=="<")
    return true;
}

Tokens& filterTokensByReg(Tokens& tokens,std::regex& reg){
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
    //const std::string delims= "+*,<>(){}|";
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
    const std::string delims= "+*^!,<>(){}|";
    std::string str_spaces_inserted=insertSpaces(str,delims);
    std::stringstream ss(str_spaces_inserted);
    std::string tmp;
    Tokens words;
    while(getline(ss,tmp,(' '))){
        words.push_back(tmp);
    }
    //remove spaces
    std::regex only_spaces ("[\\s]*");
    return filterTokensByReg(words,only_spaces);
}
const std::string TokensToString(const Tokens& tokens){
    std::string res;
    for (auto it=tokens.begin(); it!=tokens.end(); it++){
        res+=*it;
    }
    return res;
}
Graph validGraphInitialization(const Tokens& expression){
    Vertices v;    
    Edges e;

}

