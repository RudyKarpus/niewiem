#include <SFML/Graphics.hpp>
#include "game_screen.h"
#include <fstream>
#include<cstdlib>

std::string static alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}


Game_Screen::Game_Screen(sf::Color background, sf::Color font_color, sf::Font font, sf::RenderWindow *w)
{
    //prepeare screen
    this->window = w;
    read_file(file_name);
    //prepere widgets
    auto background_rec = sf::RectangleShape(sf::Vector2f(800, 600));
    background_rec.setPosition(0, 0);
    background_rec.setFillColor(background);
    sf::Text input_text;
    input_text.setPosition(10, 560);
    input_text.setCharacterSize(24);
    input_text.setFillColor(font_color);
    input_text.setFont(font);
    sf::Text points_text;
    points_text.setPosition(500, 560);
    points_text.setCharacterSize(24);
    points_text.setFillColor(font_color);
    points_text.setFont(font);
    points_text.setStyle(sf::Text::Underlined);
    sf::Text result_text;
    result_text.setPosition(400, 300);
    result_text.setCharacterSize(30);
    result_text.setFillColor(font_color);
    result_text.setFont(font);
    sf::Text play_again;
    play_again.setPosition(100, 450);
    play_again.setCharacterSize(30);
    play_again.setFillColor(font_color);
    play_again.setFont(font);
    sf::Text go_back;
    go_back.setPosition(400, 450);
    go_back.setCharacterSize(30);
    go_back.setFillColor(font_color);
    go_back.setFont(font);
    while (window->isOpen()) {
        if (state == GameScreenState::play) {
            auto event = sf::Event();
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        for (int i = 0; i < shown_words.size(); i++) {
                            Word *w = &shown_words.at(i);
                            if (w->word == toLowerCase(input)) {
                                points += w->worth;
                                shown_words.erase(shown_words.begin() + i);
                                break;
                            }
                        }
                        input = "";
                        break;
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                    {
                        input = input.substr(0, input.length()-1);
                        break;
                    }
                    std::string letter = sf::Keyboard::getDescription(sf::Keyboard::delocalize(event.key.code));
                    if (alphabet.find(letter) != std::string::npos) {
                        input += sf::Keyboard::getDescription(sf::Keyboard::delocalize(event.key.code));
                    }
                }
                if (event.type == sf::Event::Closed) {
                    window->close();
                }
            }
            window->draw(background_rec);

            for (int i = 0; i < shown_words.size(); i++) {
                Word *w = &shown_words.at(i);
                sf::Text text;
                text.setPosition(w->posx, w->posy);
                text.setString(w->word);
                text.setFont(font);
                text.setFillColor(font_color);
                w->accelerate();
                if (w->posx == window->getSize().x)
                {
                    health -= 1;
                    shown_words.erase(shown_words.begin() + i);
                    continue;
                }
                window->draw(text);
            }
            if (health == 0)
            {
                state = GameScreenState::endPlayAgain;
            }
            if (rand() % 20000 >= 19997 - (points - points % 100) / 100) {
                shown_words.push_back(Word(&list_of_words));
            }
            points_text.setString(std::to_string(points));
            input_text.setString("[" + input + "]");
            window->draw(points_text);
            window->draw(input_text);
            window->display();
        }
        else{
            auto event = sf::Event();
            while (window->pollEvent(event)){
                if (event.type == sf::Event::KeyPressed)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        next_state();
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        back_state();
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                    {
                        switch (state)
                        {
                            case GameScreenState::endPlayAgain:
                                state = GameScreenState::play;
                                points = 0;
                                shown_words.clear();
                                read_file(file_name);
                                break;
                            case GameScreenState::endGoBack:
                                return;
                                break;
                        }
                    }
                }
                if (event.type == sf::Event::Closed)
                    window->close();
            }
            play_again.setString("Play Again");
            play_again.setStyle(sf::Text::Regular);
            go_back.setString("Go Back To Menu");
            go_back.setStyle(sf::Text::Regular);
            switch (state)
            {
                case GameScreenState::endPlayAgain:
                    play_again.setString(">Play Again<");
                    play_again.setStyle(sf::Text::Underlined);
                    break;
                case GameScreenState::endGoBack:
                    go_back.setString(">Go Back To Menu<");
                    go_back.setStyle(sf::Text::Underlined);
            }
            window->draw(background_rec);
            window->draw(play_again);
            window->draw(go_back);
            window->display();
        }
    }
}

void Game_Screen::read_file(std::string file_name)
{
    std::ifstream file(file_name);
    if (!file.is_open()) {
        //error
    }

    std::string word;
    while(std::getline(file, word))
    {
        list_of_words.push_back(word);
    }

    file.close();

}

void Game_Screen::next_state()
{
    switch (state)
    {
        case GameScreenState::endPlayAgain:
            state = GameScreenState::endGoBack;
            break;
        case GameScreenState::endGoBack:
            break;
    }

}

void Game_Screen::back_state() {
    switch (state)
    {
        case GameScreenState::endPlayAgain:
            break;
        case GameScreenState::endGoBack:
            state = GameScreenState::endPlayAgain;
            break;
    }
}

