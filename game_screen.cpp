#include <SFML/Graphics.hpp>
#include "game_screen.h"
#include <fstream>
#include<cstdlib>
#include "exceptions.h"

std::string static alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

std::pair<sf::Color, std::pair<sf::Color, sf::Color>> highlight_list[7] = {
        {sf::Color::White, {sf::Color::Black, sf::Color::Red}}, {sf::Color::Black, {sf::Color::White, sf::Color::Yellow}},
        {sf::Color::Red, {sf::Color::Green, sf::Color::Blue}}, {sf::Color::Blue, {sf::Color::Red, sf::Color::Yellow}},
        {sf::Color::Yellow, {sf::Color::Black, sf::Color::Cyan}}, {sf::Color::Green, {sf::Color::Red, sf::Color::Blue}},
        {sf::Color::Cyan, {sf::Color::Black, sf::Color::Green}}};

std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

Game_Screen::Game_Screen(App_Container* container, sf::RenderWindow *w, std::vector<Word> words, int p, int h)
{
    this->appContainer = container;
    this->points = p;
    this->health = h;
    if (!words.empty()) {this->shown_words = words;}
    //prepeare screen
    this->window = w;
    read_file();
    //prepere widgets

    auto background_rec = sf::RectangleShape(sf::Vector2f(800, 600));
    background_rec.setPosition(0, 0);
    background_rec.setFillColor(appContainer->get_background().first);
    sf::Font font;
    if (!font.loadFromFile("../fonts/"+appContainer->get_font() + ".ttf"))
    {
        FileOpenFailedException exception;
        throw  exception;
    }
    sf::Text input_text;
    input_text.setPosition(10, 560);
    input_text.setCharacterSize(24);
    input_text.setFillColor(appContainer->get_font_color().first);
    input_text.setFont(font);
    sf::Text points_text;
    points_text.setPosition(400, 560);
    points_text.setCharacterSize(24);
    points_text.setFillColor(appContainer->get_font_color().first);
    points_text.setFont(font);
    points_text.setStyle(sf::Text::Underlined);
    sf::Text health_text;
    health_text.setPosition(500, 560);
    health_text.setCharacterSize(24);
    health_text.setFillColor(appContainer->get_font_color().first);
    health_text.setFont(font);
    health_text.setStyle(sf::Text::Underlined);
    sf::Text result_text;
    result_text.setPosition(400, 300);
    result_text.setCharacterSize(30);
    result_text.setFillColor(appContainer->get_font_color().first);
    result_text.setFont(font);
    sf::Text play_again;
    play_again.setPosition(100, 450);
    play_again.setCharacterSize(30);
    play_again.setFillColor(appContainer->get_font_color().first);
    play_again.setFont(font);
    sf::Text go_back;
    go_back.setPosition(400, 450);
    go_back.setCharacterSize(30);
    go_back.setFillColor(appContainer->get_font_color().first);
    go_back.setFont(font);
    sf::Text resume;
    resume.setPosition(100, 450);
    resume.setCharacterSize(30);
    resume.setFillColor(appContainer->get_font_color().first);
    resume.setFont(font);
    sf::Text save;
    save.setPosition(400, 450);
    save.setCharacterSize(30);
    save.setFillColor(appContainer->get_font_color().first);
    save.setFont(font);
    //determine highlight color
    sf::Color color_highligh;
    for (auto c: highlight_list)
    {
        if (c.first == appContainer->get_background().first)
        {
            if (c.second.first == appContainer->get_font_color().first){
                color_highligh = c.second.second;
            }
            else{
                color_highligh = c.second.first;
            }
        }
    }
    while (window->isOpen())
    {
        if (state == GameScreenState::play)
        {
            auto event = sf::Event();
            while (window->pollEvent(event)) {
                if (event.type == sf::Event::KeyPressed) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        for (int i = 0; i < shown_words.size(); i++) {
                            Word *wo = &shown_words.at(i);
                            if (wo->word == toLowerCase(input)) {
                                points += wo->worth;
                                shown_words.erase(shown_words.begin() + i);
                                break;
                            }
                        }
                        input = "";
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                    {
                        input = input.substr(0, input.length()-1);
                    }
                    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                        state = GameScreenState::pauseresume;
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
                Word *wo = &shown_words.at(i);
                //highlight
                std::string highligh = "";
                std::string not_highligh = "";
                int n = 0;
                for (auto &ch: wo->word)
                {
                    if (n!=-1 && n < input.length() && ch == tolower(input.at(n)))
                    {
                        highligh += ch;
                        n++;
                    }
                    else{
                        n = -1;
                        not_highligh += ch;
                    }

                }
                sf::Text highligh_text;
                highligh_text.setPosition(wo->posx, wo->posy);
                highligh_text.setString(highligh);
                highligh_text.setFont(font);
                highligh_text.setFillColor(color_highligh);
                sf::Text text;
                text.setPosition(wo->posx+highligh_text.getGlobalBounds().getSize().x, wo->posy);
                text.setString(not_highligh);
                text.setFont(font);
                text.setFillColor(appContainer->get_font_color().first);

                wo->accelerate();
                if (wo->posx == window->getSize().x)
                {
                    health -= 1;
                    shown_words.erase(shown_words.begin() + i);
                    continue;
                }
                window->draw(highligh_text);
                window->draw(text);
            }
            if (health == 0){
                state = GameScreenState::endPlayAgain;
            }
            if (points < 1300){
                if (rand() % 20000 >= 19997 - (points - points % 50) / 50)
                {
                    int y = determine_word_pos();
                    if (y != -1) {
                        Word wo = Word(list_of_words, y);
                        shown_words.push_back(wo);
                    }
                }
            }
            else{
                if (rand() % 20000 >= 19970) {
                    int y = determine_word_pos();
                    if (y != -1) {
                        Word wo = Word(list_of_words, y);
                        shown_words.push_back(wo);
                    }


                }
            }
            health_text.setString("Health: " + std::to_string(health));
            points_text.setString(std::to_string(points));
            input_text.setString("[" + input + "]");
            window->draw(health_text);
            window->draw(points_text);
            window->draw(input_text);

            window->display();
        }
        else if (state == GameScreenState::endPlayAgain || state == GameScreenState::endGoBack)
        {
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
                                read_file();
                                break;
                            case GameScreenState::endGoBack:
                                return;
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                    sf::Vector2f worldPosition = window->mapPixelToCoords(mousePosition);

                    if (play_again.getGlobalBounds().contains(worldPosition))
                    {
                        state = GameScreenState::play;
                        points = 0;
                        shown_words.clear();
                        read_file();
                    }
                    else if (go_back.getGlobalBounds().contains(worldPosition))
                    {
                        return;
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
        else {
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
                            case GameScreenState::pauseresume:
                                state = GameScreenState::play;
                                break;
                            case GameScreenState::pausesave:
                                appContainer->set_saved_game_words(shown_words);
                                save_to_file();
                                return;
                        }
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window);
                    sf::Vector2f worldPosition = window->mapPixelToCoords(mousePosition);
                    if (resume.getGlobalBounds().contains(worldPosition))
                    {
                        state = GameScreenState::play;
                    }
                    else if (save.getGlobalBounds().contains(worldPosition))
                    {
                        appContainer->set_saved_game_words(shown_words);
                        save_to_file();
                        return;
                    }
                }
                if (event.type == sf::Event::Closed)
                    window->close();
            }
            resume.setString("Resume");
            resume.setStyle(sf::Text::Regular);
            save.setString("Save");
            save.setStyle(sf::Text::Regular);
            switch (state)
            {
                case GameScreenState::pauseresume:
                    resume.setString(">Resume<");
                    resume.setStyle(sf::Text::Underlined);
                    break;
                case GameScreenState::pausesave:
                    save.setString(">Save<");
                    save.setStyle(sf::Text::Underlined);
                    break;
            }
            window->draw(background_rec);
            window->draw(resume);
            window->draw(save);
            window->display();
        }
    }
}

