#ifndef FML_WORD_H
#define FML_WORD_H
#include <iostream>
#include <vector>

class Word {
public:
    std::string word;
    int worth;
    int speed=0;
    int posx=0;
    int posy;

    Word(std::vector<std::string> *words_list);
    void accelerate();
};


#endif //FML_WORD_H
