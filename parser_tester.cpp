#include "calc_parser.h"

#include <iostream>
#include <string>
#include <utility>

void testParathesesBalance(){
    std::string str;
    std::getline(std::cin,str);
    bool res = checkParenthesesBalance(str);
    std::cout<<res<<std::endl;

}
void testRegex(){
    std::string str;
    std::getline(std::cin,str);
    bool res = validVertexName(str);
    std::cout<<res<<std::endl;

}
int main(){
    //testParathesesBalance();
    testRegex();


    return 0;
}