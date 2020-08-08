#ifndef GRAPH_WRAP_H
#define GRAPH_WRAP_H
#include "MyGraph.h"
//creates a graph
Graph* GraphCreate();
void GraphDestroy(Graph* graph);
Graph* addVertex(Graph* graph,Vertex v);
Graph* addEdge(Graph* graph,Edge e);
void printGraph(Graph* graph);

Graph* graphUnion(Graph* in1,Graph* in2,Graph* out);
Graph* graphIntersection(Graph* in1,Graph* in2,Graph* out);
Graph* graphDifference(Graph* in1,Graph* in2,Graph* out);
Graph* graphProduct(Graph* in1,Graph*in2, Graph* out);
Graph* graphComplement(Graph* in1,Graph*in2, Graph* out);





#endif

