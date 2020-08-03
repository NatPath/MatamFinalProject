#include "Graph.h"

bool check_graph_validity(Vertices vertices, Edges edges){
    
}
Graph::Graph(Vertices vertices, Edges edges){
    try{
        check_graph_validity(vertices,edges);
        this->vertices=vertices;
        this->edges=edges;
    }
}
Graph::Graph(string to_parse){

}

Graph Graph::operator=(Graph& b){

};//assignment
Graph Graph::operator+(Graph& b){
    Graph dest;
    Vertices new_vertices;
    Edges new_edges;
    std::set_intersection(
        b.vertices.begin(),b.vertices.end(),
        vertices.begin(),vertices.end(),
        std::back_inserter(new_vertices)
    );
    std::set_intersection(
        b.edges.begin(),b.edges.end(),
        edges.begin(),edges.end(),
        std::back_inserter(new_edges)
    );
    return Graph(new_vertices,new_edges);

};//union
Graph Graph::operator^(Graph& b){

};//intersection 
Graph Graph::operator*(Graph& b){

};//product
Graph Graph::operator!(){

};//complement
