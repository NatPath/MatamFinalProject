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
/*
bool validEdgeName(const std::string& edge_name){

}
*/

Tokens stringToTokens(const std::string& str){
    /*
    std::regex words_regex ("[^\\s]+");
    auto words_begin = std::sregex_iterator(str.begin(), str.end(), words_regex);
    auto words_end = std::sregex_iterator();
    Tokens res;
    for (;words_begin!=words_end;words_begin++){
        res.push_back(words_begin*);
    }
    */
    std::string tmp;
    std::stringstream ss(str);
    Tokens words;
    while(getline(ss,tmp,' ')){
        words.push_back(tmp);
    }
    return words;

}