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
class IllegalPrintingException: public ParserException{
    public:
    IllegalPrintingException(const std::string& expression):
    ParserException("Illegal Assignment Expression: "+expression){};
};

class IllegalEdgeNameException: public ParserException{
    public:
    IllegalEdgeNameException(const std::string& expression):
    ParserException("Illegal edge name: "+expression){};
};

class OutOfRange:public std::exception{};

class GraphInitException: public ParserException{
    public:
    GraphInitException():
    ParserException("Illegal Graph initialization"){};
};

class IllegalGraphExpression: public ParserException{
    public:
    IllegalGraphExpression(const std::string& expression):
    ParserException("Illegal Graph Expression: " +expression){};
};

class IllegalSaveExpression: public ParserException{
    public:
    IllegalSaveExpression(const std::string& expression):
    ParserException("Illegal Save Expression: " +expression){};
};


class FileDoesntExist: public ParserException{
    public:
    FileDoesntExist(const std::string& filename):
    ParserException("File '" + filename +"' does not exist or can't open"){};
};

class CantWriteToFileException: public ParserException{
    public:
    CantWriteToFileException(const std::string& filename):
    ParserException("Can't write to '" + filename +"'"){};
};

class FileDataIsNotAGraph: public ParserException{
    public:
    FileDataIsNotAGraph():
    ParserException(" File data does not represent a valid graph"){};
};



#endif