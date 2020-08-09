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

Tokens inRange(const Tokens& vec,int start,int end){
    Tokens res;    
    if (int(vec.size())<end||start<0||start>end){
        throw OutOfRange();
    }
    for (int i=start;i<end;i++){
        res.push_back(vec[i]);
    }
    return res;
}
Tokens inRange(const Tokens& vec, Tokens::const_iterator& begin,Tokens::const_iterator& end){
    Tokens res;
    Tokens::const_iterator it=begin;
    while (it!=end){
        res.push_back(*it++);
    }
    return res;
}