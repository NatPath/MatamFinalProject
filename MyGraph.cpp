#include "MyGraph.h"

////// non member functions
bool check_graph_validity(const Vertices& v,const Edges& e){
    for(auto it =e.begin(); it!=e.end(); it++){
        /*
        if (!setContains(v,it->first)||!setContains(v,it->second)){
            return false;
        }
        */
       if(!edgeValid(*it,v)){
           return false;
       }
    }
    return true;
}
bool edgeValid(const Edge& edge,const Vertices& vertices){
    return setContains(vertices,edge.first)&&setContains(vertices,edge.second);
}
void graphToBinaryFile(const Graph& graph,std::ofstream& file){

    const Edges edges= graph.getEdges();
    const Vertices vertices= graph.getVertices();

    unsigned int num_vertices=vertices.size();
    unsigned int num_edges=edges.size();

    //write num_vertices to file
    file.write(reinterpret_cast<const char*>(&num_vertices),sizeof(num_vertices));

    //write num_edges to file
    file.write(reinterpret_cast<const char*>(&num_edges),sizeof(num_edges));
    unsigned int word_size;
    char letter;
    //write vertices
    for (auto it = vertices.begin(); it!=vertices.end();it++){
        word_size=it->size();
        //write size_of vertex
        file.write(reinterpret_cast<const char*>(&word_size),sizeof(word_size));
        //write vertex letters
        for (unsigned int i=0;i<it->size();i++){
            letter=(*it)[i];
            file.write(reinterpret_cast<const char*>(&letter),sizeof(char));

        }
    }
    //write edges 
    for (auto it = edges.begin();it!=edges.end();it++){
        word_size=it->first.size();
        //write first vertex of edge
        file.write(reinterpret_cast<const char*>(&word_size),sizeof(word_size));
        //write first vertex letters
        for (unsigned int i=0;i<(it->first).size();i++){
            letter=(it->first)[i];
            file.write(reinterpret_cast<const char*>(&letter),sizeof(char));
        }

        word_size=it->second.size();
        //write second vertex of edge
        file.write(reinterpret_cast<const char*>(&word_size),sizeof(word_size));
        //write second vertex letters
        for (unsigned int i=0;i<(it->second).size();i++){
            letter=(it->second)[i];
            file.write(reinterpret_cast<const char*>(&letter),sizeof(char));
        }
    }
}


Graph full_graph(const Vertices& v){
    Edges edges;
    for (auto it=v.begin();it!=v.end();it++){
        for (auto jt=v.begin();jt!=v.end();jt++){
            if (*it!=*jt){
                edges.insert(Edge(*it,*jt));
            }
        }
    }
    return Graph(v,edges);
}

/////// Graph methods:
Graph::Graph(const Vertices& vertices,const Edges& edges){
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
        std::inserter(new_vertices,new_vertices.begin())
    );
    std::set_intersection(
        b.edges.begin(),b.edges.end(),
        edges.begin(),edges.end(),
        std::inserter(new_edges,new_edges.begin())
    );
    return Graph(new_vertices,new_edges);

}

Graph Graph::operator-(const Graph& b) const{
    Vertices new_vertices;
    Edges new_edges;
    std::set_difference(
        vertices.begin(),vertices.end(),
        b.vertices.begin(),b.vertices.end(),
        std::inserter(new_vertices,new_vertices.begin())
    );
    for (auto it=edges.begin();it!=edges.end();it++){
        if (edgeValid(*it,new_vertices)){
            new_edges.insert(*it);
        }
    }
    return Graph(new_vertices,new_edges);
}

Vertex constructProductVertex(const Vertex& a,const Vertex& b){
    Vertex new_vertex= "["+a+";"+b+"]";
    return new_vertex;
}

Edge constructProductEdge(const Edge& a,const Edge& b){
    Edge new_edge;    
    new_edge.first=constructProductVertex(a.first,b.first);
    new_edge.second=constructProductVertex(a.second,b.second);
    return new_edge;
}
//product
Graph Graph::operator*(const Graph& b) const{
    Vertices new_vertices;
    Edges new_edges;
    for (auto it=vertices.begin();it!=vertices.end();it++){
        for (auto jt=b.vertices.begin();jt!=b.vertices.end();jt++){
            new_vertices.insert(constructProductVertex(*it,*jt));
        }
    }
    for (auto it=edges.begin();it!=edges.end();it++){
        for (auto jt=b.edges.begin();jt!=b.edges.end();jt++){
            new_edges.insert(constructProductEdge(*it,*jt));            
        }
    }
    return Graph(new_vertices,new_edges);
}

//complement
Graph Graph::operator!() const{
    Graph full=full_graph(vertices);
    Edges full_edges=full.edges;
    for (auto it=edges.begin();it!=edges.end();it++){
        full_edges.erase(*it);
    }
    return Graph(vertices,full_edges);
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
const Vertices& Graph::getVertices() const{
    return vertices;        
}
const Edges& Graph::getEdges() const{
    return edges;
}


void Graph::addVertex(const Vertex& v){
    vertices.insert(v);
}
void Graph::addEdge(const Edge& e){
    edges.insert(e);
}
void Graph::addEdge(const Vertex& v1, const Vertex& v2){
    Edge e(v1,v2);
    edges.insert(e);
}
Graph applyBinaryOp(const Graph& g1,const Graph& g2,std::string& operator_token){
    if (operator_token=="+"){
        return g1+g2;
    }
    if (operator_token=="^"){
        return g1^g2;
    }
    if (operator_token=="-"){
        return g1-g2;
    }
    if (operator_token=="*"){
        return g1*g2;
    }
    //shouldnt get here
    throw BinaryOperatorFault(operator_token);
    return g1;
}