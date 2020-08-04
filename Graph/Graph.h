#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <exception>
#include <regex>
#include <algorithm>


using namespace std;
typedef string Vertex;
typedef pair<Vertex,Vertex> Edge;
typedef set<Vertex> Vertices;
typedef set<Edge> Edges;
//typedef map<Vertex,set<Vertex>> GraphType;

/**
 * Graph-
 * represents a Graph.
 * */
class Graph {
    private:
    set<Vertex> vertices;
    set<Edge> edges;
    
    Graph full_graph();
    public:
    //constructors
    Graph();
    Graph(Vertices vertices,Edges edges);
    Graph(string to_parse);

    Graph(const Graph& to_copy);//copy constructor
    ~Graph()=default;//destructor



    
    //operators
    Graph operator=(Graph& b);//assignment
    Graph operator+(Graph& b);//union
    Graph operator^(Graph& b);//intersection 
    Graph operator-(Graph& b);//difference
    Graph operator*(Graph& b);//product
    Graph operator!();//complement

    void print();





       
    
};

#endif