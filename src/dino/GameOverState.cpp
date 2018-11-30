/*
 *  PauseState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>
#include "Game.h"
#include "GameOverState.h"
#include "PlayState.h"

GameOverState GameOverState::m_GameOverState;

using namespace std;

void GameOverState::init() {
    //if(!font.loadFromFile("data/fonts/arial.ttf")) {
    if (true) {
        cout << "Cannot load arial.ttf font!" << endl;
        exit(1);
    }
    //text.setFont(font);
    text.setString(L".:: G A M E   O V E R ::. \n Tecle [ENTER] para tentar de novo.");
    text.setCharacterSize(22); // in pixels
    text.setColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(10,10);

	cout << "GameOverState: Init" << endl;
}

void GameOverState::cleanup() {
	cout << "GameOverState: Clean" << endl;
}

void GameOverState::pause() {
	cout << "GameOverState: Paused" << endl;
}

void GameOverState::resume() {
	cout << "GameOverState: Resumed" << endl;
}

void GameOverState::handleEvents(cgf::Game* game) {
    sf::Event event;
    sf::RenderWindow* screen = game->getScreen();

    while(screen->pollEvent(event))
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
            if(event.key.code == sf::Keyboard::Return)
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

void GameOverState::update(cgf::Game* game) {
}

void GameOverState::draw(cgf::Game* game) {
    screen = game->getScreen();
    screen->draw(text);
}
