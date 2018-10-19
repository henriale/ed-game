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
#include "GameOverState.h"
#include "InputManager.h"

PlayState PlayState::m_PlayState;

using namespace std;

void PlayState::init()
{
    map = new tmx::MapLoader("data/maps");       // todos os mapas/tilesets serão lidos de data/maps
    map->Load("dino-world.tmx");

    // Smurff
    playSpriteDino.load("data/img/smurf.png", 128, 128, 5, 5, 5, 5, 6, 3, 16);
    // DINO
    //playSpriteDino.load("data/img/sprite-dino.png", 448, 477, 0, 0, 30, 10, 4, 4, 16);
    playSpriteDino.setPosition(10,120);
    playSpriteDino.setFrameRange(0,15);
    playSpriteDino.setAnimRate(30);
    playSpriteDino.play();

    // Cactus
    cactus.load("data/img/cactus.png", 50, 100, 0, 0, 0, 0, 1, 1);
    cactus.setPosition(600,150);
    cactus.setFrameRange(0,15);
    cactus.setAnimRate(30);
    cactus.play();

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

void PlayState::centerMapOnPlayer()
{
    sf::View view = screen->getView();
    sf::Vector2u mapsize = map->GetMapSize();
    sf::Vector2f viewsize = view.getSize();
    viewsize.x /= 2;
    viewsize.y /= 2;
    sf::Vector2f pos = playSpriteDino.getPosition();

    float panX = viewsize.x; // minimum pan
    if(pos.x >= viewsize.x)
        panX = pos.x;

    if(panX >= mapsize.x - viewsize.x)
        panX = mapsize.x - viewsize.x;

    float panY = viewsize.y; // minimum pan
    if(pos.y >= viewsize.y)
        panY = pos.y;

    if(panY >= mapsize.y - viewsize.y)
        panY = mapsize.y - viewsize.y;

    view.setCenter(sf::Vector2f(panX,panY));
    screen->setView(view);
}

void PlayState::cleanup()
{
    delete map;
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

void PlayState::handleEvents(cgf::Game* game) {
    sf::Event event;

    while (screen->pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            game->quit();

        if(event.key.code == sf::Keyboard::P)
            game->pushState(PauseState::instance());
    }

    dirx = diry = 0;

// O DINO SÓ ANDA PRA FRENTE
//    if(im->testEvent("left"))
//        dirx = -1;

    if(im->testEvent("right"))
        dirx = 2;

    if(im->testEvent("up")) {
        diry = -5;
        isPulando = true;
    }

// O DINO NAO ENTRA NO SUBTERRANEO
//    if(im->testEvent("down"))
//        diry = 1;

    if(im->testEvent("quit") || im->testEvent("rightclick"))
        game->quit();

    if(im->testEvent("stats"))
        game->toggleStats();
}

void PlayState::update(cgf::Game* game)
{
    screen = game->getScreen();

    float x = playSpriteDino.getPosition().x;
    float y = playSpriteDino.getPosition().y;
    x += dirx * 5;
    y += diry * 5;

    playSpriteDino.setPosition(x,y);
    playSpriteDino.update(game->getUpdateInterval());

    if(playSpriteDino.bboxCollision(cactus)) {
        cout << "Colisão!" << endl;
        game->changeState(GameOverState::instance());
    }

    centerMapOnPlayer();
}

void PlayState::draw(cgf::Game* game)
{
    screen = game->getScreen();
    map->Draw(*screen);         // mapa é fundo, precisa desenhar primeiro
    screen->draw(playSpriteDino);
    screen->draw(cactus);

}

