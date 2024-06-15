#ifndef FML_APP_CONTAINER_H
#define FML_APP_CONTAINER_H
#include <SFML/Graphics.hpp>
#include "Word.h"
#pragma  once

enum class game_state{short_words, medium_word, long_words, all};
enum class color_type{background, font_color};

class App_Container {
private:
    std::pair<sf::Color, std::string> background {sf::Color::Black, "black"};
    std::pair<sf::Color, std::string> font_color {sf::Color::White, "white"};
    std::string font = "Lato";
    std::pair<game_state, std::string> game_option = {game_state::all, "all"};
    std::vector<Word> saved_game_words;
    std::pair<int, int> saved_game_state;
public:
    App_Container() = default;
    void get_saved_data();
    std::vector<Word> return_word_list();
    std::pair<sf::Color, std::string>  get_background();
    std::pair<sf::Color, std::string> get_font_color();
    std::string get_font();
    std::pair<game_state, std::string> get_game_option();
    std::pair<int, int> get_saved_game_state();
    void set_saved_game_words(std::vector<Word> saved_game_words);
    void set_game_option(std::pair<game_state, std::string> new_game_option);
    void set_next_color(color_type type);
    void set_previous_color(color_type type);
    void set_next_font();
    void set_previous_font();
    void set_next_game_option();
    void set_previous_game_option();
    friend std::ostream &operator<<(std::ostream  &os, App_Container &app);
};


#endif //FML_APP_CONTAINER_H
