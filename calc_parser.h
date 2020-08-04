#ifndef _CALC_PARSER_H
#define _CALC_PARSER_H

#include <regex>
#include "my_utils.h"
#include <exception>

bool validGraphName(const std::string& graph_name);
bool validVertexName(const std::string& vertex_name);
bool checkParenthesesBalance(const std::string& str);

class ParserException : public std::invalid_argument{
    std::string error;
    public:


    ParserException(const std::string error_class){
        error =std::string("Error: " +error_class);
    };
    const char* what() const noexcept override{
        return error.c_str();
    };
};



#endif