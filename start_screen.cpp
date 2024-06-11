#include "start_screen.h"
#include "constants.h"
#include <cmath>
#include <SFML/Graphics.hpp>
#include "game_screen.h"



Start_Screen::Start_Screen()
{
    auto window = sf::RenderWindow(
            sf::VideoMode({800, 600}), "",
            sf::Style::Default, sf::ContextSettings(0, 0, 8)
    );

    auto background = sf::RectangleShape(sf::Vector2f(800, 600));
    background.setPosition(0, 0);
    sf::Text background_text;
    background_text.setPosition(50, 200);
    background_text.setCharacterSize(30);
    sf::Text font_color_text;
    font_color_text.setPosition(300, 200);
    font_color_text.setCharacterSize(30);
    sf::Text font_text;
    font_text.setPosition(500, 200);
    font_text.setCharacterSize(30);
    sf::Text start_text;
    start_text.setPosition(350, 400);
    start_text.setCharacterSize(30);
    while (window.isOpen()) {
        auto event = sf::Event();
        sf::Font f;
        if (!f.loadFromFile("../fonts/"+font + ".ttf"))
        {
            // error...
        }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    checked_back();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    checked_next();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    state_next();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    state_back();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    Game_Screen game_screen(background_color.first, font_color.first, f, &window);
                }

            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        background_text.setFont(f);
        background_text.setFillColor(font_color.first);
        background_text.setString(background_color.second);
        background_text.setStyle(sf::Text::Regular);
        font_color_text.setFont(f);
        font_color_text.setFillColor(font_color.first);
        font_color_text.setString(font_color.second);
        font_color_text.setStyle(sf::Text::Regular);
        font_text.setFont(f);
        font_text.setFillColor(font_color.first);
        font_text.setString(font);
        font_text.setStyle(sf::Text::Regular);
        start_text.setFont(f);
        start_text.setFillColor(font_color.first);
        start_text.setString("Start");
        start_text.setStyle(sf::Text::Regular);
        switch (checked) {
            case StartScreenState::background:
                background_text.setString(">"+background_color.second+"<");
                background_text.setStyle(sf::Text::Underlined);
                break;
            case StartScreenState::font_color:
                font_color_text.setString(">"+font_color.second+"<");
                font_color_text.setStyle(sf::Text::Underlined);
                break;
            case StartScreenState::font:
                font_text.setString(">"+font+"<");
                font_text.setStyle(sf::Text::Underlined);
                break;
            case StartScreenState::start:
                start_text.setString(">Start<");
                start_text.setStyle(sf::Text::Underlined);
                break;
        }


        background.setFillColor(background_color.first);
        window.draw(background);
        window.draw(background_text);
        window.draw(font_color_text);
        window.draw(font_text);
        window.draw(start_text);
        window.display();
    }
}

void Start_Screen::checked_next()
{
    switch(checked)
    {
        case StartScreenState::background:
            checked = StartScreenState::font_color;
            break;
        case StartScreenState::font_color:
            checked = StartScreenState::font;
            break;
        case StartScreenState::font:
            checked = StartScreenState::start;
            break;
        case StartScreenState::start:
            break;
    }
}

void Start_Screen::checked_back()
{
    switch(checked)
    {
        case StartScreenState::background:
            break;
        case StartScreenState::font_color:
            checked = StartScreenState::background;
            break;
        case StartScreenState::font:
            checked = StartScreenState::font_color;
            break;
        case StartScreenState::start:
            checked = StartScreenState::font;
            break;
    }
}

void Start_Screen::state_next()
{
    switch(checked)
    {
        case StartScreenState::background:
            set_next_color(&background_color);
            break;
        case StartScreenState::font_color:
            set_next_color(&font_color);
            break;
        case StartScreenState::font:
            set_previous_font();
            break;
        case StartScreenState::start:
            return;
    }
}

void Start_Screen::set_next_color(std::pair<sf::Color, std::string>* color)
{
    int n = 0;
    for(auto col: color_list)
    {
        if(col.second == color->second){break;}
        n++;
    }
    if(n==6)
    {
        *color = color_list[0];
        return;
    }
    *color = color_list[n + 1];
}

void Start_Screen::state_back() {
    switch(checked)
    {
        case StartScreenState::background:
            set_previous_color(&background_color);
            break;
        case StartScreenState::font_color:
            set_previous_color(&font_color);
            break;
        case StartScreenState::font:
            set_next_font();
            break;
        case StartScreenState::start:
            return;
    }
}

void Start_Screen::set_previous_color(std::pair<sf::Color, std::string>* color)
{
    int n = 0;
    for(auto col: color_list)
    {
        if(col.second == color->second){break;}
        n++;
    }
    if(n==0)
    {
        *color = color_list[6];
        return;
    }
    *color = color_list[n - 1];
}


void Start_Screen::set_next_font()
{
    int n = 0;
    for(auto font_name: font_list)
    {
        if(font_name == font){break;}
        n++;
    }
    if(n == 6)
    {
        font = font_list[0];
        return;
    }
    font = font_list[n + 1];
}

void Start_Screen::set_previous_font()
{
    int n = 0;
    for(auto font_name: font_list)
    {
        if(font_name == font){break;}
        n++;
    }
    if(n == 0)
    {
        font = font_list[6];
        return;
    }
    font = font_list[n - 1];
}