#ifndef _GRAPH_H
#define _GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <fstream>
#include "my_utils.h"
#include "exceptions.h"




/**
 * Graph-
 * represents a Graph.
 * */
class Graph {
    private:
    std::set<Vertex> vertices;
    std::set<Edge> edges;
    
    public:
    //constructors
    Graph()=default;
    Graph(const Vertices& vertices,const Edges& edges);
    Graph(std::string to_parse);
    Graph(const Graph& to_copy);//copy constructor
    ~Graph()=default;//destructor

    void setEdges(const Edges& new_edges);
    void setVertices(const Vertices& new_vertices);
    const Vertices& getVertices() const;
    const Edges& getEdges() const;

    //operators
    Graph& operator=(const Graph& b);//assignment
    Graph operator+(const Graph& b) const;//union
    Graph operator^(const Graph& b) const;//intersection 
    Graph operator-(const Graph& b) const;//difference
    Graph operator*(const Graph& b) const;//product
    Graph operator!() const;//complement
    bool operator==(const Graph& b) const;//compare
    bool operator!=(const Graph& b) const;//
    void printGraph() const;
    //for python
    void addVertex(const Vertex& v);
    void addEdge(const Edge& e);
    void addEdge(const Vertex& v1, const Vertex& v2);
    
};
//returns a full graph in the context of given vertices
Graph full_graph(const Vertices& v);
//check if all the vertices and edges make sense (not edge connecting to vertices which are not present etc..)
bool check_graph_validity(const Vertices& vertices,const Edges& edges);
//Puts graph data into a binary file
void graphToBinaryFile(const Graph& graph,std::ofstream& file);
//check if edge is valid in the context of which vertices are present
bool edgeValid(const Edge& edge,const Vertices& vertices);
//apply binary operation between two graph arguements
Graph applyBinaryOp(const Graph& g1,const Graph& g2,std::string& operator_token);

#endif