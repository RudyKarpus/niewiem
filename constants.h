#include <iostream>
#include <SFML/Graphics.hpp>
#ifndef FML_CONSTANTS_H
#define FML_CONSTANTS_H
std::pair<sf::Color, std::string> color_list[7] = {{sf::Color::White, "white"}, {sf::Color::Black, "black"},
                                                     {sf::Color::Red, "red"}, {sf::Color::Blue, "blue"},
                                                     {sf::Color::Yellow, "yellow"},{sf::Color::Green, "green"},
                                                     {sf::Color::Cyan, "Cyan"}};

std::string font_list[7] = {"Lato", "Montserrat", "NunitoSans", "OpenSans", "PlayfairDisplay", "Poppins", "Roboto"};



#endif //FML_CONSTANTS_H
