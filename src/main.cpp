#include <iostream>
#include "my_utils/my_utils.h"
#include "Gcalc/Gcalc.h"

void menual_mode(){
    Gcalc calc(menual);
    calc.start();



}
void batch_mode(char* input_file,char* output_file){
    Gcalc calc(batch);
        
}
int main(int argc, char** argv){
    if (argc==1){
        menual_mode();
    }            
    else if (argc==3){
        batch_mode(argv[1],argv[2]);
    }
    else{
        print("Error: Invalid program arguments");
    }
    return 0;
}