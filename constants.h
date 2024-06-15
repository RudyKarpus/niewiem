#include <iostream>
#include <SFML/Graphics.hpp>
#pragma  once
#ifndef FML_CONSTANTS_H
#define FML_CONSTANTS_H

std::pair<sf::Color, std::string> color_list[7] = {{sf::Color::White, "white"}, {sf::Color::Black, "black"},
                                                     {sf::Color::Red, "red"}, {sf::Color::Blue, "blue"},
                                                     {sf::Color::Yellow, "yellow"},{sf::Color::Green, "green"},
                                                     {sf::Color::Cyan, "Cyan"}};

//can't link constants with game screen
/*
std::pair<sf::Color, std::pair<sf::Color, sf::Color>> highlight_list[7] = {
    {sf::Color::White, {sf::Color::Black, sf::Color::Red}}, {sf::Color::Black, {sf::Color::White, sf::Color::Yellow}},
    {sf::Color::Red, {sf::Color::Green, sf::Color::Blue}}, {sf::Color::Blue, {sf::Color::Red, sf::Color::Yellow}},
    {sf::Color::Yellow, {sf::Color::Black, sf::Color::Cyan}}, {sf::Color::Green, {sf::Color::Red, sf::Color::Blue}},
    {sf::Color::Cyan, {sf::Color::Black, sf::Color::Green}},

};
 */

std::vector<std::string> font_list = {"Lato", "Montserrat", "NunitoSans", "OpenSans", "PlayfairDisplay", "Poppins", "Roboto"};

std::vector<std::pair<game_state, std::string>> game_word_options = {{game_state::short_words, "short words"},
                                                          {game_state::medium_word, "medium words"},
                                                          {game_state::long_words, "long words"},
                                                          {game_state::all, "all"}};



#endif //FML_CONSTANTS_H
