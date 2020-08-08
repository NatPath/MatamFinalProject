#ifndef GRAPH_WRAP_H
#define GRAPH_WRAP_H
#include "MyGraph.h"

enum binary_op{UNION,INTERSECTION,DIFFERENCE,PRODUCT};
//creates a graph
Graph* create();
void destroy(Graph* graph);
Graph* addVertex(Graph* graph,char* v);
Graph* addEdge(Graph* graph,char* v1,char* v2);
void disp(Graph* graph);
Graph* graphUnion(Graph* in1,Graph* in2,Graph* out);
Graph* graphIntersection(Graph* in1,Graph* in2,Graph* out);
Graph* graphDifference(Graph* in1,Graph* in2,Graph* out);
Graph* graphProduct(Graph* in1,Graph*in2, Graph* out);
Graph* graphComplement(Graph* in, Graph* out);





#endif

