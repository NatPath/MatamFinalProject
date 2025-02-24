#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>

/*
using std::cout;
using std::string;
using std::pair;
using std::set;
*/
typedef std::string Vertex;
typedef std::pair<Vertex,Vertex> Edge;
typedef std::set<Vertex> Vertices;
typedef std::set<Edge> Edges;
//typedef map<Vertex,set<Vertex>> GraphType;

/**
 * Graph-
 * represents a Graph.
 * */
class Graph {
    private:
    std::set<Vertex> vertices;
    std::set<Edge> edges;
    
    Graph full_graph();
    public:
    //constructors
    Graph();
    Graph(Vertices vertices,Edges edges);
    Graph(std::string to_parse);

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