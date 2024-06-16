#include "start_screen.h"
#include <SFML/Graphics.hpp>
#include "game_screen.h"
#include "options_window.h"
#include "exceptions.h"


Start_Screen::Start_Screen(App_Container* container)
{
    this->appContainer = container;
    auto window = sf::RenderWindow(
            sf::VideoMode({800, 600}), "",
            sf::Style::Default, sf::ContextSettings(0, 0, 8)
    );

    auto background = sf::RectangleShape(sf::Vector2f(800, 600));
    background.setPosition(0, 0);
    background.setFillColor(appContainer->get_background().first);
    sf::Font f;
    if (!f.loadFromFile("../fonts/"+appContainer->get_font() + ".ttf"))
    {
        FileOpenFailedException exception;
        throw  exception;
    }
    sf::Text start_text;
    start_text.setPosition(350, 100);
    start_text.setCharacterSize(30);
    sf::Text options_text;
    options_text.setPosition(350, 200);
    options_text.setCharacterSize(30);
    sf::Text load_save;
    load_save.setPosition(308, 300);
    load_save.setCharacterSize(30);
    sf::Text instruction;
    instruction.setPosition(40, 450);
    instruction.setCharacterSize(22);
    instruction.setFont(f);
    instruction.setString("<, >, ^, v use to move through aplication or click on text. \n"
                          "^ and v is  also used to change setting in options. \n"
                          "Use Escape to pause game or go back in options screen");
    while (window.isOpen()) {
        auto event = sf::Event();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    state_back();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    state_next();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    switch (checked)
                    {
                        case StartScreenState::start: {
                            std::vector<Word> list;
                            Game_Screen game_screen(appContainer, &window, list);
                            break;
                        }
                        case StartScreenState::options: {
                            Options_Window optionsWindow(appContainer, &window);
                            break;
                        }
                        case StartScreenState::load_last_save: {
                            appContainer->get_saved_data();
                            Game_Screen game_screen(appContainer, &window, appContainer->return_word_list(), appContainer->get_saved_game_state().first, appContainer->get_saved_game_state().second);
                            break;
                        }
                    }
                }

            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
                if (start_text.getGlobalBounds().contains(worldPosition))
                {
                    std::vector<Word> list;
                    Game_Screen game_screen(appContainer, &window, list);
                }
                else if (options_text.getGlobalBounds().contains(worldPosition))
                {
                    Options_Window optionsWindow(appContainer, &window);
                }
                else if (load_save.getGlobalBounds().contains(worldPosition))
                {
                    appContainer->get_saved_data();
                    Game_Screen game_screen(appContainer, &window, appContainer->return_word_list(), appContainer->get_saved_game_state().first, appContainer->get_saved_game_state().second);
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }
        background.setFillColor(appContainer->get_background().first);
        start_text.setString("Start");
        start_text.setStyle(sf::Text::Regular);
        start_text.setFont(f);
        start_text.setFillColor(appContainer->get_font_color().first);
        options_text.setString("Options");
        options_text.setStyle(sf::Text::Regular);
        options_text.setFont(f);
        options_text.setFillColor(appContainer->get_font_color().first);
        load_save.setString("Load save");
        load_save.setStyle(sf::Text::Regular);
        load_save.setFont(f);
        load_save.setFillColor(appContainer->get_font_color().first);
        instruction.setFillColor(appContainer->get_font_color().first);
        switch (checked) {
            case StartScreenState::start:
                start_text.setString(">Start<");
                start_text.setStyle(sf::Text::Underlined);
                break;
            case StartScreenState::options:
                options_text.setString(">Options<");
                options_text.setStyle(sf::Text::Underlined);
                break;
            case StartScreenState::load_last_save:
                load_save.setString(">Load save<");
                load_save.setStyle(sf::Text::Underlined);
                break;
        }

        window.draw(background);
        window.draw(start_text);
        window.draw(options_text);
        window.draw(load_save);
        window.draw(instruction);
        window.display();
    }
}

void Start_Screen::state_next()
{
    switch(checked)
    {
        case StartScreenState::start:
            checked = StartScreenState::options;
            break;
        case StartScreenState::options:
            checked = StartScreenState::load_last_save;
            break;
        case StartScreenState::load_last_save:
            break;
    }
}

void Start_Screen::state_back()
{
    switch(checked)
    {
        case StartScreenState::start:
            break;
        case StartScreenState::options:
            checked = StartScreenState::start;
            break;
        case StartScreenState::load_last_save:
            checked = StartScreenState::options;
            break;
    }
}

