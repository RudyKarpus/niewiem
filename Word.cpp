#include "Word.h"
#include <iostream>
#include <vector>
#include<cstdlib>


Word::Word(std::vector<std::string> *words_list)
{
    int random_number;

    random_number = rand()%words_list->size();
    this->word = words_list->at(random_number);
    words_list->erase(words_list->begin()+random_number);

    random_number = rand()%100 + 50;
    this->worth = random_number;

    random_number = rand()%500 + 10;
    this->posy = random_number;
}

void Word::accelerate()
{
    int random_number = rand()%1000;
    int r = posy%20;
    if(random_number+(posx-r)/20>995)
    {
        posx++;
    }
}
