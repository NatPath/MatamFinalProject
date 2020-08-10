#include "graph_for_python.h"
#include "calc_parser.h"

bool checkArguments(Graph* a1,Graph* a2,Graph* a3){
    if(a1==nullptr||a2==nullptr||a3==nullptr){
        print("Error: one of the input arguements given is a nullptr");
        return false;
    }
    return true;
}
bool checkArguments(Graph* a1,Graph* a2){
    if(a1==nullptr||a2==nullptr){
        print("Error: one of the input arguements given is a nullptr");
        return false;
    }
    return true;
}
bool checkArguments(Graph* a1){
    if(a1==nullptr){
        print("Error: graph arguement given is a nullptr");
        return false;
    }
    return true;
}
Graph* applyOperator(Graph* a1,Graph* a2,Graph* out,binary_op op){
    if(!checkArguments(a1,a2,out)){
        return nullptr;
    }
    switch(op){
        case UNION:
        *out=*a1+*a2;        
        break;

        case INTERSECTION:
        *out=(*a1)^(*a2);
        break;

        case DIFFERENCE:
        *out=(*a1)-(*a2);
        break;
        
        case PRODUCT:
        *out=*a1*(*a2);
        break;
    }
    return out;
}

Graph* create(){
    Graph *g;
    try{
        g=new Graph();
    }
    catch(std::exception& e){
        std::cout<<"Error: " << +e.what()<<std::endl;
        return nullptr;
    }
    return g;
}
void destroy(Graph* graph){
    if (checkArguments(graph)){
        free(graph);
    }
    graph=nullptr;
}
Graph* addVertex(Graph* graph,char* v){
    if(checkArguments(graph)){
        try{
            if (validVertexName(v)){
                graph->addVertex(v);
                return graph;
            }
        }
        catch(std::exception& e){
            std::cout<<"Error: " << e.what()<<std::endl;
            return nullptr;
        }
        print("Error: Illegal Vertex name");
    }
    return nullptr;
}
Graph* addEdge(Graph* graph,char* v1,char* v2){
    if (checkArguments(graph)){
        try{
            Edge e(v1,v2);
            if (edgeValid(e,graph->getVertices())){
                graph->addEdge(e);
                return graph;
            }
            print("Error: Illegal Edge for the graph given, missing endpoint");
        }
        catch(std::exception& e){
            std::cout<<"Error: "<<e.what()<<std::endl;
            return nullptr;
        }
    } 
    return nullptr;
}
void disp(Graph* graph){
    if(checkArguments(graph)){
        graph->printGraph();
    }
}

Graph* graphUnion(Graph* in1,Graph* in2,Graph* out){
    return applyOperator(in1,in2,out,UNION);
}
Graph* graphIntersection(Graph* in1,Graph* in2,Graph* out){
    return applyOperator(in1,in2,out,INTERSECTION);
}
Graph* graphDifference(Graph* in1,Graph* in2,Graph* out){
    return applyOperator(in1,in2,out,DIFFERENCE);
}
Graph* graphProduct(Graph* in1,Graph*in2, Graph* out){
    return applyOperator(in1,in2,out,PRODUCT);
}
Graph* graphComplement(Graph* in, Graph* out){
    if(checkArguments(in,out)){
        *out=!(*in);
        return out;
    }
    return nullptr;
}