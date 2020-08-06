#ifndef _CALC_PARSER_H
#define _CALC_PARSER_H

#include <regex>
#include <exception>
#include <fstream>
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
bool complexGraphExpression(const Tokens& expression, Graph& g);
bool validGraphLoad(const Tokens& expression,Graph& g);

bool legalVertices(const Vertices& vertices);
bool legalEdges(const Edges& edges);

//binary handeling
Graph binaryToGraph(std::vector<unsigned char>& file);
std::vector<unsigned char> graphToBinary(const Graph& graph);





#endif