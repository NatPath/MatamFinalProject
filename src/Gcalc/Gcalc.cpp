
#include "Gcalc.h"


Gcalc::Gcalc(Mode mode):mode(mode){};
void Gcalc::start(){
    std::string command;
    while(command!="quit"){
        std::cout<<"Gcalc> ";
        std::cin>>command;
        parse_command(command);

    }
}