#include "MyGraph.h"

/*
bool check_graph_validity(Vertices vertices, Edges edges){
    
}
*/
bool check_graph_validity(Vertices& v,Edges& e){
    for(auto it =e.begin(); it!=e.end(); it++){
        if (!setContains(v,it->first)||!setContains(v,it->second)){
            return false;
        }
    }
    return true;
}
Graph::Graph(Vertices& vertices,Edges& edges){
    if(check_graph_validity(vertices,edges)){
        this->vertices=vertices;
        this->edges=edges;
    }
    else{
        throw GraphInitException();
    }
}
Graph::Graph(std::string to_parse){

}

//copy constructor
Graph::Graph(const Graph& to_copy){
    vertices=to_copy.vertices;
    edges=to_copy.edges;
}
void Graph::setEdges(const Edges& new_edges){
    edges=new_edges;
}
void Graph::setVertices(const Vertices& new_vertices){
    vertices=new_vertices;
}

//boolean operators
bool Graph::operator==(const Graph& b) const{
    return vertices==b.vertices && edges==b.edges;
}
bool Graph::operator!=(const Graph& b) const{
    return !(*this==b);
}

//assignment
Graph& Graph::operator=(const Graph& b){
    if(*this==b){
        return *this;
    }
    vertices=b.vertices;
    edges=b.edges;
    return *this;
}

//union
Graph Graph::operator+(const Graph& b) const{
    Vertices new_vertices;
    Edges new_edges;
    std::set_union(
        b.vertices.begin(),b.vertices.end(),
        vertices.begin(),vertices.end(),
        std::inserter(new_vertices,new_vertices.begin())
    );
    std::set_union(
        b.edges.begin(),b.edges.end(),
        edges.begin(),edges.end(),
        std::inserter(new_edges,new_edges.begin())
    );
    return Graph(new_vertices,new_edges);

}
//intersection 
Graph Graph::operator^(const Graph& b) const{
    Vertices new_vertices;
    Edges new_edges;
    std::set_intersection(
        b.vertices.begin(),b.vertices.end(),
        vertices.begin(),vertices.end(),
//        std::back_inserter(new_vertices)
        std::inserter(new_vertices,new_vertices.begin())
    );
    std::set_union(
        b.edges.begin(),b.edges.end(),
        edges.begin(),edges.end(),
        std::inserter(new_edges,new_edges.begin())
    );
    return Graph(new_vertices,new_edges);

}
//product
Graph Graph::operator*(const Graph& b) const{
    return b;

}
//complement
Graph Graph::operator!() const{
    return *this;
}

void printEdge(Edge edge){
    print(edge.first+" "+edge.second);
}
void Graph::printGraph() const{
    //print vertices
    for(auto it=vertices.begin();it!=vertices.end();it++){
        print(*it);        
    }
    print("$");
    for(auto it=edges.begin();it!=edges.end();it++){
        printEdge(*it);
    }
}