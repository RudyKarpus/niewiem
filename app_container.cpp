#include <fstream>
#include "app_container.h"
#include "constants.h"

std::pair<sf::Color, std::string> App_Container::get_background() { return background;}

std::pair<sf::Color, std::string> App_Container::get_font_color() {return font_color;}

std::string App_Container::get_font() {return font;}

std::pair<game_state, std::string> App_Container::get_game_option() {return game_option;}

void App_Container::set_game_option(std::pair<game_state, std::string> new_game_option) {this->game_option = new_game_option;}

void App_Container::set_next_color(color_type type)
{
    std::pair<sf::Color, std::string>* color;
    if (type == color_type::background){
        color = &background;
    }
    else{
        color = &font_color;
    }
    int n = 0;
    for (auto c: color_list)
    {
        if (color->second == c.second)
        {
            break;
        }
        n++;
    }
    if(n==6)
    {
        *color = color_list[0];
        return;
    }
    *color = color_list[n + 1];
}

void App_Container::set_previous_color(color_type type)
{
    std::pair<sf::Color, std::string>* color;
    if (type == color_type::background){
        color = &background;
    }
    else{
        color = &font_color;
    }
    int n = 0;
    for (auto c: color_list)
    {
        if (color->second == c.second)
        {
            break;
        }
        n++;
    }
    if(n==0)
    {
        *color = color_list[6];
        return;
    }
    *color = color_list[n - 1];
}

void App_Container::set_next_font()
{
    int n = 0;
    for(auto font_name: font_list)
    {
        if(font_name == font){break;}
        n++;
    }
    if(n == font_list.size() - 1)
    {
        font = font_list.at(0);
        return;
    }
    font = font_list.at(n+1);
}

void App_Container::set_previous_font()
{
    int n = 0;
    for(auto font_name: font_list)
    {
        if(font_name == font){break;}
        n++;
    }
    if(n == 0)
    {
        font = font_list.at(font_list.size() - 1);
        return;
    }
    font = font_list.at(n - 1);
}

void App_Container::set_next_game_option()
{
    int n = 0;
    for(auto state: game_word_options)
    {
        if (game_option.second == state.second){break;}
        n++;
    }
    if(n == game_word_options.size() - 1)
    {
        game_option = game_word_options.at(0);
        return;
    }
    game_option = game_word_options.at(n+1);
}

void App_Container::set_previous_game_option()
{
    int n = 0;
    for(auto state: game_word_options)
    {
        if (game_option.second == state.second){break;}
        n++;
    }
    if(n == 0)
    {
        game_option = game_word_options.at(game_word_options.size()-1);
        return;
    }
    game_option = game_word_options.at(n-1);
}

void App_Container::set_saved_game_words(std::vector<Word> saved_game_words) {
    this->saved_game_words = saved_game_words;
}

void App_Container::get_saved_data() {
    std::ifstream file("../save.txt");
    if (!file.is_open()) {
        //error
    }
    Word w;
    while (file >> w){
        saved_game_words.push_back(w);
    }
    file.close();
}

std::vector<Word> App_Container::return_word_list() {
    return saved_game_words;
}


