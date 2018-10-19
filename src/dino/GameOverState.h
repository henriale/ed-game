/*
 *  PauseState.h
 *  Normal "pause" state
 *
 *  Created by Marcelo Cohen on 08/13.
 *  Copyright 2013 PUCRS. All rights reserved.
 *
 */

#ifndef GAME_OVER_STATE_H_
#define GAME_OVER_STATE_H_

#include "GameState.h"
#include "Sprite.h"

class GameOverState : public cgf::GameState
{
    public:

    void init();
    void cleanup();

    void pause();
    void resume();

    void handleEvents(cgf::Game* game);
    void update(cgf::Game* game);
    void draw(cgf::Game* game);

    // Implement Singleton Pattern
    static GameOverState* instance()
    {
        return &m_GameOverState;
    }

    protected:

    GameOverState() {}

    private:

    static GameOverState m_GameOverState;

    sf::Font font;
    sf::Text text;
};

#endif
