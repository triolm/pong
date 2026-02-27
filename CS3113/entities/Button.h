#ifndef BUTTON_H
#define BUTTON_H
#include "Entity.h"


class Button: public Entity
{
public:
    Button(Vector2 position, Vector2 scale, const char *textureFilepath,
           Vector2 spriteSheetDimensions,  std::vector<int> animationIncides) :  
           Entity(position, scale, textureFilepath, 
           spriteSheetDimensions, animationIncides) {}


    bool CollidingWithPoint(Vector2 point){
       float xDistance = fabs(getPosition().x - point.x) - getColliderDimensions().x/2 ;
        float yDistance = fabs(getPosition().y - point.y) - getColliderDimensions().y/2;
        // printf("HI\n");
        if (xDistance < 0.0f && yDistance < 0.0f) return true;
        // printf("X\n");

        return false;
    }

private:
    float minHeight, maxHeight;
};

#endif