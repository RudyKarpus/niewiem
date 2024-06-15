#include "options_window.h"
#include "exceptions.h"

Options_Window::Options_Window(App_Container* container, sf::RenderWindow *w)
{
    this->appContainer = container;
    this->window = w;

    auto background = sf::RectangleShape(sf::Vector2f(800, 600));
    background.setPosition(0, 0);
    background.setFillColor(appContainer->get_background().first);

    sf::Text background_text;
    background_text.setPosition(50, 200);
    background_text.setCharacterSize(30);
    sf::Text font_color_text;
    font_color_text.setPosition(300, 200);
    font_color_text.setCharacterSize(30);
    sf::Text font_text;
    font_text.setPosition(500, 200);
    font_text.setCharacterSize(30);
    sf::Text game_text;
    game_text.setPosition(350, 400);
    game_text.setCharacterSize(30);

    while (window->isOpen()) {
        auto event = sf::Event();
        while (window->pollEvent(event)) {

            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    state_next();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    state_back();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    switch (checked) {
                        case OptionsScreenState::background:
                            appContainer->set_next_color(color_type::background);
                            break;
                        case OptionsScreenState::font_color:
                            appContainer->set_next_color(color_type::font_color);
                            break;
                        case OptionsScreenState::font:
                            appContainer->set_next_font();
                            break;
                        case OptionsScreenState::game_mode:
                            appContainer->set_next_game_option();
                            break;
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    switch (checked) {
                        case OptionsScreenState::background:
                            appContainer->set_previous_color(color_type::background);
                            break;
                        case OptionsScreenState::font_color:
                            appContainer->set_previous_color(color_type::font_color);
                            break;
                        case OptionsScreenState::font:
                            appContainer->set_previous_font();
                            break;
                        case OptionsScreenState::game_mode:
                            appContainer->set_previous_game_option();
                            break;
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    return;
                }
            }

            if (event.type == sf::Event::Closed)
                window->close();
        }
        sf::Font f;
        if (!f.loadFromFile("../fonts/"+appContainer->get_font() + ".ttf"))
        {
            FileOpenFailedException exception;
            throw  exception;
        }

        background.setFillColor(appContainer->get_background().first);
        background_text.setFont(f);
        background_text.setFillColor(appContainer->get_font_color().first);
        background_text.setString(appContainer->get_background().second);
        background_text.setStyle(sf::Text::Regular);
        font_color_text.setFont(f);
        font_color_text.setFillColor(appContainer->get_font_color().first);
        font_color_text.setString(appContainer->get_font_color().second);
        font_color_text.setStyle(sf::Text::Regular);
        font_text.setFont(f);
        font_text.setFillColor(appContainer->get_font_color().first);
        font_text.setString(appContainer->get_font());
        font_text.setStyle(sf::Text::Regular);
        game_text.setFont(f);
        game_text.setFillColor(appContainer->get_font_color().first);
        game_text.setString(appContainer->get_game_option().second);
        game_text.setStyle(sf::Text::Regular);

        switch (checked) {
            case OptionsScreenState::background:
                background_text.setString(">"+appContainer->get_background().second+"<");
                background_text.setStyle(sf::Text::Underlined);
                break;
            case OptionsScreenState::font_color:
                font_color_text.setString(">"+appContainer->get_font_color().second+"<");
                font_color_text.setStyle(sf::Text::Underlined);
                break;
            case OptionsScreenState::font:
                font_text.setString(">"+appContainer->get_font()+"<");
                font_text.setStyle(sf::Text::Underlined);
                break;
            case OptionsScreenState::game_mode:
                game_text.setString(">"+appContainer->get_game_option().second+"<");
                game_text.setStyle(sf::Text::Underlined);
                break;
        }

        window->draw(background);
        window->draw(background_text);
        window->draw(font_color_text);
        window->draw(font_text);
        window->draw(game_text);
        window->display();
    }
}



void Options_Window::state_next() {
    switch(checked)
    {
        case OptionsScreenState::background:
            checked = OptionsScreenState::font_color;
            break;
        case OptionsScreenState::font_color:
            checked = OptionsScreenState::font;
            break;
        case OptionsScreenState::font:
            checked = OptionsScreenState::game_mode;
            break;
        case OptionsScreenState::game_mode:
            break;
    }
}

void Options_Window::state_back() {
    switch(checked)
    {
        case OptionsScreenState::background:
            break;
        case OptionsScreenState::font_color:
            checked = OptionsScreenState::background;
            break;
        case OptionsScreenState::font:
            checked = OptionsScreenState::font_color;
            break;
        case OptionsScreenState::game_mode:
            checked = OptionsScreenState::font;
            break;
    }
}

