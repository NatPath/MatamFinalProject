#include "Graph.h"

bool check_graph_validity(Vertices vertices, Edges edges){
    
}
Graph::Graph(Vertices vertices, Edges edges){
    try{
        check_graph_validity(vertices,edges);
        this->vertices=vertices;
        this->edges=edges;
    }
    catch(...){
        throw;
    }
}
Graph::Graph(std::string to_parse){

}

//assignment
Graph Graph::operator=(Graph& b){

}
//union
Graph Graph::operator+(Graph& b){
    Vertices new_vertices;
    Edges new_edges;
    std::set_union(
        b.vertices.begin(),b.vertices.end(),
        vertices.begin(),vertices.end(),
        std::back_inserter(new_vertices)
    );
    std::set_union(
        b.edges.begin(),b.edges.end(),
        edges.begin(),edges.end(),
        std::back_inserter(new_edges)
    );
    return Graph(new_vertices,new_edges);

}
//intersection 
Graph Graph::operator^(Graph& b){
    Vertices new_vertices;
    Edges new_edges;
    std::set_intersection(
        b.vertices.begin(),b.vertices.end(),
        vertices.begin(),vertices.end(),
        std::back_inserter(new_vertices)
    );
    std::set_union(
        b.edges.begin(),b.edges.end(),
        edges.begin(),edges.end(),
        std::back_inserter(new_edges)
    );
    return Graph(new_vertices,new_edges);

}
//product
Graph Graph::operator*(Graph& b){

}
Graph Graph::operator!(){


}
//complement