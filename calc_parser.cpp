#include "calc_parser.h"
#include <stack>

bool validGraphName(std::string graph_name){
    std::regex reg ("[a-zA-Z]+[a-zA-Z0-9\\[\\]]*");

}
bool validVertexName(const std::string& vertex_name){
    std::regex contains_only_reg ("[[:alnum:]\\[\\];]*");
    bool contains_only = std::regex_match(vertex_name,contains_only_reg);
    if (!contains_only){
        std::cout<<"Contains an illegal Character"<<std::endl;
        print("contains illegal character");
    }
    bool parenthesesBalanced=checkParenthesesBalance(vertex_name);
    //std::regex semicol_in_the_middle_reg ("([^;]*(\\[[^\\]]*\\])*[^;]*)*");
    if (!parenthesesBalanced){
        print("not ok hoe");
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