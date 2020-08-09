#ifndef _CALC_PARSER_H
#define _CALC_PARSER_H

#include <regex>
#include <exception>
#include <fstream>
#include "my_utils.h"
#include "exceptions.h"
#include "MyGraph.h"


//returns whether graph_name is a legitimate name for a graph
bool validGraphName(const std::string& graph_name);
//returns whether vertex_name is a legitimate name for a vertex
bool validVertexName(const std::string& vertex_name);

//checks whether expression is an edge name
bool validEdgeName(const Tokens& expression);

//checks if str has balanced SQUARE parantheses AND semicolumn is only in the middle of them
bool checkParenthesesBalance(const std::string& str);
//makes a string command into a Tokens
Tokens stringToTokens(const std::string& str);
//makes tokens into one long string
const std::string TokensToString(const Tokens& tokensm);
bool validGraphInitialization(const Tokens& expression,Graph& g);
//makes a
bool complexGraphExpression(const Tokens& expression, Graph& g);
bool validGraphLoad(const Tokens& expression,Graph& g);

//Vertix - Edge legality
bool legalVertices(const Vertices& vertices);
bool legalEdges(const Edges& edges);

//binary graph handeling functions
Graph binaryToGraph(std::vector<unsigned char>& file);
std::vector<unsigned char> graphToBinary(const Graph& graph);

enum ParanthesesTypes {CURLY,SMOOTH};
//Make a token starting with an opening parentheses and stops with a blanced closer
Tokens findClosingParantheses(const Tokens& expression,ParanthesesTypes ptype,Tokens::const_iterator& jt,bool* balanced=0);

//trims even number of "!" which are side by side, makes code faster I guess
Tokens negTrim(const Tokens& expression);

//Given an expression which starts with "!"
//looks for last binary operator and puts ")" before it,
// and a "(" after the "!";
Tokens isolateNeg(const Tokens& expression);

bool isBinaryOp(std::string str);
Tokens findNextBinaryOperator(const Tokens& expression,Tokens::const_iterator& it);
//bool identifyFirstExpression(const Tokens& expression,Graph& g,Tokens::const_iterator& it);
//bool Gcalc::complexGraphExpression(const Tokens& expression, Graph& g);
std::string insertCharByDelim(const std::string& str,const std::string delim,char char_to_insert);


Tokens filterSpacesPreAndPostFixFromTokens(const Tokens& unfiltered_tokens);




#endif