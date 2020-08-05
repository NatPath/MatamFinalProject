#ifndef _CALC_PARSER_H
#define _CALC_PARSER_H

#include <regex>
#include <exception>
#include "my_utils.h"

typedef std::vector<const std::string> Tokens;
bool validGraphName(const std::string& graph_name);
bool validVertexName(const std::string& vertex_name);
bool checkParenthesesBalance(const std::string& str);
Tokens stringToTokens(const std::string& str);


class ParserException : public std::exception{
    std::string error;
    public:
    ParserException(const std::string& error_class){
        error =std::string("Error: " +error_class);
    };
    const char* what() const noexcept override{
        return error.c_str();
    };
};



#endif