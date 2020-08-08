#include <iostream>
#include <fstream>

#include "my_utils.h"
#include "Gcalc.h"

void menual_mode(){
    Gcalc calc(menual);
    calc.start();
}
void batch_mode(const char* input_file,const char* output_file){
    Gcalc calc(batch);
    std::ifstream in(input_file);
    if(!in){
        std::cerr<<"cannot open file "<<input_file<<std::endl;
        return;
    }
    std::cin.rdbuf(in.rdbuf());
    std::ofstream out(output_file);
    if(!out){
        std::cerr<<"cannot open file "<<output_file<<std::endl;
        return;
    }
    std::cout.rdbuf(out.rdbuf());
    calc.start();
        
}
int main(int argc, char** argv){
    if (argc==1){
        menual_mode();
    }            
    else if (argc==3){
        batch_mode(argv[1],argv[2]);
    }
    else{
        std::cerr<<"Error: Invalid program arguments"<<std::endl;
    }
    return 0;
}