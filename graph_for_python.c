#include "graph_for_python.h"
#include "calc_parser.h"

Graph* GraphCreate(){
    Graph g;
    return &g;
}
void GraphDestroy(Graph* graph){
    if(!graph){
        free(graph);
    }
}
Graph* addVertex(Graph* graph,Vertex v){
    if (validVertexName(v)){
        graph->addVertex(v);
        return graph;
    }
    else{
        print("Error: Illegal Vertex name");
        return NULL;
    }
}
Graph* addEdge(Graph* graph,Edge e){
    if (edgeValid(e,graph->getVertices())){
        graph->addEdge(e);
        return graph;
    }
    else{
        print("Error: Illegal Edge for the graph given, missing endpoint");
        return NULL;
    }
}
void printGraph(Graph* graph){
    graph->printGraph();
}

Graph* graphUnion(Graph* in1,Graph* in2,Graph* out){
    *out=*in1+*in2;
    return out;
}
Graph* graphIntersection(Graph* in1,Graph* in2,Graph* out){
    *out=*in1^*in2;
    return out;
}
Graph* graphDifference(Graph* in1,Graph* in2,Graph* out){
    *out=*in1-*in2;
    return out;

}
Graph* graphProduct(Graph* in1,Graph*in2, Graph* out){
    *out=*in1*(*in2);
    return out;
}
Graph* graphComplement(Graph* in, Graph* out){
    *out=!(*in);
    return out;
}