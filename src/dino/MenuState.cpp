/*
 *  MenuState.cpp
 *  Example "menu" state
 *
 *  Created by Marcelo Cohen on 04/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include "Game.h"
#include "InputManager.h"
#include "MenuState.h"
#include "PlayState.h"

MenuState MenuState::m_MenuState;

using namespace std;

void MenuState::init() {

    text.setFont(font);
    text.setString(L"PUCRS - FACIN\nEntretenimento Digital\nT-Rex Game\n\nAcione a barra de espaco para iniciar o jogo");
    text.setCharacterSize(24); // in pixels
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);

    cout << "MenuState Init Successful" << endl;
}

void MenuState::cleanup()
{
    cout << "MenuState Cleanup Successful" << endl;
}

void MenuState::pause()
{
    cout << "MenuState Paused" << endl;
}

void MenuState::resume()
{
    cout << "MenuState Resumed" << endl;
}

void MenuState::handleEvents(cgf::Game* game)
{
    sf::Event event;
    sf::RenderWindow* screen = game->getScreen();

    while (screen->pollEvent(event))
    {
        // check the type of the event...
        switch (event.type)
        {
            // window closed
        case sf::Event::Closed:
            game->quit();
            break;

            // key pressed
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Space)
                game->changeState(PlayState::instance());
            if(event.key.code == sf::Keyboard::Escape)
                game->quit();
            break;

            // we don't process other types of events
        default:
            break;
        }
    }
}

void MenuState::update(cgf::Game* game) {
}

void MenuState::draw(cgf::Game *game) {
    sf::RenderWindow* screen = game->getScreen();
    screen->draw(text);
}

