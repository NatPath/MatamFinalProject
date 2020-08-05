#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

class ParserException : public std::exception{
    std::string error;
    public:
    ParserException(const std::string& error_class){
        error =std::string("Error: " +error_class);
    };
    const char* what() const noexcept override{
        return error.c_str();
    };
};
class UnrecognizedCommandException : public ParserException{
    public:
    UnrecognizedCommandException(const std::string& command):
    ParserException("Unrecognized Command: "+command){};
};
class UndefinedVariableException: public ParserException{
    public:
    UndefinedVariableException(const std::string& variable):
    ParserException("Undefined variable: "+variable){};
};
class IllegalAssignmentException: public ParserException{
    public:
    IllegalAssignmentException(const std::string& expression):
    ParserException("Illegal Assignment Expression: "+expression){};
};

class IllegalEdgeNameException: public ParserException{
    public:
    IllegalEdgeNameException(const std::string& expression):
    ParserException("Illegal edge name: "+expression){};
};

class OutOfRange{};



#endif