void Game_Screen::read_file()
{
    std::vector<std::string> files_names;
    switch(appContainer->get_game_option().first)
    {
        case game_state::short_words:
            files_names.push_back("../words_short.txt");
            break;
        case game_state::medium_word:
            files_names.push_back("../words_medium.txt");
            break;
        case game_state::long_words:
            files_names.push_back("../words_long.txt");
            break;
        case game_state::all:
            files_names.push_back("../words_short.txt");
            files_names.push_back("../words_medium.txt");
            files_names.push_back("../words_long.txt");
            break;
    }
    for(auto file_name: files_names) {
        std::ifstream file(file_name);
        if (!file.is_open()) {
            FileOpenFailedException exception;
            throw  exception;
        }
        std::string word;
        while (std::getline(file, word)) {
            list_of_words.push_back(word);
        }

        file.close();
    }

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
        case GameScreenState::pauseresume:
            state = GameScreenState::pausesave;
            break;
        case GameScreenState::pausesave:
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
        case GameScreenState::pauseresume:
            break;
        case GameScreenState::pausesave:
            state = GameScreenState::pauseresume;
            break;
    }
}

void Game_Screen::save_to_file()
{
    std::ofstream file("../save.txt");
    if (!file.is_open()) {
        FileOpenFailedException exception;
        throw  exception;
    }
    file<<appContainer->get_game_option().second<<"\n";
    file<<points<<"\n"<<health<<"\n";
    for (auto w: appContainer->return_word_list())
    {
        file<<w<<"\n";
    }
    file.close();
}

int Game_Screen::determine_word_pos() {
    if (shown_words.empty())
    {
        return  rand()%500 + 10;
    }
    for(int n = 35; n<=510; n+=50) {
        int k = 0;
        for (const auto& word: shown_words) {
            if (word.posy < n - 25 || word.posy > n + 25) {
                k++;
            }
            else{
                if (word.posx >= 70) {k++;}
                else {break;}
            }
        }
        if (k==shown_words.size()) {return  n;}
    }
    return -1;
}

int Game_Screen::getHealth() {return health;}

int Game_Screen::getPoints() {return points;}

