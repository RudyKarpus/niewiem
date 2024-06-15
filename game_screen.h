#ifndef FML_GAME_SCREEN_H
#define FML_GAME_SCREEN_H
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Word.h"
#include "app_container.h"

enum class GameScreenState{play, endPlayAgain, endGoBack, pauseresume, pausesave};

class Game_Screen {
private:
    sf::RenderWindow *window;
    App_Container* appContainer;
    std::string input = "";
    std::vector<Word> shown_words;
    std::vector<std::string> list_of_words;
    int points;
    int health;
    GameScreenState state = GameScreenState::play;
public:
    Game_Screen(App_Container* container, sf::RenderWindow *w, std::vector<Word> shown_words, int points = 0, int health = 3);
    void read_file();
    void next_state();
    void back_state();
    void save_to_file();
    int determine_word_pos();
    int getPoints();
    int getHealth();

};


#endif //FML_GAME_SCREEN_H
