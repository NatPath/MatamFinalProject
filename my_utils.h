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
bool setContains(std::set<T>& s,T elem){
    return s.find(elem)!=s.end();
}
Tokens inRange(Tokens vec,int start,int end){
    Tokens res;    
    if (vec.size()<=end||start<0||start>end){
        throw OutOfRange();
    }
    for (int i=start;i<end;i++){
        res.push_back(vec[i]);
    }
    return res;
}
template<class T,class S>
bool operator==(std::pair<T,S> a,std::pair<T,S> b){
    return a.first==b.first&&a.second==b.second;
}

#endif