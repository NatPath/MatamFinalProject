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


typedef std::vector<std::string> Tokens;
typedef std::string Vertex;
typedef std::pair<Vertex,Vertex> Edge;
typedef std::set<Vertex> Vertices;
typedef std::set<Edge> Edges;

template<class T>
void print(T str){
    std::cout<<str<<std::endl;
}
template<class T>
bool setContains(const std::set<T>& s,const T& elem){
    return s.find(elem)!=s.end();
}
template<class T,class S>
bool operator==(std::pair<T,S> a,std::pair<T,S> b){
    return a.first==b.first&&a.second==b.second;
}

Tokens inRange(const Tokens& vec,int start,int end);

#endif