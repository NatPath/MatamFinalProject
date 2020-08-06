#include "my_utils.h"
#include "exceptions.h"

void print(const std::string& str){
    try{
        std::cout<<str<<std::endl;
    }
    catch(...){
        throw;
    }
}
Tokens inRange(Tokens vec,int start,int end){
    Tokens res;    
    if (int(vec.size())<=end||start<0||start>end){
        throw OutOfRange();
    }
    for (int i=start;i<end;i++){
        res.push_back(vec[i]);
    }
    return res;
}