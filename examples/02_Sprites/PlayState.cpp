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
    playSpriteDino.load("data/img/dino-trex.png", 86, 94, 1, 1, 1, 1, 6, 1, 16);
    playSpriteDino.setPosition(200,100);
    playSpriteDino.setFrameRange(0,15);
    playSpriteDino.setAnimRate(15);
    playSpriteDino.play();

    dirx = 0; // direção do sprite: para a direita (1), esquerda (-1)
    diry = 0; // baixo (1), cima (-1)

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
    screen = game->getScreen();
    sf::Event event;

    while (screen->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            game->quit();
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

    playSprite1.setXspeed(50*dirx);
    playSprite1.setYspeed(50*diry);
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
