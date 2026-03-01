#ifndef BALL_H
#define BALL_H


#include "Entity.h"
#include "Paddle.h"


class Ball: public Entity
{
public:
    Ball(Vector2 position, Vector2 scale, const char *textureFilepath,
        float minHeight, float maxHeight,float minWidth, float maxWidth,
        Vector2 spriteSheetDimensions, std::vector<int> animationIndices, float speed = 500) : 

        minHeight(minHeight), maxHeight(maxHeight), 
        minWidth(minWidth), maxWidth(maxWidth),
        Entity(position, scale, textureFilepath, 
        spriteSheetDimensions, animationIndices){

        // setSpeed(500);
        moveLeft();
        reset(speed);
    }

    void update(float deltaTime){
        if(dead) return;
        // printf("%f\n",getColliderDimensions().y/2.0f);
        Entity::update(deltaTime);
        if(getPosition().y +  getColliderDimensions().y/2.0f > maxHeight){
            setMovementY(-getMovement().y);
            setPositionY(maxHeight - getColliderDimensions().y/2.0f);
            setAngle(GetRandomValue(0,365));
        }
        if(getPosition().y -  getColliderDimensions().y/2.0f < minHeight) {
            setMovementY(-getMovement().y);
            setPositionY(minHeight + getColliderDimensions().y/2.0f);
            setAngle(GetRandomValue(0,365));
        }

        if(getPosition().x > maxWidth || 
           getPosition().x - getColliderDimensions().x < minWidth) {
            // reset();
            dead = true;
            beenScored = false;
        }

    }

    bool getDead() const {
        return dead;
    }
    void setDead(bool dead){
        this->dead = dead;
    }

    bool getBeenScored() const{
        return beenScored;
    }

    void setBeenScored(bool s){
        beenScored = s;
    }

    void reset(float speed){
        setSpeed(speed);
        setPosition({(minWidth + maxWidth)/2.0f,(minHeight+maxHeight)/2.0f});
            setMovementY(0);
            normaliseMovement();
            setMovementY(GetRandomValue(-15,15)/100.0f);
            normaliseMovement();
    }

    void paddleInteraction(Paddle* p){
        // printf("%d\n", isColliding(p));
        if(isColliding(p)){
            setMovementX(-getMovement().x);
            // https://community.khronos.org/t/the-math-of-pong-or-deflection-of-an-object-off-a-surface/32572/5
            float paddleY = p->getPosition().y;
            float paddleHeight = p->getScale().y/2.0f;
            setMovementY((getPosition().y-paddleY)/paddleHeight);
            normaliseMovement();

            setSpeed(getSpeed() * 1.025f);

            setAngle(GetRandomValue(0,365));

            float posDiff = p->getPosition().x - getPosition().x;
            
            if(posDiff > 0) posDiff -= p->getColliderDimensions().x/2.0f + getColliderDimensions().x/2.0f;
            else posDiff += p->getColliderDimensions().x/2.0f + getColliderDimensions().x/2.0f;

            // if(posDiff.y > 0) posDiff.y -= p->getColliderDimensions().y + getColliderDimensions().y;
            // else posDiff.y += p->getColliderDimensions().y + getColliderDimensions().y;
            setPositionX(getPosition().x + posDiff);

            
        }
    }

private:
    float minHeight, maxHeight;
    float minWidth, maxWidth;
    bool dead = false;
    bool beenScored = true;
};

#endif