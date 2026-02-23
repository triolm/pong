#ifndef BALL_H
#define BALL_H


#include "Entity.h"
#include "Paddle.h"


class Ball: public Entity
{
public:
    Ball(Vector2 position, Vector2 scale, const char *textureFilepath,
        float minHeight, float maxHeight,float minWidth, float maxWidth) : 
        minHeight(minHeight), maxHeight(maxHeight),   
        minWidth(minWidth), maxWidth(maxWidth),   
        Entity(position, scale, textureFilepath) {
        setSpeed(400);
    }

    void update(float deltaTime){
        Entity::update(deltaTime);
        if(getPosition().y > maxHeight || getPosition().y < minHeight) {
            setMovementY(-getMovement().y);
            setPositionY(getPosition().y + getMovement().y*2);
        }

        if(getPosition().x > maxWidth || getPosition().x < minWidth) {
            setPosition({(minWidth + maxWidth)/2.0f,(minHeight+maxHeight)/2.0f});
            setMovementY(0);
            normaliseMovement();
        }

    }

    void paddleInteraction(Paddle* p){
        printf("%d\n", isColliding(p));
        if(isColliding(p)){
            setMovementX(-getMovement().x);
            setPositionX(getPosition().x + getMovement().x*2);
            // https://community.khronos.org/t/the-math-of-pong-or-deflection-of-an-object-off-a-surface/32572/5
            float paddleY = p->getPosition().y;
            float paddleHeight = p->getScale().y/2.0f;
            
            printf("%f\n", paddleHeight/(paddleY-getPosition().y));
            setMovementY((getPosition().y-paddleY)/paddleHeight);
            normaliseMovement();
        }
    }

private:
    float minHeight, maxHeight;
    float minWidth, maxWidth;
};

#endif