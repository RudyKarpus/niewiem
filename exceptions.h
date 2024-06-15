#ifndef FML_EXCEPTIONS_H
#define FML_EXCEPTIONS_H
#include <iostream>

class FileOpenFailedException : public std::exception {
    char * what () {
        return "File cannot be opened";
    }
};


#endif //FML_EXCEPTIONS_H
