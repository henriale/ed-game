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
#include "PauseState.h"
#include "InputManager.h"

PauseState PauseState::m_PauseState;

using namespace std;

void PauseState::init() {
    if (!font.loadFromFile("data/fonts/arial.ttf")) {
        cout << "Cannot load arial.ttf font!" << endl;
        exit(1);
    }
    text.setFont(font);
    text.setString(L".:: P A U S E ::. \n Tecle [R] para retornar ao jogo.");
    text.setCharacterSize(22); // in pixels
    text.setColor(sf::Color::White);

	cout << "PauseState: Init" << endl;
}

void PauseState::cleanup() {
	cout << "PauseState: Clean" << endl;
}

void PauseState::pause() {
	cout << "PauseState: Paused" << endl;
}

void PauseState::resume() {
	cout << "PauseState: Resumed" << endl;
}

void PauseState::handleEvents(cgf::Game* game) {
    sf::Event event;

    while(screen->pollEvent(event)) {
        if(event.key.code == sf::Keyboard::R)
            game->popState();
    }
}

void PauseState::update(cgf::Game* game) {
}

void PauseState::draw(cgf::Game* game) {
    screen = game->getScreen();
    screen->draw(text);
}
