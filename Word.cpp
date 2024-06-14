#include "Word.h"
#include <iostream>
#include <vector>
#include<cstdlib>
#include <cmath>


Word::Word(std::vector<std::string> &words_list, int posy)
{
    this->posx = 1;
    int random_number;

    random_number = rand()%100 + 50;
    this->worth = random_number;

    this->posy = posy;
    random_number = rand()%words_list.size();

    this->word = words_list.at(random_number);
    words_list.erase(words_list.begin()+random_number);
}

void Word::accelerate()
{
    double random_number = rand()%(600);
    if (random_number <= log(pow(posx, sqrt(posx)))/5)
    {
        posx ++;
    }
}

std::ostream &operator<<(std::ostream &os, Word &w) {
    os << w.word << " " << w.worth << " " << w.posx << " " << w.posy;
    return os;
}

std::istream &operator>>(std::istream &is, Word &w) {
    is >> w.word >> w.worth >> w.posx >> w.posy;
    return is;
}

