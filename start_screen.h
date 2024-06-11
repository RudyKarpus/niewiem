#ifndef FML_START_SCREEN_H
#define FML_START_SCREEN_H
#pragma once
#include "fmt/color.h"
#include <SFML/Graphics.hpp>


enum class StartScreenState{background, font_color, font, start};


class Start_Screen {
private:
    std::pair<sf::Color, std::string> background_color = { sf::Color::Black, "black"};
    std::pair<sf::Color, std::string> font_color = {sf::Color::White, "white"};
    std::string font = "Lato";
    StartScreenState checked = StartScreenState::background;

public:
    Start_Screen();
    void display();
    void checked_next();
    void checked_back();
    void state_next();
    void set_next_color(std::pair<sf::Color, std::string>* color);
    void state_back();
    void set_previous_color(std::pair<sf::Color, std::string>* color);
    void set_next_font();
    void set_previous_font();
};


#endif //FML_START_SCREEN_H
