#include "calc_parser.h"

#include <iostream>
#include <string>
#include <utility>

void testParathesesBalance(){
    std::string str1;
    std::string str2;
    std::getline(std::cin,str1);
    std::getline(std::cin,str2);

    bool res1 = checkParenthesesBalance(str1);
    bool res2 = checkParenthesesBalance(str2);
    print(res1);
    print(res2);

}
void testRegex(){
    std::string str;
    std::getline(std::cin,str);
    bool res = validVertexName(str);
    std::cout<<res<<std::endl;

}
void testTokenizeString(){
    std::cout<<"Enter a string: "<<std::endl;
    std::string str;
    std::getline(std::cin,str);
    Tokens tokens= stringToTokens(str);
    for (auto i =tokens.begin() ;i != tokens.end();i++){
        print(i);
    }
}
int main(){
    //testParathesesBalance();
    testRegex();
    //testTokenizeString();



    return 0;
}