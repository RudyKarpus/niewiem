#ifndef FML_GAME_SCREEN_H
#define FML_GAME_SCREEN_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Word.h"

enum class GameScreenState{play, endPlayAgain, endGoBack};

class Game_Screen {
private:
    sf::RenderWindow *window;
    std::string input = "";
    std::vector<Word> shown_words;
    std::vector<std::string> list_of_words;
    std::string file_name = "../words.txt";
    int points = 0;
    int health = 3;
    GameScreenState state = GameScreenState::play;
public:
    Game_Screen(sf::Color background, sf::Color font_color, sf::Font font, sf::RenderWindow *w);
    void read_file(std::string file_name);
    void next_state();
    void back_state();
};


#endif //FML_GAME_SCREEN_H
