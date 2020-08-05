#ifndef _CALC_PARSER_H
#define _CALC_PARSER_H

#include <regex>
#include <exception>
#include "my_utils.h"
#include "exceptions.h"
#include "MyGraph.h"


bool validGraphName(const std::string& graph_name);
bool validVertexName(const std::string& vertex_name);
bool validEdgeName(const Tokens& expression);
bool checkParenthesesBalance(const std::string& str);
//makes a string command into a Tokens
Tokens stringToTokens(const std::string& str);
//makes tokens into one long string
const std::string TokensToString(const Tokens& tokensm);
bool validGraphInitialization(const Tokens& expression,Graph& g);



#endif