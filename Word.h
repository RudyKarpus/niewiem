#ifndef FML_WORD_H
#define FML_WORD_H
#include <iostream>
#include <vector>

class Word {
public:
    std::string word;
    int worth;
    int posx;
    int posy;
    Word() = default;
    Word(std::vector<std::string> &words_list, int posy);
    ~Word(){}
    void accelerate();
    friend std::ostream &operator<<(std::ostream  &os, Word &w);
    friend std::istream &operator>>(std::istream &is, Word&w);
};


#endif //FML_WORD_H
