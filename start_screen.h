#ifndef FML_START_SCREEN_H
#define FML_START_SCREEN_H
#pragma once
#include "fmt/color.h"
#include "app_container.h"
#include <SFML/Graphics.hpp>


enum class StartScreenState{start, options, load_last_save};


class Start_Screen {
private:
    App_Container* appContainer;
    StartScreenState checked = StartScreenState::start;

public:
    Start_Screen(App_Container* container);
    void state_next();
    void state_back();
};


#endif //FML_START_SCREEN_H
