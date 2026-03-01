#ifndef POWER_H
#define POWER_H


#include "Entity.h"
#include "Paddle.h"


class PowerUp: public Entity
{
public:
    PowerUp(Vector2 position, Vector2 scale, const char *textureFilepath,
        float minHeight, float maxHeight,float minWidth, float maxWidth,
        Vector2 spriteSheetDimensions, std::vector<int> animationIndices) : 

        minHeight(minHeight), maxHeight(maxHeight), 
        minWidth(minWidth), maxWidth(maxWidth),
        Entity(position, scale, textureFilepath, 
        spriteSheetDimensions, animationIndices){

        // setSpeed(500);
    }

    void update(float deltaTime, Paddle* p1, Paddle* p2){
        if(!on && GetRandomValue(1,1000) == 2){
            // printf("hi\n");
            on = true;
            setPosition({minWidth, (float)GetRandomValue((int)minHeight, (int)maxHeight)});
            if(isColliding(p1) || isColliding(p2)) on = false;
        }
        
        if(!on && GetRandomValue(1,1000) == 2){
            // printf("hi\n");
            on = true;
            setPosition({maxWidth, (float)GetRandomValue((int)minHeight, (int)maxHeight)});
            if(isColliding(p1) || isColliding(p2)) on = false;
        }

        if(on) paddleInteraction(p1);
        if(on) paddleInteraction(p2);

    }

    void render(){
        if(on) {
            // printf("b\n");
            Entity::render();
        }
    }


    void paddleInteraction(Paddle* p){
        // printf("%d\n", isColliding(p));
        if(isColliding(p)){
           on = false;
           p->upgrade();
        }
    }

    void reset(){
        on = false;
    }

private:
    float minHeight, maxHeight;
    float minWidth, maxWidth;
    bool on = false;
};

#endif