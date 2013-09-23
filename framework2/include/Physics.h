/*
 *  Physics.h
 *  Physics manager using Box2D
 *
 *  Created by Marcelo Cohen on 05/11.
 *  Copyright 2011 PUCRS. All rights reserved.
 *
 */

#ifndef CGF_PHYSICS_H
#define CGF_PHYSICS_H

#include <Box2D/Box2D.h>
#include "Sprite.h"

namespace cgf
{

struct BodyData
{
    int id;         // id for the body (used in contacts)
    Sprite* image;  // image associated to the body (can be NULL)
    b2Vec2 size;    // size of the collision object (not used)
    b2Vec2 offset;  // offset for drawing
    b2Color color;  // color for drawing collision object (when image == NULL)
};

class Physics
{
    public:
        b2Body* newBoxImage(int id, Sprite* sprite, float density, float friction, float restitution, bool staticObj=false);
        b2Body* newBox(int id, float x, float y, float width, float height, float density, float friction, float restitution, bool staticObj=false);
        b2Body* newCircleImage(int id, Sprite* sprite, float density, float friction, float restitution, bool staticObj=false);
        b2Body* newCircle(int id, float x, float y, float radius, float density, float friction, float restitution, bool staticObj=false);
        void destroy(b2Body* bptr);

        void setImage(b2Body* body, Sprite* sprite);
        Sprite* getImage(b2Body* body);

        void setColor(b2Body* body, const b2Color& cor);
        b2Color& getColor(b2Body* body);

        void setPosition(b2Body* body, const b2Vec2& pos);
        void setAngle(b2Body* body, float angle);
        b2Vec2 getPosition(b2Body* body);

        void setGravity(float grav);
        float getGravity();
    
        void step();
        void debugDraw();
        b2Body* haveContact(int id1, int id2);

        void setDrawOffset(float ox, float oy);

        static void setConvFactor(float conv);

        // Implement Singleton Pattern
        static Physics* instance()
        {
            return &m_Physics;
        }
    protected:
        Physics();
        ~Physics();
    private:
        static Physics m_Physics;
        static const int velocityIterations = 10;
        static const int positionIterations = 8;
        static const float timeStep;

        static float CONV; // fator de conversão Box2D -> OpenGL

        float gravity;
        float offsetX, offsetY; // offset to apply to translation when drawing

        b2World* world;
};

} // namespace cgf
#endif // Physics_H