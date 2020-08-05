#include "my_utils.h"
void print(const std::string& str){
    try{
        std::cout<<str<<std::endl;
    }
    catch(...){
        throw;
    }
}