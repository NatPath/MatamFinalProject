#ifndef _MY_UTILS_H
#define _MY_UTILS_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <exception>
#include <regex>
#include <algorithm>


//"Naming things is useful for readability and sanity"- Albert Einstein
typedef std::vector<std::string> Tokens;
typedef std::string Vertex;
typedef std::pair<Vertex,Vertex> Edge;
typedef std::set<Vertex> Vertices;
typedef std::set<Edge> Edges;

//template print for printable objects, assumes T is printable
template<class T>
void print(T str){
    std::cout<<str<<std::endl;
}
//checks if a set contains an element.  assumes T is comparable
template<class T>
bool setContains(const std::set<T>& s,const T& elem){
    return s.find(elem)!=s.end();
}
//compare between two pairs, see if there is a Match of both their fields, assumes T and S are comparble
template<class T,class S>
bool operator==(std::pair<T,S> a,std::pair<T,S> b){
    return a.first==b.first&&a.second==b.second;
}
//returns sub-Tokens starting with element in index of "start" and of the size of "size"
Tokens inRange(const Tokens& vec,int start,int size);
//returns sub-Tokens from iterators , from begin to end
Tokens inRange(const Tokens& vec, Tokens::const_iterator& begin,Tokens::const_iterator& end);

#endif