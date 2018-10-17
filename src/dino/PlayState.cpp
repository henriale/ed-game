/*
 *  PlayState.cpp
 *  Normal "play" state
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>
#include "Game.h"
#include "PlayState.h"
#include "PauseState.h"
#include "InputManager.h"

PlayState PlayState::m_PlayState;

using namespace std;

void PlayState::init()
{
    // Smurff
    playSprite1.load("data/img/smurf.png", 128, 128, 5, 5, 5, 5, 6, 3, 16);
    playSprite1.setPosition(10,100);
    playSprite1.setFrameRange(0,15);
    playSprite1.setAnimRate(30);
    playSprite1.play();

    // Dino
    playSpriteDino.load("data/img/alex.png", 86, 94, 0, 0, 0, 0, 3, 2, 24);
    playSpriteDino.setPosition(200,100);
    playSpriteDino.setFrameRange(0,15);
    playSpriteDino.setAnimRate(15);
    playSpriteDino.play();

    dirx = 0; // sprite direction: right (1), left (-1)
    diry = 0; // down (1), up (-1)

    im = cgf::InputManager::instance();

    im->addKeyInput("left", sf::Keyboard::Left);
    im->addKeyInput("right", sf::Keyboard::Right);
    im->addKeyInput("up", sf::Keyboard::Up);
    im->addKeyInput("down", sf::Keyboard::Down);
    im->addKeyInput("quit", sf::Keyboard::Escape);
    im->addKeyInput("stats", sf::Keyboard::S);
    im->addMouseInput("rightclick", sf::Mouse::Right);

	cout << "PlayState: Init" << endl;
}

void PlayState::cleanup()
{
	cout << "PlayState: Clean" << endl;
}

void PlayState::pause()
{
	cout << "PlayState: Paused" << endl;
}

void PlayState::resume()
{
	cout << "PlayState: Resumed" << endl;
}

void PlayState::handleEvents(cgf::Game* game)
{
    sf::Event event;

    while (screen->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            game->quit();
        if(event.key.code == sf::Keyboard::P)
            game->pushState(PauseState::instance());
    }

    dirx = diry = 0;

    if(im->testEvent("left"))
        dirx = -1;

    if(im->testEvent("right"))
        dirx = 1;

    if(im->testEvent("up"))
        diry = -1;

    if(im->testEvent("down"))
        diry = 1;

    if(im->testEvent("quit") || im->testEvent("rightclick"))
        game->quit();

    if(im->testEvent("stats"))
        game->toggleStats();
}

void PlayState::update(cgf::Game* game)
{
    playSprite1.update(game->getUpdateInterval());
    playSpriteDino.update(game->getUpdateInterval());
}

void PlayState::draw(cgf::Game* game)
{
    screen = game->getScreen();
    screen->draw(playSprite1);
    screen->draw(playSpriteDino);
}

