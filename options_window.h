#ifndef FML_OPTIONS_WINDOW_H
#define FML_OPTIONS_WINDOW_H
#include <SFML/Graphics.hpp>
#include "app_container.h"
#pragma  once


enum class OptionsScreenState{background, font_color, font, game_mode};

class Options_Window {
private:
    App_Container* appContainer;
    sf::RenderWindow *window;
    OptionsScreenState checked = OptionsScreenState::background;
public:
    Options_Window(App_Container* container, sf::RenderWindow *w);
    void clicked_next();
    void state_next();
    void state_back();
};


#endif //FML_OPTIONS_WINDOW_H
