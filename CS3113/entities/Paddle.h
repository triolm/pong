#ifndef PADDLE_H
#define PADDLE_H
#include "Entity.h"


class Paddle: public Entity
{
public:
    Paddle(Vector2 position, Vector2 scale, const char *textureFilepath, 
           float minHeight, float maxHeight) : 
           minHeight(minHeight), maxHeight(maxHeight), 
           Entity(position, scale, textureFilepath) {}


    void update(float deltaTime){
        Entity::update(deltaTime);
        if(getPosition().y > maxHeight) setPositionY(maxHeight);
        if(getPosition().y < minHeight) setPositionY(minHeight);
    }

private:
    float minHeight, maxHeight;
};

#endif