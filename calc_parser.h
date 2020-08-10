#ifndef _CALC_PARSER_H
#define _CALC_PARSER_H

#include <regex>
#include <exception>
#include <fstream>
#include "my_utils.h"
#include "exceptions.h"
#include "MyGraph.h"


enum ParanthesesTypes {CURLY,SMOOTH};
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

//checks if expression is a valid SINGLE initialization expression { v1 ,v2...|<vi,vj>...}
bool validGraphInitialization(const Tokens& expression,Graph& g);

//checks if the expression is a valid SINGLE load expression
bool validGraphLoad(const Tokens& expression,Graph& g);

//Vertix - Edge legality
bool legalVertices(const Vertices& vertices);
//checks if the Edges have legal names
bool legalEdges(const Edges& edges);

//binary graph handeling functions
Graph binaryToGraph(std::vector<unsigned char>& file);
//Encodes a Graph into binary vector of bytes ( each unsigned char in the vector is a byte)
std::vector<unsigned char> graphToBinary(const Graph& graph);


//Make a token starting with an opening parentheses and stops with a blanced closer
Tokens findClosingParantheses(const Tokens& expression,ParanthesesTypes ptype,Tokens::const_iterator& jt,bool* balanced=0);

//trims even number of "!" which are side by side, makes code faster I guess
Tokens negTrim(const Tokens& expression);

//Given an expression which starts with "!"
//looks for last binary operator and puts ")" before it,
// and a "(" after the "!";
Tokens isolateNeg(const Tokens& expression);

//checks if a string is a binary operator
bool isBinaryOp(std::string str);
//find the next binary operator, sets 'it' to it and return sub tokens util it apears 
Tokens findNextBinaryOperator(const Tokens& expression,Tokens::const_iterator& it);
//gets a string and returns a string with a given char insertet before and after every element of delim
std::string insertCharByDelim(const std::string& str,const std::string delim,char char_to_insert);
//Filters each of the Tokens elements, removes spaces from beginning and end
Tokens filterSpacesPreAndPostFixFromTokens(const Tokens& unfiltered_tokens);
//returns an iterator to the last semi column in the expression( if not found returns end())
Tokens::const_iterator lastSemiColumn(const Tokens& save_expression);
//retruns an iterator to the first element in the Tokens which is identical to str
Tokens::const_iterator firstFirstApearanceOf(const Tokens& expression,const std::string& str);




#endif